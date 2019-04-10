#include "header/model/wtg_models/wt_relay_model/wtrly0.h"
#include "header/basic/utility.h"
#include <iostream>
using namespace std;

WTRLY0::WTRLY0()
{
    clear();
}

WTRLY0::~WTRLY0()
{
    clear();
}

void WTRLY0::clear()
{
    prepare_model_data_table();
    prepare_model_internal_variable_table();

    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        set_wind_spped_relay_pair_in_pu_s(i, 0.0, 0.0);
        set_rotor_speed_relay_pair_in_pu_s(i, 0.0, 0.0);
        set_bus_frequency_relay_pair_in_pu_s(i, 0.0, 0.0);
        set_bus_voltage_relay_pair_in_pu_s(i, 0.0, 0.0);
    }
}

void WTRLY0::copy_from_const_model(const WTRLY0& model)
{
    clear();

    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        set_wind_spped_relay_pair_in_pu_s(i, model.get_wind_speed_relay_threshold_in_pu(i), model.get_wind_speed_relay_delay_in_s(i));
        set_rotor_speed_relay_pair_in_pu_s(i, model.get_rotor_speed_relay_threshold_in_pu(i), model.get_rotor_speed_relay_delay_in_s(i));
        set_bus_frequency_relay_pair_in_pu_s(i, model.get_bus_frequency_relay_threshold_in_pu(i), model.get_bus_frequency_relay_delay_in_s(i));
        set_bus_voltage_relay_pair_in_pu_s(i, model.get_bus_voltage_relay_threshold_in_pu(i), model.get_bus_voltage_relay_delay_in_s(i));
    }
}

WTRLY0::WTRLY0(const WTRLY0& model) : WT_RELAY_MODEL()
{
    copy_from_const_model(model);
}

WTRLY0& WTRLY0::operator=(const WTRLY0& model)
{
    if(this==&model)
        return *this;

    copy_from_const_model(model);

    return (*this);
}

string WTRLY0::get_model_name() const
{
    return "WTRLY0";
}

void WTRLY0::set_wind_spped_relay_pair_in_pu_s(size_t index, double vwind, double tdelay)
{
    if(index>=MAX_RELAY_COUNT)
    {
        ostringstream osstream;
        osstream<<"Warning. Index exceeds "<<MAX_RELAY_COUNT<<" when setting up "<<get_model_name()<<" of "<<get_device_name()<<endl
                <<"No wind speed relay pair will be set.";
        show_information_with_leading_time_stamp(osstream);
    }
    vwind_th[index] = vwind;
    vwind_relay_timer[index].set_timer_interval_in_s(tdelay);
}

void WTRLY0::set_rotor_speed_relay_pair_in_pu_s(size_t index, double speed, double tdelay)
{
    if(index>=MAX_RELAY_COUNT)
    {
        ostringstream osstream;
        osstream<<"Warning. Index exceeds "<<MAX_RELAY_COUNT<<" when setting up "<<get_model_name()<<" of "<<get_device_name()<<endl
                <<"No rotor speed relay pair will be set.";
        show_information_with_leading_time_stamp(osstream);
    }
    speed_th[index] = speed;
    speed_relay_timer[index].set_timer_interval_in_s(tdelay);
}

void WTRLY0::set_bus_frequency_relay_pair_in_pu_s(size_t index, double freq, double tdelay)
{
    if(index>=MAX_RELAY_COUNT)
    {
        ostringstream osstream;
        osstream<<"Warning. Index exceeds "<<MAX_RELAY_COUNT<<" when setting up "<<get_model_name()<<" of "<<get_device_name()<<endl
                <<"No bus frequency relay pair will be set.";
        show_information_with_leading_time_stamp(osstream);
    }
    freq_th[index] = freq;
    freq_relay_timer[index].set_timer_interval_in_s(tdelay);
}

