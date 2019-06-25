from ctypes import *
import platform
import os

libsteps_version = "0.5.0"
libsteps_date = "2019/05/15"

def get_base_library():
    dirname, filename = os.path.split(os.path.abspath(__file__))
    dirname = dirname.replace('\\','/')
    if not dirname.endswith('/'):
        dirname = dirname + '/'
    
    libsteps_name = 'libSTEPS'
    libsteps_extension = '.so'
    if platform.system()=="Linux" or platform.system()=="Unix":
        libsteps_extension = '.so'
    elif platform.system()=="Windows":
        libsteps_extension = '.dll'
        
    library = dirname+libsteps_name+libsteps_extension
    if not os.path.exists(library):
        library = dirname+libsteps_name+libsteps_extension
        if not os.path.exists(library):
            library = None

    return library
    
def load_library():
    library = get_base_library()
    if library is not None:
        libsteps = cdll.LoadLibrary(library)
    else:
        return None

    libsteps.api_set_default_toolkit_log_file.restype = None
    libsteps.api_set_default_toolkit_log_file.argtype = (c_char_p, )
    
    libsteps.api_generate_new_toolkit.restype = c_uint
    libsteps.api_generate_new_toolkit.argtypes = None
    
    libsteps.api_delete_toolkit.restype = None
    libsteps.api_delete_toolkit.argtypes = (c_uint, )
    
    libsteps.api_initialize_toolkit.restype = None
    libsteps.api_initialize_toolkit.argtypes = (c_uint, )
    
    libsteps.api_clear_toolkit.restype = None
    libsteps.api_clear_toolkit.argtypes = (c_uint, )
    
    libsteps.api_get_toolkit_float_data.restype = c_double
    libsteps.api_get_toolkit_float_data.argtypes = (c_char_p, c_uint)
    
    libsteps.api_set_toolkit_float_data.restype = None
    libsteps.api_set_toolkit_float_data.argtypes = (c_char_p, c_double, c_uint)
    
    libsteps.api_get_toolkit_string_data.restype = c_char_p
    libsteps.api_get_toolkit_string_data.argtypes = (c_char_p, c_uint)
    
    libsteps.api_set_toolkit_string_data.restype = None
    libsteps.api_set_toolkit_string_data.argtypes = (c_char_p, c_char_p, c_uint)
    
    libsteps.api_get_toolkit_bool_data.restype = c_bool
    libsteps.api_get_toolkit_bool_data.argtypes = (c_char_p, c_uint)
    
    libsteps.api_set_toolkit_bool_data.restype = None
    libsteps.api_set_toolkit_bool_data.argtypes = (c_char_p, c_bool, c_uint)

    libsteps.api_load_powerflow_data_from_file.restype = None
    libsteps.api_load_powerflow_data_from_file.argtypes = (c_char_p, c_char_p, c_uint)
    libsteps.api_load_dynamic_data_from_file.restype = None
    libsteps.api_load_dynamic_data_from_file.argtypes = (c_char_p, c_char_p, c_uint)

    libsteps.api_save_powerflow_data_to_file.restype = None
    libsteps.api_save_powerflow_data_to_file.argtypes = (c_char_p, c_char_p, c_bool, c_uint)
    libsteps.api_save_dynamic_data_to_file.restype = None
    libsteps.api_save_dynamic_data_to_file.argtypes = (c_char_p, c_char_p, c_uint)
    
    libsteps.api_check_network_connectivity.restype = None
    libsteps.api_check_network_connectivity.argtypes = (c_bool, c_uint)

    libsteps.api_get_allowed_maximum_bus_number.restype = c_uint
    libsteps.api_get_allowed_maximum_bus_number.argtypes = (c_uint, )

    libsteps.api_set_allowed_maximum_bus_number.restype = None
    libsteps.api_set_allowed_maximum_bus_number.argtypes = (c_uint, c_uint)

    libsteps.api_get_device_capacity.restype = c_uint
    libsteps.api_get_device_capacity.argtypes = (c_char_p, c_uint)
    libsteps.api_get_area_capacity.restype = c_uint
    libsteps.api_get_area_capacity.argtypes = (c_uint, )
    libsteps.api_get_zone_capacity.restype = c_uint
    libsteps.api_get_zone_capacity.argtypes = (c_uint, )
    libsteps.api_get_owner_capacity.restype = c_uint
    libsteps.api_get_owner_capacity.argtypes = (c_uint, )

    libsteps.api_set_device_capacity.restype = None
    libsteps.api_set_device_capacity.argtypes = (c_char_p, c_uint, c_uint)
    libsteps.api_set_area_capacity.restype = None
    libsteps.api_set_area_capacity.argtypes = (c_uint,  c_uint)
    libsteps.api_set_zone_capacity.restype = None
    libsteps.api_set_zone_capacity.argtypes = (c_uint,  c_uint)
    libsteps.api_set_owner_capacity.restype = None
    libsteps.api_set_owner_capacity.argtypes = (c_uint,  c_uint)

    libsteps.api_get_device_count.restype = c_uint
    libsteps.api_get_device_count.argtypes = (c_char_p, c_uint)
    libsteps.api_get_area_count.restype = c_uint
    libsteps.api_get_area_count.argtypes = (c_uint, )
    libsteps.api_get_zone_count.restype = c_uint
    libsteps.api_get_zone_count.argtypes = (c_uint, )
    libsteps.api_get_owner_count.restype = c_uint
    libsteps.api_get_owner_count.argtypes = (c_uint, )
    libsteps.api_get_in_service_bus_count.restype = c_uint
    libsteps.api_get_in_service_bus_count.argtypes = (c_uint, )
    libsteps.api_update_overshadowed_buses.restype = None
    libsteps.api_update_overshadowed_buses.argtypes = (c_uint, )
    libsteps.api_set_all_buses_un_overshadowed.restype = None
    libsteps.api_set_all_buses_un_overshadowed.argtypes = (c_uint, )
    libsteps.api_get_overshadowed_bus_count.restype = c_uint
    libsteps.api_get_overshadowed_bus_count.argtypes = (c_uint, )

    libsteps.api_is_bus_exist.restype = c_bool
    libsteps.api_is_bus_exist.argtypes = (c_uint, c_uint)
    libsteps.api_is_generator_exist.restype = c_bool
    libsteps.api_is_generator_exist.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_is_wt_generator_exist.restype = c_bool
    libsteps.api_is_wt_generator_exist.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_is_pv_unit_exist.restype = c_bool
    libsteps.api_is_pv_unit_exist.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_is_energy_storage_exist.restype = c_bool
    libsteps.api_is_energy_storage_exist.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_is_load_exist.restype = c_bool
    libsteps.api_is_load_exist.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_is_fixed_shunt_exist.restype = c_bool
    libsteps.api_is_fixed_shunt_exist.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_is_line_exist.restype = c_bool
    libsteps.api_is_line_exist.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_is_transformer_exist.restype = c_bool
    libsteps.api_is_transformer_exist.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_is_hvdc_exist.restype = c_bool
    libsteps.api_is_hvdc_exist.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_is_equivalent_device_exist.restype = c_bool
    libsteps.api_is_equivalent_device_exist.argtypes = (c_uint, c_char_p, c_uint)

    libsteps.api_show_device_data.restype = None
    libsteps.api_show_device_data.argtypes = (c_char_p, c_uint)

    libsteps.api_bus_number2bus_name.restype = c_char_p
    libsteps.api_bus_number2bus_name.argtypes = (c_uint, c_uint)
    libsteps.api_bus_name2bus_number.restype = c_uint
    libsteps.api_bus_name2bus_number.argtypes = (c_char_p, c_uint)

    libsteps.api_initialize_bus_search.restype = None
    libsteps.api_initialize_bus_search.argtypes = (c_double, c_double, c_double, c_double, c_uint, c_uint, c_uint, c_uint)
    libsteps.api_initialize_all_bus_search.restype = None
    libsteps.api_initialize_all_bus_search.argtypes = (c_uint, )

    libsteps.api_get_current_bus_number.restype = c_uint
    libsteps.api_get_current_bus_number.argtypes = (c_uint, )

    libsteps.api_goto_next_bus.restype = None
    libsteps.api_goto_next_bus.argtypes = (c_uint, )

    libsteps.api_initialize_device_search.restype = None
    libsteps.api_initialize_device_search.argtypes = (c_char_p, c_uint, c_uint)

    libsteps.api_get_current_device_bus_number.restype = c_uint
    libsteps.api_get_current_device_bus_number.argtypes = (c_char_p, c_char_p, c_uint)

    libsteps.api_get_current_device_identifier.restype = c_char_p
    libsteps.api_get_current_device_identifier.argtypes = (c_char_p, c_uint)

    libsteps.api_goto_next_device.restype = None
    libsteps.api_goto_next_device.argtypes = (c_char_p, c_uint)

    libsteps.api_initialize_area_search.restype = None
    libsteps.api_initialize_area_search.argtypes = (c_uint, )

    libsteps.api_get_current_area_number.restype = c_uint
    libsteps.api_get_current_area_number.argtypes = (c_uint, )

    libsteps.api_goto_next_area.restype = None
    libsteps.api_goto_next_area.argtypes = (c_uint, )

    libsteps.api_initialize_zone_search.restype = None
    libsteps.api_initialize_zone_search.argtypes = (c_uint, )

    libsteps.api_get_current_zone_number.restype = c_uint
    libsteps.api_get_current_zone_number.argtypes = (c_uint, )

    libsteps.api_goto_next_zone.restype = None
    libsteps.api_goto_next_zone.argtypes = (c_uint, )

    libsteps.api_initialize_owner_search.restype = None
    libsteps.api_initialize_owner_search.argtypes = (c_uint, )

    libsteps.api_get_current_owner_number.restype = c_uint
    libsteps.api_get_current_owner_number.argtypes = (c_uint, )

    libsteps.api_goto_next_owner.restype = None
    libsteps.api_goto_next_owner.argtypes = (c_uint, )

    libsteps.api_add_bus.restype = None
    libsteps.api_add_bus.argtypes = (c_uint, c_char_p, c_double, c_uint)
    libsteps.api_add_generator.restype = None
    libsteps.api_add_generator.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_wt_generator.restype = None
    libsteps.api_add_wt_generator.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_pv_unit.restype = None
    libsteps.api_add_pv_unit.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_energy_storage.restype = None
    libsteps.api_add_energy_storage.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_load.restype = None
    libsteps.api_add_load.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_fixed_shunt.restype = None
    libsteps.api_add_fixed_shunt.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_line.restype = None
    libsteps.api_add_line.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_add_hvdc.restype = None
    libsteps.api_add_hvdc.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_add_transformer.restype = None
    libsteps.api_add_transformer.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_add_equivalent_device.restype = None
    libsteps.api_add_equivalent_device.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_area.restype = None
    libsteps.api_add_area.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_zone.restype = None
    libsteps.api_add_zone.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_add_owner.restype = None
    libsteps.api_add_owner.argtypes = (c_uint, c_char_p, c_uint)

    libsteps.api_remove_bus.restype = None
    libsteps.api_remove_bus.argtypes = (c_uint, c_uint)
    libsteps.api_remove_generator.restype = None
    libsteps.api_remove_generator.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_remove_wt_generator.restype = None
    libsteps.api_remove_wt_generator.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_remove_pv_unit.restype = None
    libsteps.api_remove_pv_unit.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_remove_energy_storage.restype = None
    libsteps.api_remove_energy_storage.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_remove_load.restype = None
    libsteps.api_remove_load.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_remove_fixed_shunt.restype = None
    libsteps.api_remove_fixed_shunt.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_remove_line.restype = None
    libsteps.api_remove_line.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_remove_hvdc.restype = None
    libsteps.api_remove_hvdc.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_remove_transformer.restype = None
    libsteps.api_remove_transformer.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_remove_equivalent_device.restype = None
    libsteps.api_remove_equivalent_device.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_remove_area.restype = None
    libsteps.api_remove_area.argtypes = (c_uint, c_uint)
    libsteps.api_remove_zone.restype = None
    libsteps.api_remove_zone.argtypes = (c_uint, c_uint)
    libsteps.api_remove_owner.restype = None
    libsteps.api_remove_owner.argtypes = (c_uint, c_uint)




    libsteps.api_get_bus_integer_data.restype = (c_int)
    libsteps.api_get_bus_integer_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_get_bus_float_data.restype = (c_double)
    libsteps.api_get_bus_float_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_get_bus_string_data.restype = (c_char_p)
    libsteps.api_get_bus_string_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_set_bus_integer_data.restype = None
    libsteps.api_set_bus_integer_data.argtypes = (c_uint, c_char_p, c_int, c_uint)
    libsteps.api_set_bus_float_data.restype = None
    libsteps.api_set_bus_float_data.argtypes = (c_uint, c_char_p, c_double, c_uint)
    libsteps.api_set_bus_string_data.restype = None
    libsteps.api_set_bus_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)

    libsteps.api_get_load_integer_data.restype = (c_int)
    libsteps.api_get_load_integer_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_load_float_data.restype = (c_double)
    libsteps.api_get_load_float_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_load_string_data.restype = (c_char_p)
    libsteps.api_get_load_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_load_boolean_data.restype = (c_bool)
    libsteps.api_get_load_boolean_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_set_load_integer_data.restype = None
    libsteps.api_set_load_integer_data.argtypes = (c_uint, c_char_p, c_char_p, c_int, c_uint)
    libsteps.api_set_load_float_data.restype = None
    libsteps.api_set_load_float_data.argtypes = (c_uint, c_char_p, c_char_p, c_double, c_uint)
    libsteps.api_set_load_string_data.restype = None
    libsteps.api_set_load_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_load_boolean_data.restype = None
    libsteps.api_set_load_boolean_data.argtypes = (c_uint, c_char_p, c_char_p, c_bool, c_uint)

    libsteps.api_get_source_integer_data.restype = (c_int)
    libsteps.api_get_source_integer_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_source_float_data.restype = (c_double)
    libsteps.api_get_source_float_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_source_string_data.restype = (c_char_p)
    libsteps.api_get_source_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_source_boolean_data.restype = (c_bool)
    libsteps.api_get_source_boolean_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_set_source_integer_data.restype = None
    libsteps.api_set_source_integer_data.argtypes = (c_uint, c_char_p, c_char_p, c_int, c_uint)
    libsteps.api_set_source_float_data.restype = None
    libsteps.api_set_source_float_data.argtypes = (c_uint, c_char_p, c_char_p, c_double, c_uint)
    libsteps.api_set_source_string_data.restype = None
    libsteps.api_set_source_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_source_boolean_data.restype = None
    libsteps.api_set_source_boolean_data.argtypes = (c_uint, c_char_p, c_char_p, c_bool, c_uint)

    libsteps.api_get_fixed_shunt_integer_data.restype = (c_int)
    libsteps.api_get_fixed_shunt_integer_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_fixed_shunt_float_data.restype = (c_double)
    libsteps.api_get_fixed_shunt_float_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_fixed_shunt_string_data.restype = (c_char_p)
    libsteps.api_get_fixed_shunt_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_fixed_shunt_boolean_data.restype = (c_bool)
    libsteps.api_get_fixed_shunt_boolean_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_set_fixed_shunt_integer_data.restype = None
    libsteps.api_set_fixed_shunt_integer_data.argtypes = (c_uint, c_char_p, c_char_p, c_int, c_uint)
    libsteps.api_set_fixed_shunt_float_data.restype = None
    libsteps.api_set_fixed_shunt_float_data.argtypes = (c_uint, c_char_p, c_char_p, c_double, c_uint)
    libsteps.api_set_fixed_shunt_string_data.restype = None
    libsteps.api_set_fixed_shunt_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_fixed_shunt_boolean_data.restype = None
    libsteps.api_set_fixed_shunt_boolean_data.argtypes = (c_uint, c_char_p, c_char_p, c_bool, c_uint)

    libsteps.api_get_line_integer_data.restype = (c_int)
    libsteps.api_get_line_integer_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_line_float_data.restype = (c_double)
    libsteps.api_get_line_float_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_line_string_data.restype = (c_char_p)
    libsteps.api_get_line_string_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_line_boolean_data.restype = (c_bool)
    libsteps.api_get_line_boolean_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_set_line_integer_data.restype = None
    libsteps.api_set_line_integer_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_int, c_uint)
    libsteps.api_set_line_float_data.restype = None
    libsteps.api_set_line_float_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_double, c_uint)
    libsteps.api_set_line_string_data.restype = None
    libsteps.api_set_line_string_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_line_boolean_data.restype = None
    libsteps.api_set_line_boolean_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_bool, c_uint)

    libsteps.api_get_transformer_integer_data.restype = (c_int)
    libsteps.api_get_transformer_integer_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_get_transformer_float_data.restype = (c_double)
    libsteps.api_get_transformer_float_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_get_transformer_string_data.restype = (c_char_p)
    libsteps.api_get_transformer_string_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_get_transformer_boolean_data.restype = (c_bool)
    libsteps.api_get_transformer_boolean_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_transformer_integer_data.restype = None
    libsteps.api_set_transformer_integer_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_int, c_uint)
    libsteps.api_set_transformer_float_data.restype = None
    libsteps.api_set_transformer_float_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)
    libsteps.api_set_transformer_string_data.restype = None
    libsteps.api_set_transformer_string_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_transformer_boolean_data.restype = None
    libsteps.api_set_transformer_boolean_data.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_bool, c_uint)

    libsteps.api_get_hvdc_integer_data.restype = (c_int)
    libsteps.api_get_hvdc_integer_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_get_hvdc_float_data.restype = (c_double)
    libsteps.api_get_hvdc_float_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_get_hvdc_string_data.restype = (c_char_p)
    libsteps.api_get_hvdc_string_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_get_hvdc_boolean_data.restype = (c_bool)
    libsteps.api_get_hvdc_boolean_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_hvdc_integer_data.restype = None
    libsteps.api_set_hvdc_integer_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_int, c_uint)
    libsteps.api_set_hvdc_float_data.restype = None
    libsteps.api_set_hvdc_float_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)
    libsteps.api_set_hvdc_string_data.restype = None
    libsteps.api_set_hvdc_string_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_hvdc_boolean_data.restype = None
    libsteps.api_set_hvdc_boolean_data.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_bool, c_uint)

    libsteps.api_get_area_integer_data.restype = (c_int)
    libsteps.api_get_area_integer_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_get_area_float_data.restype = (c_double)
    libsteps.api_get_area_float_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_get_area_string_data.restype = (c_char_p)
    libsteps.api_get_area_string_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_set_area_integer_data.restype = None
    libsteps.api_set_area_integer_data.argtypes = (c_uint, c_char_p, c_int, c_uint)
    libsteps.api_set_area_float_data.restype = None
    libsteps.api_set_area_float_data.argtypes = (c_uint, c_char_p, c_double, c_uint)
    libsteps.api_set_area_string_data.restype = None
    libsteps.api_set_area_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)

    libsteps.api_get_zone_integer_data.restype = (c_int)
    libsteps.api_get_zone_integer_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_get_zone_string_data.restype = (c_char_p)
    libsteps.api_get_zone_string_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_set_zone_integer_data.restype = None
    libsteps.api_set_zone_integer_data.argtypes = (c_uint, c_char_p, c_int, c_uint)
    libsteps.api_set_zone_string_data.restype = None
    libsteps.api_set_zone_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)

    libsteps.api_get_owner_integer_data.restype = (c_int)
    libsteps.api_get_owner_integer_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_get_owner_string_data.restype = (c_char_p)
    libsteps.api_get_owner_string_data.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_set_owner_integer_data.restype = None
    libsteps.api_set_owner_integer_data.argtypes = (c_uint, c_char_p, c_int, c_uint)
    libsteps.api_set_owner_string_data.restype = None
    libsteps.api_set_owner_string_data.argtypes = (c_uint, c_char_p, c_char_p, c_uint)

    libsteps.api_set_dynamic_model.restype = None
    libsteps.api_set_dynamic_model.argtypes = (c_char_p, c_char_p, c_uint)
    
    libsteps.api_get_generator_related_model_name.restype = c_char_p
    libsteps.api_get_generator_related_model_name.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_generator_related_model_float_parameter.restype = c_double
    libsteps.api_get_generator_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_generator_related_model_float_parameter.restype = None
    libsteps.api_set_generator_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)

    libsteps.api_get_wt_generator_related_model_name.restype = c_char_p
    libsteps.api_get_wt_generator_related_model_name.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_wt_generator_related_model_float_parameter.restype = c_double
    libsteps.api_get_wt_generator_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_wt_generator_related_model_float_parameter.restype = None
    libsteps.api_set_wt_generator_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)

    libsteps.api_get_pv_unit_related_model_name.restype = c_char_p
    libsteps.api_get_pv_unit_related_model_name.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_pv_unit_related_model_float_parameter.restype = c_double
    libsteps.api_get_pv_unit_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_pv_unit_related_model_float_parameter.restype = None
    libsteps.api_set_pv_unit_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)

    libsteps.api_get_load_related_model_name.restype = c_char_p
    libsteps.api_get_load_related_model_name.argtypes = (c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_load_related_model_float_parameter.restype = c_double
    libsteps.api_get_load_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_load_related_model_float_parameter.restype = None
    libsteps.api_set_load_related_model_float_parameter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)

    libsteps.api_get_line_related_model_name.restype = c_char_p
    libsteps.api_get_line_related_model_name.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_line_related_model_float_parameter.restype = c_double
    libsteps.api_get_line_related_model_float_parameter.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_line_related_model_float_parameter.restype = None
    libsteps.api_set_line_related_model_float_parameter.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)

    libsteps.api_get_hvdc_related_model_name.restype = c_char_p
    libsteps.api_get_hvdc_related_model_name.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_uint)
    libsteps.api_get_hvdc_related_model_float_parameter.restype = c_double
    libsteps.api_get_hvdc_related_model_float_parameter.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_set_hvdc_related_model_float_parameter.restype = None
    libsteps.api_set_hvdc_related_model_float_parameter.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_double, c_uint)


    libsteps.api_get_powerflow_solver_integer_parameter.restype = (c_uint)
    libsteps.api_get_powerflow_solver_integer_parameter.argtypes = (c_char_p, c_uint)
    libsteps.api_get_powerflow_solver_float_parameter.restype = (c_double)
    libsteps.api_get_powerflow_solver_float_parameter.argtypes = (c_char_p, c_uint)
    libsteps.api_get_powerflow_solver_boolean_parameter.restype = (c_bool)
    libsteps.api_get_powerflow_solver_boolean_parameter.argtypes = (c_char_p, c_uint)
    libsteps.api_set_powerflow_solver_integer_parameter.restype = None
    libsteps.api_set_powerflow_solver_integer_parameter.argtypes = (c_char_p, c_int, c_uint)
    libsteps.api_set_powerflow_solver_float_parameter.restype = None
    libsteps.api_set_powerflow_solver_float_parameter.argtypes = (c_char_p, c_double, c_uint)
    libsteps.api_set_powerflow_solver_boolean_parameter.restype = None
    libsteps.api_set_powerflow_solver_boolean_parameter.argtypes = (c_char_p, c_bool, c_uint)

    libsteps.api_solve_powerflow.restype = None
    libsteps.api_solve_powerflow.argtypes = (c_char_p, c_uint)
    libsteps.api_is_powerflow_converged.restype = (c_bool)
    libsteps.api_is_powerflow_converged.argtypes = (c_uint, )
    libsteps.api_show_powerflow_result.restype = None
    libsteps.api_show_powerflow_result.argtypes = (c_uint, )
    libsteps.api_save_powerflow_result.restype = None
    libsteps.api_save_powerflow_result.argtypes = (c_char_p, c_uint)
    libsteps.api_save_extended_powerflow_result.restype = None
    libsteps.api_save_extended_powerflow_result.argtypes = (c_char_p, c_uint)
    libsteps.api_save_jacobian_matrix.restype = None
    libsteps.api_save_jacobian_matrix.argtypes = (c_char_p, c_uint)

    libsteps.api_build_network_matrix.restype = None
    libsteps.api_build_network_matrix.argtypes = (c_uint, )
    libsteps.api_build_decoupled_network_matrix.restype = None
    libsteps.api_build_decoupled_network_matrix.argtypes = (c_uint, )
    libsteps.api_build_dc_network_matrix.restype = None
    libsteps.api_build_dc_network_matrix.argtypes = (c_uint, )
    libsteps.api_build_dynamic_network_matrix.restype = None
    libsteps.api_build_dynamic_network_matrix.argtypes = (c_uint, )
    libsteps.api_save_network_matrix.restype = None
    libsteps.api_save_network_matrix.argtypes = (c_char_p, c_uint)
    libsteps.api_save_decoupled_network_matrix.restype = None
    libsteps.api_save_decoupled_network_matrix.argtypes = (c_char_p, c_uint)
    libsteps.api_save_dc_network_matrix.restype = None
    libsteps.api_save_dc_network_matrix.argtypes = (c_char_p, c_uint)
    libsteps.api_save_dynamic_network_matrix.restype = None
    libsteps.api_save_dynamic_network_matrix.argtypes = (c_char_p, c_uint)

    libsteps.api_get_dynamic_simulator_integer_parameter.restype = (c_uint)
    libsteps.api_get_dynamic_simulator_integer_parameter.argtypes = (c_char_p, c_uint)
    libsteps.api_get_dynamic_simulator_float_parameter.restype = (c_double)
    libsteps.api_get_dynamic_simulator_float_parameter.argtypes = (c_char_p, c_uint)
    libsteps.api_get_dynamic_simulator_string_parameter.restype = (c_char_p)
    libsteps.api_get_dynamic_simulator_string_parameter.argtypes = (c_char_p, c_uint)
    libsteps.api_get_dynamic_simulator_boolean_parameter.restype = (c_bool)
    libsteps.api_get_dynamic_simulator_boolean_parameter.argtypes = (c_char_p, c_uint)
    libsteps.api_set_dynamic_simulator_integer_parameter.restype = None
    libsteps.api_set_dynamic_simulator_integer_parameter.argtypes = (c_char_p, c_int, c_uint)
    libsteps.api_set_dynamic_simulator_float_parameter.restype = None
    libsteps.api_set_dynamic_simulator_float_parameter.argtypes = (c_char_p, c_double, c_uint)
    libsteps.api_set_dynamic_simulator_string_parameter.restype = None
    libsteps.api_set_dynamic_simulator_string_parameter.argtypes = (c_char_p, c_char_p, c_uint)
    libsteps.api_set_dynamic_simulator_boolean_parameter.restype = None
    libsteps.api_set_dynamic_simulator_boolean_parameter.argtypes = (c_char_p, c_bool, c_uint)
    libsteps.api_get_dynamic_simulator_output_file.restype = (c_char_p)
    libsteps.api_get_dynamic_simulator_output_file.argtypes = (c_uint, )
    libsteps.api_set_dynamic_simulator_output_file.restype = None
    libsteps.api_set_dynamic_simulator_output_file.argtypes = (c_char_p, c_uint)

    libsteps.api_get_dynamic_simulation_time_step.restype = (c_double)
    libsteps.api_get_dynamic_simulation_time_step.argtypes = (c_uint, )
    libsteps.api_set_dynamic_simulation_time_step.restype = None
    libsteps.api_set_dynamic_simulation_time_step.argtypes = (c_double, c_uint)
    libsteps.api_get_dynamic_simulation_time.restype = (c_double)
    libsteps.api_get_dynamic_simulation_time.argtypes = (c_uint, )

    libsteps.api_prepare_meters.restype = None
    libsteps.api_prepare_meters.argtypes = (c_uint, )
    libsteps.api_prepare_bus_related_meters.restype = None
    libsteps.api_prepare_bus_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_generator_related_meters.restype = None
    libsteps.api_prepare_generator_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_wt_generator_related_meters.restype = None
    libsteps.api_prepare_wt_generator_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_pv_unit_related_meters.restype = None
    libsteps.api_prepare_pv_unit_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_energy_storage_related_meters.restype = None
    libsteps.api_prepare_energy_storage_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_load_related_meters.restype = None
    libsteps.api_prepare_load_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_line_related_meters.restype = None
    libsteps.api_prepare_line_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_hvdc_related_meters.restype = None
    libsteps.api_prepare_hvdc_related_meters.argtypes = (c_uint, )
    libsteps.api_prepare_equivalent_device_related_meters.restype = None
    libsteps.api_prepare_equivalent_device_related_meters.argtypes = (c_uint, )


    libsteps.api_prepare_bus_related_meter.restype = None
    libsteps.api_prepare_bus_related_meter.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_prepare_generator_related_meter.restype = None
    libsteps.api_prepare_generator_related_meter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_prepare_wt_generator_related_meter.restype = None
    libsteps.api_prepare_wt_generator_related_meter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_prepare_pv_unit_related_meter.restype = None
    libsteps.api_prepare_pv_unit_related_meter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_prepare_energy_storage_related_meter.restype = None
    libsteps.api_prepare_energy_storage_related_meter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_prepare_load_related_meter.restype = None
    libsteps.api_prepare_load_related_meter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_prepare_line_related_meter.restype = None
    libsteps.api_prepare_line_related_meter.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_prepare_hvdc_related_meter.restype = None
    libsteps.api_prepare_hvdc_related_meter.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_char_p, c_char_p, c_uint)
    libsteps.api_prepare_equivalent_device_related_meter.restype = None
    libsteps.api_prepare_equivalent_device_related_meter.argtypes = (c_uint, c_char_p, c_char_p, c_char_p, c_uint)

    libsteps.api_start_dynamic_simulation.restype = None
    libsteps.api_start_dynamic_simulation.argtypes = (c_uint, )
    libsteps.api_stop_dynamic_simulation.restype = None
    libsteps.api_stop_dynamic_simulation.argtypes = (c_uint, )
    libsteps.api_run_simulation_to_time.restype = None
    libsteps.api_run_simulation_to_time.argtypes = (c_double, c_uint)
    libsteps.api_run_a_step.restype = None
    libsteps.api_run_a_step.argtypes = (c_uint, )

    libsteps.api_set_bus_fault.restype = None
    libsteps.api_set_bus_fault.argtypes = (c_uint, c_char_p, c_double, c_double, c_uint)
    libsteps.api_clear_bus_fault.restype = None
    libsteps.api_clear_bus_fault.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_trip_bus.restype = None
    libsteps.api_trip_bus.argtypes = (c_uint, c_uint)

    libsteps.api_set_line_fault.restype = None
    libsteps.api_set_line_fault.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_double, c_double, c_double, c_uint)
    libsteps.api_clear_line_fault.restype = None
    libsteps.api_clear_line_fault.argtypes = (c_uint, c_uint, c_char_p, c_char_p, c_double, c_uint)
    libsteps.api_trip_line.restype = None
    libsteps.api_trip_line.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_trip_line_breaker.restype = None
    libsteps.api_trip_line_breaker.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_close_line.restype = None
    libsteps.api_close_line.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_close_line_breaker.restype = None
    libsteps.api_close_line_breaker.argtypes = (c_uint, c_uint, c_char_p, c_uint)

    libsteps.api_trip_transformer.restype = None
    libsteps.api_trip_transformer.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_trip_transformer_breaker.restype = None
    libsteps.api_trip_transformer_breaker.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_close_transformer.restype = None
    libsteps.api_close_transformer.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_close_transformer_breaker.restype = None
    libsteps.api_close_transformer_breaker.argtypes = (c_uint, c_uint, c_uint, c_char_p, c_uint)

    libsteps.api_trip_generator.restype = None
    libsteps.api_trip_generator.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_shed_generator.restype = None
    libsteps.api_shed_generator.argtypes = (c_uint, c_char_p, c_double, c_uint)

    libsteps.api_trip_load.restype = None
    libsteps.api_trip_load.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_close_load.restype = None
    libsteps.api_close_load.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_scale_load.restype = None
    libsteps.api_scale_load.argtypes = (c_uint, c_char_p, c_double, c_uint)
    libsteps.api_scale_all_loads.restype = None
    libsteps.api_scale_all_loads.argtypes = (c_double, c_uint)

    libsteps.api_trip_fixed_shunt.restype = None
    libsteps.api_trip_fixed_shunt.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_close_fixed_shunt.restype = None
    libsteps.api_close_fixed_shunt.argtypes = (c_uint, c_char_p, c_uint)

    libsteps.api_manually_bypass_hvdc.restype = None
    libsteps.api_manually_bypass_hvdc.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_manually_unbypass_hvdc.restype = None
    libsteps.api_manually_unbypass_hvdc.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_manually_block_hvdc.restype = None
    libsteps.api_manually_block_hvdc.argtypes = (c_uint, c_uint, c_char_p, c_uint)
    libsteps.api_manually_unblock_hvdc.restype = None
    libsteps.api_manually_unblock_hvdc.argtypes = (c_uint, c_uint, c_char_p, c_uint)

    libsteps.api_get_generator_voltage_reference_in_pu.restype = (c_double)
    libsteps.api_get_generator_voltage_reference_in_pu.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_set_generator_voltage_reference_in_pu.restype = None
    libsteps.api_set_generator_voltage_reference_in_pu.argtypes = (c_uint, c_char_p, c_double, c_uint)

    libsteps.api_get_generator_power_reference_in_MW.restype = (c_double)
    libsteps.api_get_generator_power_reference_in_MW.argtypes = (c_uint, c_char_p, c_uint)
    libsteps.api_set_generator_power_reference_in_MW.restype = None
    libsteps.api_set_generator_power_reference_in_MW.argtypes = (c_uint, c_char_p, c_double, c_uint)

    libsteps.api_search_cct.restype = (c_double)
    libsteps.api_search_cct.argtypes = (c_char_p, c_char_p, c_uint, c_uint, c_char_p, c_uint, c_uint, c_uint)

    return libsteps
