#include "header/toolkit/cct_searcher/cct_searcher_test.h"
#include "header/basic/utility.h"
#include "header/data_imexporter/psse_imexporter.h"
#include "header/prepare_for_tests/prepare_models_for_test.h"
#include "header/meter/meter_setter.h"
#include "header/steps_namespace.h"
#include "header/toolkit/powerflow_solver/powerflow_solver.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

CCT_SEARCHER_TEST::CCT_SEARCHER_TEST()
{
    TEST_ADD(CCT_SEARCHER_TEST::test_constructor);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_and_get_power_system_database_maximum_bus_number);

    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_search_title);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_powerflow_data_filename);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_dynamic_data_filename);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_fault_device);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_fault_side_bus);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_fault_location_to_fault_bus);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_fault_shunt);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_fault_time);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_minimum_clearint_time);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_maximum_clearint_time);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_flag_trip_line_after_clearing_fault);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_simulation_time_span);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_angle_difference_threshold);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_simulator_max_iteration);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_simulator_allowed_max_power_imbalance_in_MVA);
    TEST_ADD(CCT_SEARCHER_TEST::test_set_get_simulator_iteration_accelerator);

    TEST_ADD(CCT_SEARCHER_TEST::test_seach_cct_for_IEEE_9_bus_model_classic);
}

void CCT_SEARCHER_TEST::setup()
{
    searcher = new CCT_SEARCHER();

    set_dynamic_simulation_time_step_in_s(0.01);
}

void CCT_SEARCHER_TEST::tear_down()
{
    delete searcher;

    show_test_end_information();
}

void CCT_SEARCHER_TEST::test_constructor()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    TEST_ASSERT(searcher->get_power_system_database_maximum_bus_number()==10000);
    TEST_ASSERT(searcher->get_search_title()=="CCT_SEARCH");
    TEST_ASSERT(searcher->get_powerflow_data_filename()=="");
    TEST_ASSERT(searcher->get_dynamic_data_filename()=="");
    TEST_ASSERT(searcher->get_fault_device().is_valid()==false);
    TEST_ASSERT(searcher->get_fault_side_bus()==0);
    TEST_ASSERT(fabs(searcher->get_fault_location_to_fault_side_bus_in_pu()-0.0)<FLOAT_EPSILON);
    TEST_ASSERT(abs(searcher->get_fault_shunt_in_pu())<FLOAT_EPSILON);
    TEST_ASSERT(fabs(searcher->get_fault_time_in_s()-0.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(searcher->get_minimum_clearing_time_in_s()-0.1)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(searcher->get_maximum_clearing_time_in_s()-1.5)<FLOAT_EPSILON);
    TEST_ASSERT(searcher->get_flag_trip_line_after_clearing_fault()==false);
    TEST_ASSERT(fabs(searcher->get_simulation_time_span_in_s()-5.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(searcher->get_angle_difference_threshold_in_deg()-170.0)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(searcher->get_simulator_allowed_max_power_imbalance_in_MVA()-0.0001)<FLOAT_EPSILON);
    TEST_ASSERT(fabs(searcher->get_simulator_iteration_accelerator()-1.0)<FLOAT_EPSILON);
    TEST_ASSERT(searcher->get_simulator_max_iteration()==200);
}

void CCT_SEARCHER_TEST::test_set_and_get_power_system_database_maximum_bus_number()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    TEST_ASSERT(searcher->get_power_system_database_maximum_bus_number()==10000);

    searcher->set_power_system_database_maximum_bus_number(1000);

    TEST_ASSERT(searcher->get_power_system_database_maximum_bus_number()==1000);
}


void CCT_SEARCHER_TEST::test_set_get_search_title()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_search_title("CCT_SEARCH_DEMO_SYSTEM");

    TEST_ASSERT(searcher->get_search_title()=="CCT_SEARCH_DEMO_SYSTEM");
}

void CCT_SEARCHER_TEST::test_set_get_powerflow_data_filename()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_powerflow_data_filename("abc.raw");

    TEST_ASSERT(searcher->get_powerflow_data_filename()=="abc.raw");
}

void CCT_SEARCHER_TEST::test_set_get_dynamic_data_filename()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_dynamic_data_filename("abc.dyr");

    TEST_ASSERT(searcher->get_dynamic_data_filename()=="abc.dyr");
}