void WTRLY0::set_bus_voltage_relay_pair_in_pu_s(size_t index, double volt, double tdelay)
{
    if(index>=MAX_RELAY_COUNT)
    {
        ostringstream osstream;
        osstream<<"Warning. Index exceeds "<<MAX_RELAY_COUNT<<" when setting up "<<get_model_name()<<" of "<<get_device_name()<<endl
                <<"No bus voltage relay pair will be set.";
        show_information_with_leading_time_stamp(osstream);
    }
    volt_th[index] = volt;
    volt_relay_timer[index].set_timer_interval_in_s(tdelay);
}

double WTRLY0::get_wind_speed_relay_threshold_in_pu(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return vwind_th[index];
    else
        return 0.0;
}

double WTRLY0::get_wind_speed_relay_delay_in_s(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return vwind_relay_timer[index].get_timer_interval_in_s();
    else
        return 0.0;
}

double WTRLY0::get_rotor_speed_relay_threshold_in_pu(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return speed_th[index];
    else
        return 0.0;
}

double WTRLY0::get_rotor_speed_relay_delay_in_s(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return speed_relay_timer[index].get_timer_interval_in_s();
    else
        return 0.0;
}

double WTRLY0::get_bus_frequency_relay_threshold_in_pu(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return freq_th[index];
    else
        return 0.0;
}

double WTRLY0::get_bus_frequency_relay_delay_in_s(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return freq_relay_timer[index].get_timer_interval_in_s();
    else
        return 0.0;
}

double WTRLY0::get_bus_voltage_relay_threshold_in_pu(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return volt_th[index];
    else
        return 0.0;
}

double WTRLY0::get_bus_voltage_relay_delay_in_s(size_t index) const
{
    if(index<MAX_RELAY_COUNT)
        return volt_relay_timer[index].get_timer_interval_in_s();
    else
        return 0.0;
}

bool WTRLY0::setup_model_with_steps_string_vector(vector<string>& data)
{
    /*wtrly0  bus  ickt
              nvwind v1  t1  v2  t2  vn  tn
              nspeed s1  t1  s2  t2  sn  tn
              nfreq  f1  t1  f2  t2  fn  tn
              nvolt  v1  t1  v2  t2  vn  tn /
    */
    bool is_successful = false;
    if(data.size()<7)
        return is_successful;

    string model_name = get_string_data(data[0],"");
    if(model_name!=get_model_name())
        return is_successful;

    size_t n;
    double v, s, f, t;

    size_t i=3;
    n = get_integer_data(data[i], "0"); ++i;
    for(size_t k=0; k<n; ++k)
    {
        v = get_double_data(data[i], "0.0"); ++i;
        t = get_double_data(data[i], "0.0"); ++i;
        set_wind_spped_relay_pair_in_pu_s(k, v, t);
        cout<<"wind speed relay pair: "<<k<<", "<<v<<", "<<t<<endl;
    }

    n = get_integer_data(data[i], "0"); ++i;
    for(size_t k=0; k<n; ++k)
    {
        s = get_double_data(data[i], "0.0"); ++i;
        t = get_double_data(data[i], "0.0"); ++i;
        set_rotor_speed_relay_pair_in_pu_s(k, s, t);
        cout<<"rotor speed relay pair: "<<k<<", "<<s<<", "<<t<<endl;
    }

    n = get_integer_data(data[i], "0"); ++i;
    for(size_t k=0; k<n; ++k)
    {
        f = get_double_data(data[i], "0.0"); ++i;
        t = get_double_data(data[i], "0.0"); ++i;
        set_bus_frequency_relay_pair_in_pu_s(k, f, t);
        cout<<"bus frequency relay pair: "<<k<<", "<<f<<", "<<t<<endl;
    }

    n = get_integer_data(data[i], "0"); ++i;
    for(size_t k=0; k<n; ++k)
    {
        v = get_double_data(data[i], "0.0"); ++i;
        t = get_double_data(data[i], "0.0"); ++i;
        set_bus_voltage_relay_pair_in_pu_s(k, v, t);
        cout<<"bus voltage relay pair: "<<k<<", "<<v<<", "<<t<<endl;
    }

    is_successful = true;

    return is_successful;
}

bool WTRLY0::setup_model_with_psse_string(string data)
{
    vector<string> record = psse_dyr_string2steps_string_vector(data);
    return setup_model_with_steps_string_vector(record);
}

