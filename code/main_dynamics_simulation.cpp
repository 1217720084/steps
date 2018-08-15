#include <istream>
#include <iostream>
#include "header/power_system_database.h"
#include "header/toolkit/dynamic_simulator/dynamic_simulator.h"
#include "header/toolkit/powerflow_solver/powerflow_solver.h"
#include "header/basic/utility.h"
#include "header/data_imexporter/psse_imexporter.h"
#include "header/prepare_for_tests/prepare_models_for_test.h"
using namespace std;

int main()
{
    initialize_simulator(); // this function should be called first

    POWER_SYSTEM_DATABASE* db;
    DYNAMICS_SIMULATOR* simulator;

    db = new POWER_SYSTEM_DATABASE;
    simulator = new DYNAMICS_SIMULATOR(db);

    db->set_allowed_max_bus_number(1000);

    set_dynamic_simulation_time_step_in_s(0.01);
    simulator->set_allowed_max_power_imbalance_in_MVA(0.01);
    simulator->set_max_DAE_iteration(200);
    simulator->set_max_network_iteration(1);
    simulator->set_iteration_accelerator(0.8);

    PSSE_IMEXPORTER importer;

    importer.set_power_system_database(db);
    //importer.load_powerflow_data("IEEE39.raw");
    //importer.load_dynamic_data("IEEE39_GENROU_SEXS_IEEEG1.dyr");
    importer.load_powerflow_data("bench_shandong_v2.raw");
    importer.load_dynamic_data("bench_shandong_v2.dyr");
    //importer.load_dynamic_data("bench_shandong_with_avr.dyr");

    POWERFLOW_SOLVER powerflow_solver;

    powerflow_solver.set_power_system_database(db);

    powerflow_solver.set_max_iteration(30);
    powerflow_solver.set_allowed_max_active_power_imbalance_in_MW(0.00001);
    powerflow_solver.set_allowed_max_reactive_power_imbalance_in_MVar(0.00001);
    powerflow_solver.set_flat_start_logic(false);
    powerflow_solver.set_transformer_tap_adjustment_logic(true);

    powerflow_solver.solve_with_fast_decoupled_solution();

    powerflow_solver.show_powerflow_result();

    simulator->prepare_meters();
    //simulator->prepare_hvdc_related_meters();

    //simulator->set_output_file("test_log/IEEE_39_bus_model_GENROU_SEXS_IEEEG1_load_scale_down_at_bus_3_by_10%");
    //simulator->set_output_file("test_log/IEEE_39_bus_model_GENROU_SEXS_IEEEG1_generation_scale_down_at_bus_38_by_10%");
    //simulator->set_output_file("test_log/IEEE_39_bus_model_GENROU_SEXS_IEEEG1_trip_bus_");
    //simulator->set_output_file("test_log/bench_shandong_with_avr_fault_at_line_82_60");
    simulator->set_output_file("test_log/bench_shandong_with_avr_fault_at_line_82_80");
    //simulator->set_output_file("test_log/bench_shandong_with_avr_trip_mac_140");

    simulator->start();
    simulator->run_to(1.0);

    /*DEVICE_ID did;
    did.set_device_type("LOAD");
    TERMINAL terminal;
    terminal.append_bus(3);
    did.set_device_terminal(terminal);
    did.set_device_identifier("1");

    simulator->scale_load(did, -0.1);
    */

    /*did.set_device_type("GENERATOR");
    terminal.clear();
    terminal.append_bus(38);
    did.set_device_terminal(terminal);
    did.set_device_identifier("1");

    simulator->shed_generator(did, 0.1);
    */


    DEVICE_ID did;
    did.set_device_type("LINE");
    TERMINAL terminal;
    terminal.append_bus(82);
    terminal.append_bus(80);
    did.set_device_terminal(terminal);
    did.set_device_identifier("1");

    simulator->set_line_fault(did, 82, 0.0, complex<double>(0.0, -1e4));

    simulator->run_to(1.35);

    simulator->clear_line_fault(did, 82, 0.0);
/*
    DEVICE_ID did;
    did.set_device_type("GENERATOR");
    TERMINAL terminal;
    terminal.append_bus(140);
    did.set_device_terminal(terminal);
    did.set_device_identifier("1");

    simulator->trip_generator(did);
*/

    simulator->run_to(5.0);

    delete simulator;

    delete db;

    terminate_simulator();

    return 0;
}