void CCT_SEARCHER_TEST::test_set_get_fault_device()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    terminal.append_bus(1);
    terminal.append_bus(2);
    did.set_device_terminal(terminal);
    did.set_device_identifier("#1");

    searcher->set_fault_device(did);

    TEST_ASSERT(searcher->get_fault_device()==did);
}

void CCT_SEARCHER_TEST::test_set_get_fault_side_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_fault_side_bus(2);

    TEST_ASSERT(searcher->get_fault_side_bus()==2);
}

void CCT_SEARCHER_TEST::test_set_get_fault_location_to_fault_bus()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_fault_location_to_fault_side_bus_in_pu(0.2);

    TEST_ASSERT(fabs(searcher->get_fault_location_to_fault_side_bus_in_pu()-0.2)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_fault_shunt()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    complex<double> shunt(0.01, 1.0e8);
    searcher->set_fault_shunt_in_pu(shunt);

    TEST_ASSERT(abs(searcher->get_fault_shunt_in_pu()-shunt)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_fault_time()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_fault_time_in_s(0.1);

    TEST_ASSERT(abs(searcher->get_fault_time_in_s()-0.1)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_minimum_clearint_time()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_minimum_clearing_time_in_s(0.1);

    TEST_ASSERT(abs(searcher->get_minimum_clearing_time_in_s()-0.1)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_maximum_clearint_time()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_maximum_clearing_time_in_s(1.0);

    TEST_ASSERT(abs(searcher->get_maximum_clearing_time_in_s()-1.0)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_flag_trip_line_after_clearing_fault()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_flag_trip_line_after_clearing_fault(false);

    TEST_ASSERT(searcher->get_flag_trip_line_after_clearing_fault()==false);

    searcher->set_flag_trip_line_after_clearing_fault(true);

    TEST_ASSERT(searcher->get_flag_trip_line_after_clearing_fault()==true);
}

void CCT_SEARCHER_TEST::test_set_get_simulation_time_span()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_simulation_time_span_in_s(5.0);

    TEST_ASSERT(abs(searcher->get_simulation_time_span_in_s()-5.0)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_angle_difference_threshold()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_angle_difference_threshold_in_deg(180.0);

    TEST_ASSERT(abs(searcher->get_angle_difference_threshold_in_deg()-180.0)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_simulator_max_iteration()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_simulator_max_iteration(20);

    TEST_ASSERT(searcher->get_simulator_max_iteration()==20);
}

void CCT_SEARCHER_TEST::test_set_get_simulator_allowed_max_power_imbalance_in_MVA()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_simulator_allowed_max_power_imbalance_in_MVA(0.01);

    TEST_ASSERT(abs(searcher->get_simulator_allowed_max_power_imbalance_in_MVA()-0.01)<FLOAT_EPSILON);
}

void CCT_SEARCHER_TEST::test_set_get_simulator_iteration_accelerator()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    searcher->set_simulator_iteration_accelerator(0.8);

    TEST_ASSERT(abs(searcher->get_simulator_iteration_accelerator()-0.8)<FLOAT_EPSILON);
}


void CCT_SEARCHER_TEST::test_seach_cct_for_IEEE_9_bus_model_classic()
{
    show_test_information_for_function_of_class(__FUNCTION__,"CCT_SEARCHER_TEST");

    ostringstream osstream;

    string file = "test_log/";
    file += __FUNCTION__;
    file += ".txt";
    redirect_stdout_to_file(file);

    //searcher->set_search_title("CCT_SEARCH_IEEE9_CLASSIC_FAULT_AT_LINE_7_5");
    searcher->set_search_title("");
    searcher->set_powerflow_data_filename("IEEE9_classical.raw");
    searcher->set_dynamic_data_filename("IEEE9_classical.dyr");

    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    terminal.append_bus(5);
    terminal.append_bus(7);
    did.set_device_terminal(terminal);
    did.set_device_identifier("1");
    searcher->set_fault_device(did);

    searcher->set_fault_side_bus(7);
    searcher->set_fault_location_to_fault_side_bus_in_pu(0.0);
    searcher->set_fault_shunt_in_pu(complex<double>(0.0, -2e8));
    searcher->set_flag_trip_line_after_clearing_fault(false);

    double cct = searcher->search_cct();

    osstream<<"Searched CCT is: "<<cct<<" s"<<endl;
    show_information_with_leading_time_stamp(osstream);

    recover_stdout();
}