bool WTRLY0::setup_model_with_bpa_string(string data)
{
    ostringstream osstream;
    osstream<<get_model_name()<<"::"<<__FUNCTION__<<"() is not fully supported to set up model with following data:"<<endl
            <<data;
    show_information_with_leading_time_stamp(osstream);
    return false;
}


void WTRLY0::initialize()
{
    WT_GENERATOR* gen = get_wt_generator_pointer();
    if(gen==NULL)
        return;

    WT_GENERATOR_MODEL* gen_model = gen->get_wt_generator_model();
    if(gen_model==NULL)
        return;
    if(not gen_model->is_model_initialized())
        gen_model->initialize();

    WT_AERODYNAMIC_MODEL* aero_model = gen->get_wt_aerodynamic_model();
    if(aero_model==NULL)
        return;
    if(not aero_model->is_model_initialized())
        aero_model->initialize();

    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        vwind_relay_timer[i].set_attached_device(get_wt_generator_pointer());
        speed_relay_timer[i].set_attached_device(get_wt_generator_pointer());
        freq_relay_timer[i].set_attached_device(get_wt_generator_pointer());
        volt_relay_timer[i].set_attached_device(get_wt_generator_pointer());

        vwind_relay_timer[i].reset();
        speed_relay_timer[i].reset();
        freq_relay_timer[i].reset();
        volt_relay_timer[i].reset();
    }
}

void WTRLY0::run(DYNAMIC_MODE mode)
{
    if(mode==RELAY_MODE)
    {
        check_wind_speed_relay();
        check_rotor_speed_relay();
        check_bus_frequency_relay();
        check_bus_voltage_relay();
    }
}


void WTRLY0::check_wind_speed_relay()
{
    ostringstream osstream;

    WT_GENERATOR* wtgen = (WT_GENERATOR*) get_device_pointer();
    bool status = wtgen->get_status();
    if(status==false)
        return;

    DEVICE_ID did = get_device_id();

    DYNAMICS_SIMULATOR& sim = get_default_dynamic_simulator();

    double vwind = get_wind_speed_in_pu();

    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(vwind_th[i])>FLOAT_EPSILON and fabs(vwind_th[i]-1.0)>FLOAT_EPSILON)
        {
            if(not vwind_relay_timer[i].is_started())
            {
                if(vwind_th[i]>1.0 and vwind>vwind_th[i])
                {
                    vwind_relay_timer[i].start();
                    osstream<<"Wind speed relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                            <<"s due to wind speed exceeding over wind speed threshold: "<<vwind<<" > "<<vwind_th[i]<<endl;
                    show_information_with_leading_time_stamp(osstream);
                }
                else
                {
                    if(vwind_th[i]<1.0 and vwind<vwind_th[i])
                    {
                        vwind_relay_timer[i].start();
                        osstream<<"Wind speed relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to wind speed exceeding under wind speed threshold: "<<vwind<<" < "<<vwind_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                }
            }

            if(vwind_relay_timer[i].is_started())
            {
                if(vwind_relay_timer[i].is_timed_out())
                {

                    osstream<<"Wind speed relay timer of "<<get_device_name()<<" is timed out at "<<get_dynamic_simulation_time_in_s()<<" s"<<endl;
                    show_information_with_leading_time_stamp(osstream);
                    sim.trip_wt_generator(did, INFINITE_THRESHOLD);
                    sim.enable_relay_action_flag();
                }
                else
                {
                    if(vwind_th[i]>1.0 and vwind<vwind_th[i])
                    {
                        vwind_relay_timer[i].reset();
                        osstream<<"Wind speed relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to wind speed less than over wind speed threshold: "<<vwind<<" < "<<vwind_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                    else
                    {
                        if(vwind_th[i]<1.0 and vwind>vwind_th[i])
                        {
                            vwind_relay_timer[i].reset();
                            osstream<<"Wind speed relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                    <<"s due to wind speed greater than under wind speed threshold: "<<vwind<<" > "<<vwind_th[i]<<endl;
                            show_information_with_leading_time_stamp(osstream);
                        }
                    }
                }
            }
        }
    }
}

