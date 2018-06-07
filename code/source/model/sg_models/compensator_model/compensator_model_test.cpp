#include "header/model/sg_models/compensator_model/compensator_model_test.h"
#include "header/model/sg_models/sync_generator_model/genrou.h"
#include "header/basic/utility.h"
#include "header/steps_namespace.h"

using namespace std;
COMPENSATOR_MODEL_TEST::COMPENSATOR_MODEL_TEST()
{
    TEST_ADD(COMPENSATOR_MODEL_TEST::test_get_generator_terminal_voltage);
    TEST_ADD(COMPENSATOR_MODEL_TEST::test_get_generator_terminal_current);
}


void COMPENSATOR_MODEL_TEST::setup()
{
    SG_MODEL_TEST::setup();

    GENERATOR* genptr = get_test_generator();

    GENROU genmodel;
    genmodel.set_Rs(0.01);
    genmodel.set_Xd(0.5);
    genmodel.set_Xq(0.4);
    genmodel.set_Xdp(0.1);
    genmodel.set_Xqp(0.2);
    genmodel.set_Xpp(0.04);
    genmodel.set_Xl(0.01);
    genmodel.set_Td0p_in_s(0.5);
    genmodel.set_Tq0p_in_s(0.4);
    genmodel.set_Td0pp_in_s(0.04);
    genmodel.set_Tq0pp_in_s(0.03);
    genmodel.set_Tj_in_s(6.0);
    genmodel.set_D(6.0);
    genmodel.set_saturation_at_1(0.1);
    genmodel.set_saturation_at_1p2(0.5);

    genptr->set_model(&genmodel);
}

void COMPENSATOR_MODEL_TEST::tear_down()
{
    SG_MODEL_TEST::tear_down();

    show_test_end_information();
}

void COMPENSATOR_MODEL_TEST::apply_voltage_drop_of_10_percent()
{
    POWER_SYSTEM_DATABASE* psdb = get_test_power_system_database();
    BUS* bus = psdb->get_bus(1);
    bus->set_voltage_in_pu(bus->get_voltage_in_pu()-0.1);
}


void COMPENSATOR_MODEL_TEST::export_meter_title()
{
    ostringstream osstream;
    osstream<<"TIME\tVOLT\tCURRENT\tECOMP";
    show_information_with_leading_time_stamp(osstream);
}

void COMPENSATOR_MODEL_TEST::export_meter_values()
{
    ostringstream osstream;

    COMPENSATOR_MODEL* model = get_test_compensator_model();

    double voltage = abs(model->get_generator_terminal_voltage_in_pu());
    double current = abs(model->get_generator_terminal_current_in_pu());
    double ecomp = model->get_compensated_voltage_in_pu();
    osstream<<setw(6)<<setprecision(3)<<fixed<<STEPS::TIME<<"\t"
      <<setw(10)<<setprecision(6)<<fixed<<voltage<<"\t"
      <<setw(10)<<setprecision(6)<<fixed<<current<<"\t"
      <<setw(10)<<setprecision(6)<<fixed<<ecomp;
    show_information_with_leading_time_stamp(osstream);
}

void COMPENSATOR_MODEL_TEST::initialize_models()
{
    ostringstream oosstream;
    double delt = 0.001;
    set_dynamic_simulation_time_step_in_s(delt);

    GENERATOR* genptr = get_test_generator();
    COMPENSATOR_MODEL* model = get_test_compensator_model();

    oosstream<<"Model:"<<model->get_standard_model_string()<<endl;
    show_information_with_leading_time_stamp(oosstream);

    SYNC_GENERATOR_MODEL* genmodel = genptr->get_sync_generator_model();
    genmodel->initialize();

    STEPS::TIME = -delt*2.0;

    model->initialize();

    export_meter_title();
    export_meter_values();
}
void COMPENSATOR_MODEL_TEST::update_models()
{
    COMPENSATOR_MODEL* model = get_test_compensator_model();
    SYNC_GENERATOR_MODEL* genmodel = get_test_sync_generator_model();
    genmodel->run(UPDATE_MODE);
    model->run(UPDATE_MODE);
}

void COMPENSATOR_MODEL_TEST::run_to_time(double tend)
{
    double delt = get_dynamic_simulation_time_step_in_s();

    COMPENSATOR_MODEL* model = get_test_compensator_model();
    SYNC_GENERATOR_MODEL* genmodel = get_test_sync_generator_model();
    double ecomp;
    while(true)
    {
        STEPS::TIME += delt;
        if(STEPS::TIME>tend+FLOAT_EPSILON)
        {
            STEPS::TIME -=delt;
            break;
        }
        ecomp = model->get_compensated_voltage_in_pu();
        while(true)
        {
            genmodel->run(INTEGRATE_MODE);
            model->run(INTEGRATE_MODE);
            if(fabs(ecomp-model->get_compensated_voltage_in_pu())>1e-6)
                ecomp = model->get_compensated_voltage_in_pu();
            else
                break;
        }
        genmodel->run(UPDATE_MODE);
        model->run(UPDATE_MODE);

        export_meter_values();
    }
}


void COMPENSATOR_MODEL_TEST::run_step_response_of_compensator_model()
{
    initialize_models();
    run_to_time(1.0);
    apply_voltage_drop_of_10_percent();
    update_models();
    run_to_time(6.0);
}

void COMPENSATOR_MODEL_TEST::test_get_generator_terminal_voltage()
{
    show_test_information_for_function_of_class(__FUNCTION__,"COMPENSATOR_MODEL_TEST");

    GENERATOR* genptr = get_test_generator();
    POWER_SYSTEM_DATABASE* psdb = get_test_power_system_database();
    COMP model;
    model.set_power_system_database(psdb);
    model.set_device_id(genptr->get_device_id());
    TEST_ASSERT(model.get_generator_terminal_voltage_in_pu()==1.0);
}


void COMPENSATOR_MODEL_TEST::test_get_generator_terminal_current()
{
    show_test_information_for_function_of_class(__FUNCTION__,"COMPENSATOR_MODEL_TEST");

    GENERATOR* genptr = get_test_generator();
    POWER_SYSTEM_DATABASE* psdb = get_test_power_system_database();

    (genptr->get_sync_generator_model())->initialize();

    COMP model;
    model.set_power_system_database(psdb);
    model.set_device_id(genptr->get_device_id());

    TEST_ASSERT(abs(model.get_generator_terminal_current_in_pu()-complex<double>(1.0,-0.3)*0.5)<FLOAT_EPSILON);
}

