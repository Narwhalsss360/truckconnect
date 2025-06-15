#include "telemetry_metadata.h"

namespace truckconnect {
    template <telemetry_id id>
    struct storage_type_of;

    template<>
    struct storage_type_of<telemetry_id::master> : metadata::master::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::configuration> : metadata::configuration::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::gameplay> : metadata::gameplay::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::channels> : metadata::channels::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::general> : metadata::general::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck> : metadata::truck::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer> : metadata::trailer::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::configuration_substances_info> : metadata::configuration_substances_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::configuration_controls_info> : metadata::configuration_controls_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::configuration_hshifter_info> : metadata::configuration_hshifter_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::configuration_truck_info> : metadata::configuration_truck_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::configuration_trailer_info> : metadata::configuration_trailer_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::configuration_job_info> : metadata::configuration_job_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::gameplay_job_cancelled_info> : metadata::gameplay_job_cancelled_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::gameplay_job_delivered_info> : metadata::gameplay_job_delivered_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::gameplay_player_fined_info> : metadata::gameplay_player_fined_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::gameplay_player_tollgate_paid_info> : metadata::gameplay_player_tollgate_paid_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::gameplay_player_use_ferry_info> : metadata::gameplay_player_use_ferry_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::gameplay_player_use_train_info> : metadata::gameplay_player_use_train_info::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::channel_paused> : metadata::channel_paused::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::channel_local_scale> : metadata::channel_local_scale::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::channel_game_time> : metadata::channel_game_time::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::channel_multiplayer_time_offset> : metadata::channel_multiplayer_time_offset::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::channel_next_rest_stop> : metadata::channel_next_rest_stop::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::job_channel_cargo_damage> : metadata::job_channel_cargo_damage::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_connected> : metadata::trailer_channel_connected::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_cargo_damage> : metadata::trailer_channel_cargo_damage::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_world_placement> : metadata::trailer_channel_world_placement::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_local_linear_velocity> : metadata::trailer_channel_local_linear_velocity::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_local_angular_velocity> : metadata::trailer_channel_local_angular_velocity::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_local_linear_acceleration> : metadata::trailer_channel_local_linear_acceleration::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_local_angular_acceleration> : metadata::trailer_channel_local_angular_acceleration::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wear_body> : metadata::trailer_channel_wear_body::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wear_chassis> : metadata::trailer_channel_wear_chassis::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wear_wheels> : metadata::trailer_channel_wear_wheels::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_susp_deflection> : metadata::trailer_channel_wheel_susp_deflection::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_on_ground> : metadata::trailer_channel_wheel_on_ground::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_substance> : metadata::trailer_channel_wheel_substance::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_velocity> : metadata::trailer_channel_wheel_velocity::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_steering> : metadata::trailer_channel_wheel_steering::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_rotation> : metadata::trailer_channel_wheel_rotation::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_lift> : metadata::trailer_channel_wheel_lift::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::trailer_channel_wheel_lift_offset> : metadata::trailer_channel_wheel_lift_offset::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_world_placement> : metadata::truck_channel_world_placement::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_local_linear_velocity> : metadata::truck_channel_local_linear_velocity::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_local_angular_velocity> : metadata::truck_channel_local_angular_velocity::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_local_linear_acceleration> : metadata::truck_channel_local_linear_acceleration::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_local_angular_acceleration> : metadata::truck_channel_local_angular_acceleration::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_cabin_offset> : metadata::truck_channel_cabin_offset::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_cabin_angular_velocity> : metadata::truck_channel_cabin_angular_velocity::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_cabin_angular_acceleration> : metadata::truck_channel_cabin_angular_acceleration::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_head_offset> : metadata::truck_channel_head_offset::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_speed> : metadata::truck_channel_speed::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_engine_rpm> : metadata::truck_channel_engine_rpm::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_engine_gear> : metadata::truck_channel_engine_gear::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_displayed_gear> : metadata::truck_channel_displayed_gear::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_input_steering> : metadata::truck_channel_input_steering::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_input_throttle> : metadata::truck_channel_input_throttle::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_input_brake> : metadata::truck_channel_input_brake::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_input_clutch> : metadata::truck_channel_input_clutch::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_effective_steering> : metadata::truck_channel_effective_steering::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_effective_throttle> : metadata::truck_channel_effective_throttle::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_effective_brake> : metadata::truck_channel_effective_brake::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_effective_clutch> : metadata::truck_channel_effective_clutch::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_cruise_control> : metadata::truck_channel_cruise_control::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_hshifter_slot> : metadata::truck_channel_hshifter_slot::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_hshifter_selector> : metadata::truck_channel_hshifter_selector::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_parking_brake> : metadata::truck_channel_parking_brake::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_motor_brake> : metadata::truck_channel_motor_brake::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_retarder_level> : metadata::truck_channel_retarder_level::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_brake_air_pressure> : metadata::truck_channel_brake_air_pressure::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_brake_air_pressure_warning> : metadata::truck_channel_brake_air_pressure_warning::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_brake_air_pressure_emergency> : metadata::truck_channel_brake_air_pressure_emergency::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_brake_temperature> : metadata::truck_channel_brake_temperature::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_fuel> : metadata::truck_channel_fuel::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_fuel_warning> : metadata::truck_channel_fuel_warning::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_fuel_average_consumption> : metadata::truck_channel_fuel_average_consumption::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_fuel_range> : metadata::truck_channel_fuel_range::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_adblue> : metadata::truck_channel_adblue::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_adblue_warning> : metadata::truck_channel_adblue_warning::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_oil_pressure> : metadata::truck_channel_oil_pressure::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_oil_pressure_warning> : metadata::truck_channel_oil_pressure_warning::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_oil_temperature> : metadata::truck_channel_oil_temperature::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_water_temperature> : metadata::truck_channel_water_temperature::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_water_temperature_warning> : metadata::truck_channel_water_temperature_warning::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_battery_voltage> : metadata::truck_channel_battery_voltage::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_battery_voltage_warning> : metadata::truck_channel_battery_voltage_warning::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_electric_enabled> : metadata::truck_channel_electric_enabled::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_engine_enabled> : metadata::truck_channel_engine_enabled::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_lblinker> : metadata::truck_channel_lblinker::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_rblinker> : metadata::truck_channel_rblinker::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_hazard_warning> : metadata::truck_channel_hazard_warning::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_lblinker> : metadata::truck_channel_light_lblinker::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_rblinker> : metadata::truck_channel_light_rblinker::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_parking> : metadata::truck_channel_light_parking::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_low_beam> : metadata::truck_channel_light_low_beam::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_high_beam> : metadata::truck_channel_light_high_beam::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_aux_front> : metadata::truck_channel_light_aux_front::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_aux_roof> : metadata::truck_channel_light_aux_roof::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_beacon> : metadata::truck_channel_light_beacon::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_brake> : metadata::truck_channel_light_brake::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_light_reverse> : metadata::truck_channel_light_reverse::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wipers> : metadata::truck_channel_wipers::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_dashboard_backlight> : metadata::truck_channel_dashboard_backlight::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_differential_lock> : metadata::truck_channel_differential_lock::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_lift_axle> : metadata::truck_channel_lift_axle::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_lift_axle_indicator> : metadata::truck_channel_lift_axle_indicator::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_trailer_lift_axle> : metadata::truck_channel_trailer_lift_axle::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_trailer_lift_axle_indicator> : metadata::truck_channel_trailer_lift_axle_indicator::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wear_engine> : metadata::truck_channel_wear_engine::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wear_transmission> : metadata::truck_channel_wear_transmission::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wear_cabin> : metadata::truck_channel_wear_cabin::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wear_chassis> : metadata::truck_channel_wear_chassis::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wear_wheels> : metadata::truck_channel_wear_wheels::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_odometer> : metadata::truck_channel_odometer::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_navigation_distance> : metadata::truck_channel_navigation_distance::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_navigation_time> : metadata::truck_channel_navigation_time::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_navigation_speed_limit> : metadata::truck_channel_navigation_speed_limit::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_susp_deflection> : metadata::truck_channel_wheel_susp_deflection::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_on_ground> : metadata::truck_channel_wheel_on_ground::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_substance> : metadata::truck_channel_wheel_substance::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_velocity> : metadata::truck_channel_wheel_velocity::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_steering> : metadata::truck_channel_wheel_steering::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_rotation> : metadata::truck_channel_wheel_rotation::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_lift> : metadata::truck_channel_wheel_lift::storage_type {};

    template<>
    struct storage_type_of<telemetry_id::truck_channel_wheel_lift_offset> : metadata::truck_channel_wheel_lift_offset::storage_type {};
}