void WTRLY0::check_rotor_speed_relay()
{
    ostringstream osstream;

    WT_GENERATOR* wtgen = (WT_GENERATOR*) get_device_pointer();
    bool status = wtgen->get_status();
    if(status==false)
        return;

    DEVICE_ID did = get_device_id();

    DYNAMICS_SIMULATOR& sim = get_default_dynamic_simulator();

    double speed = get_wt_generator_rotor_speed_in_pu();

    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(speed_th[i])>FLOAT_EPSILON and fabs(speed_th[i]-1.0)>FLOAT_EPSILON)
        {
            if(not speed_relay_timer[i].is_started())
            {
                if(speed_th[i]>1.0 and speed>speed_th[i])
                {
                    speed_relay_timer[i].start();
                    osstream<<"Rotor speed relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                            <<"s due to rotor speed exceeding over rotor speed threshold: "<<speed<<" > "<<speed_th[i]<<endl;
                    show_information_with_leading_time_stamp(osstream);
                }
                else
                {
                    if(speed_th[i]<1.0 and speed<speed_th[i])
                    {
                        speed_relay_timer[i].start();
                        osstream<<"Rotor speed relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to rotor speed exceeding under rotor speed threshold: "<<speed<<" < "<<speed_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                }
            }

            if(speed_relay_timer[i].is_started())
            {
                if(speed_relay_timer[i].is_timed_out())
                {

                    osstream<<"Rotor speed relay timer of "<<get_device_name()<<" is timed out at "<<get_dynamic_simulation_time_in_s()<<" s"<<endl;
                    show_information_with_leading_time_stamp(osstream);
                    sim.trip_wt_generator(did, INFINITE_THRESHOLD);
                    sim.enable_relay_action_flag();
                }
                else
                {
                    if(speed_th[i]>1.0 and speed<speed_th[i])
                    {
                        speed_relay_timer[i].reset();
                        osstream<<"Rotor speed relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to rotor speed less than over rotor speed threshold: "<<speed<<" < "<<speed_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                    else
                    {
                        if(speed_th[i]<1.0 and speed>speed_th[i])
                        {
                            speed_relay_timer[i].reset();
                            osstream<<"Rotor speed relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                    <<"s due to rotor speed greater than under rotor speed threshold: "<<speed<<" > "<<speed_th[i]<<endl;
                            show_information_with_leading_time_stamp(osstream);
                        }
                    }
                }
            }
        }
    }
}

void WTRLY0::check_bus_frequency_relay()
{
    ostringstream osstream;

    WT_GENERATOR* wtgen = (WT_GENERATOR*) get_device_pointer();
    bool status = wtgen->get_status();
    if(status==false)
        return;

    DEVICE_ID did = get_device_id();

    DYNAMICS_SIMULATOR& sim = get_default_dynamic_simulator();

    double freq = get_bus_frequency_in_pu();

    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(freq_th[i])>FLOAT_EPSILON and fabs(freq_th[i]-1.0)>FLOAT_EPSILON)
        {
            if(not freq_relay_timer[i].is_started())
            {
                if(freq_th[i]>1.0 and freq>freq_th[i])
                {
                    freq_relay_timer[i].start();
                    osstream<<"Bus frequency relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                            <<"s due to bus frequency exceeding over bus frequency threshold: "<<freq<<" > "<<freq_th[i]<<endl;
                    show_information_with_leading_time_stamp(osstream);
                }
                else
                {
                    if(freq_th[i]<1.0 and freq<freq_th[i])
                    {
                        freq_relay_timer[i].start();
                        osstream<<"Bus frequency relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to bus frequency exceeding under bus frequency threshold: "<<freq<<" < "<<freq_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                }
            }

            if(freq_relay_timer[i].is_started())
            {
                if(freq_relay_timer[i].is_timed_out())
                {

                    osstream<<"Bus frequency relay timer of "<<get_device_name()<<" is timed out at "<<get_dynamic_simulation_time_in_s()<<" s"<<endl;
                    show_information_with_leading_time_stamp(osstream);
                    sim.trip_wt_generator(did, INFINITE_THRESHOLD);
                    sim.enable_relay_action_flag();
                }
                else
                {
                    if(freq_th[i]>1.0 and freq<freq_th[i])
                    {
                        freq_relay_timer[i].reset();
                        osstream<<"Bus frequency relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to bus frequency less than over bus frequency threshold: "<<freq<<" < "<<freq_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                    else
                    {
                        if(freq_th[i]<1.0 and freq>freq_th[i])
                        {
                            freq_relay_timer[i].reset();
                            osstream<<"Bus frequency relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                    <<"s due to bus frequency greater than under bus frequency threshold: "<<freq<<" > "<<freq_th[i]<<endl;
                            show_information_with_leading_time_stamp(osstream);
                        }
                    }
                }
            }
        }
    }
}

void WTRLY0::check_bus_voltage_relay()
{
    ostringstream osstream;

    WT_GENERATOR* wtgen = (WT_GENERATOR*) get_device_pointer();
    bool status = wtgen->get_status();
    if(status==false)
        return;

    DEVICE_ID did = get_device_id();

    DYNAMICS_SIMULATOR& sim = get_default_dynamic_simulator();

    double volt = get_bus_voltage_in_pu();
    if(volt>2.0)
        return;

    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(volt_th[i])>FLOAT_EPSILON and fabs(volt_th[i]-1.0)>FLOAT_EPSILON)
        {
            if(not volt_relay_timer[i].is_started())
            {
                if(volt_th[i]>1.0 and volt>volt_th[i])
                {
                    volt_relay_timer[i].start();
                    osstream<<"Bus voltage relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                            <<"s due to bus voltage exceeding over bus voltage threshold: "<<volt<<" > "<<volt_th[i]<<endl;
                    show_information_with_leading_time_stamp(osstream);
                }
                else
                {
                    if(volt_th[i]<1.0 and volt<volt_th[i])
                    {
                        volt_relay_timer[i].start();
                        osstream<<"Bus voltage relay timer of "<<get_device_name()<<" is started at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to bus voltage exceeding under bus voltage threshold: "<<volt<<" < "<<volt_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                }
            }

            if(volt_relay_timer[i].is_started())
            {
                if(volt_relay_timer[i].is_timed_out())
                {

                    osstream<<"Bus voltage relay timer of "<<get_device_name()<<" is timed out at "<<get_dynamic_simulation_time_in_s()<<" s"<<endl;
                    show_information_with_leading_time_stamp(osstream);
                    sim.trip_wt_generator(did, INFINITE_THRESHOLD);
                    sim.enable_relay_action_flag();
                }
                else
                {
                    if(volt_th[i]>1.0 and volt<volt_th[i])
                    {
                        volt_relay_timer[i].reset();
                        osstream<<"Bus voltage relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                <<"s due to bus voltage less than over bus voltage threshold: "<<volt<<" < "<<volt_th[i]<<endl;
                        show_information_with_leading_time_stamp(osstream);
                    }
                    else
                    {
                        if(volt_th[i]<1.0 and volt>volt_th[i])
                        {
                            volt_relay_timer[i].reset();
                            osstream<<"Bus voltage relay timer of "<<get_device_name()<<" is reset at "<<get_dynamic_simulation_time_in_s()
                                    <<"s due to bus voltage greater than under bus voltage threshold: "<<volt<<" > "<<volt_th[i]<<endl;
                            show_information_with_leading_time_stamp(osstream);
                        }
                    }
                }
            }
        }
    }
}

void WTRLY0::check()
{
    ;
}

void WTRLY0::report()
{
    ostringstream osstream;
    osstream<<get_standard_model_string();
    show_information_with_leading_time_stamp(osstream);
}

void WTRLY0::save()
{
    ;
}
string WTRLY0::get_standard_model_string() const
{
    ostringstream osstream;

    DEVICE_ID did = get_device_id();
    size_t bus = did.get_device_terminal().get_buses()[0];
    string identifier = did.get_device_identifier();


    osstream<<setw(8)<<bus<<", "
      <<"'"<<get_model_name()<<"', "
      <<"'"<<identifier<<"', ";
    size_t n=0;
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(vwind_th[i])<FLOAT_EPSILON and fabs(vwind_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
            ++n;
    }
    osstream<<setw(8)<<n<<", ";
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(vwind_th[i])<FLOAT_EPSILON and fabs(vwind_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
        {
            osstream<<setw(8)<<setprecision(6)<<vwind_th[i]<<", ";
            osstream<<setw(8)<<setprecision(6)<<vwind_relay_timer[i].get_timer_interval_in_s()<<", ";
        }
    }

    n = 0;
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(speed_th[i])<FLOAT_EPSILON and fabs(speed_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
            ++n;
    }
    osstream<<setw(8)<<n<<", ";
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(speed_th[i])<FLOAT_EPSILON and fabs(speed_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
        {
            osstream<<setw(8)<<setprecision(6)<<speed_th[i]<<", ";
            osstream<<setw(8)<<setprecision(6)<<speed_relay_timer[i].get_timer_interval_in_s()<<", ";
        }
    }

    n = 0;
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(freq_th[i])<FLOAT_EPSILON and fabs(freq_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
            ++n;
    }
    osstream<<setw(8)<<n<<", ";
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(freq_th[i])<FLOAT_EPSILON and fabs(freq_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
        {
            osstream<<setw(8)<<setprecision(6)<<freq_th[i]<<", ";
            osstream<<setw(8)<<setprecision(6)<<freq_relay_timer[i].get_timer_interval_in_s()<<", ";
        }
    }

    n = 0;
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(volt_th[i])<FLOAT_EPSILON and fabs(volt_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
            ++n;
    }
    osstream<<setw(8)<<n;
    for(size_t i=0; i<MAX_RELAY_COUNT; ++i)
    {
        if(fabs(volt_th[i])<FLOAT_EPSILON and fabs(volt_th[i]-1.0)<FLOAT_EPSILON)
            continue;
        else
        {
            osstream<<", "<<setw(8)<<setprecision(6)<<volt_th[i];
            osstream<<", "<<setw(8)<<setprecision(6)<<volt_relay_timer[i].get_timer_interval_in_s();
        }
    }
    osstream<<" /";
    return osstream.str();
}

void WTRLY0::prepare_model_data_table()
{
    clear_model_data_table();
    size_t i=1;
    //add_model_data_name_and_index_pair("TURBINE INERTIA", i); i++; /*1*/
}

double WTRLY0::get_model_data_with_name(string par_name) const
{
    par_name = string2upper(par_name);
    if(is_model_data_exist(par_name))
    {
        //if(par_name=="TURBINE INERTIA") return get_Hturbine_in_s();
        return 0.0;
    }
    else
    {
        show_set_get_model_data_with_name_error(get_device_name(), get_model_name(), __FUNCTION__, par_name);
        return 0.0;
    }
}

void WTRLY0::set_model_data_with_name(string par_name, double value)
{
    par_name = string2upper(par_name);
    if(is_model_data_exist(par_name))
    {
        //if(par_name=="TURBINE INERTIA") return set_Hturbine_in_s(value);
    }
    else
    {
        show_set_get_model_data_with_name_error(get_device_name(), get_model_name(), __FUNCTION__, par_name);
        return;
    }
}


void WTRLY0::prepare_model_internal_variable_table()
{
    clear_model_internal_variable_table();
    size_t i=1;
    //add_model_inernal_variable_name_and_index_pair("STATE@TURBINE SPEED BLOCK", i); i++;
}

double WTRLY0::get_model_internal_variable_with_name(string var_name)
{
    var_name = string2upper(var_name);
    //if(var_name=="STATE@TURBINE SPEED BLOCK") return turbine_inertia_block.get_state();

    return 0.0;
}

string WTRLY0::get_dynamic_data_in_psse_format() const
{
    return "";
}

string WTRLY0::get_dynamic_data_in_bpa_format() const
{
    return get_dynamic_data_in_psse_format();
}

string WTRLY0::get_dynamic_data_in_steps_format() const
{
    return get_dynamic_data_in_psse_format();
}
