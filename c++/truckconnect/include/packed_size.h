#pragma once
#include "telemetry_metadata.h"

namespace truckconnect {
    namespace metadata {
        constexpr const uint32_t packed_size_of_gameplay_player_use_train_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<int64_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_gameplay_player_use_ferry_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<int64_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_gameplay_player_tollgate_paid_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<int64_t>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_gameplay_player_fined_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<int64_t>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_gameplay_job_delivered_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<int64_t>::serialization_info::packed_size +
            value_storage<int32_t>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<bool>::serialization_info::packed_size +
            value_storage<bool>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_gameplay_job_cancelled_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<int64_t>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_configuration_job_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<uint64_t>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<bool>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<bool>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_configuration_trailer_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<scs_value_fvector_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_vector_storage<scs_value_fvector_t>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size +
            value_vector_storage<float>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_configuration_truck_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<float>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<scs_value_fvector_t>::serialization_info::packed_size +
            value_vector_storage<float>::serialization_info::packed_size +
            value_vector_storage<float>::serialization_info::packed_size +
            value_storage<scs_value_fvector_t>::serialization_info::packed_size +
            value_storage<scs_value_fvector_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_vector_storage<scs_value_fvector_t>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size +
            value_vector_storage<float>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size +
            value_vector_storage<bool>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_configuration_hshifter_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<uint32_t>::serialization_info::packed_size +
            value_vector_storage<int32_t>::serialization_info::packed_size +
            value_vector_storage<uint32_t>::serialization_info::packed_size +
            value_vector_storage<uint32_t>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_configuration_controls_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_storage<std::string>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_configuration_substances_info = 
            value_storage<uint32_t>::serialization_info::packed_size +
            value_vector_storage<std::string>::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_trailer = 
            metadata::trailer_channel_connected::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_cargo_damage::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_world_placement::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_local_linear_velocity::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_local_angular_velocity::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_local_linear_acceleration::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_local_angular_acceleration::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wear_body::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wear_chassis::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wear_wheels::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_susp_deflection::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_on_ground::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_substance::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_velocity::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_steering::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_rotation::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_lift::storage_type::serialization_info::packed_size +
            metadata::trailer_channel_wheel_lift_offset::storage_type::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_truck = 
            metadata::truck_channel_world_placement::storage_type::serialization_info::packed_size +
            metadata::truck_channel_local_linear_velocity::storage_type::serialization_info::packed_size +
            metadata::truck_channel_local_angular_velocity::storage_type::serialization_info::packed_size +
            metadata::truck_channel_local_linear_acceleration::storage_type::serialization_info::packed_size +
            metadata::truck_channel_local_angular_acceleration::storage_type::serialization_info::packed_size +
            metadata::truck_channel_cabin_offset::storage_type::serialization_info::packed_size +
            metadata::truck_channel_cabin_angular_velocity::storage_type::serialization_info::packed_size +
            metadata::truck_channel_cabin_angular_acceleration::storage_type::serialization_info::packed_size +
            metadata::truck_channel_head_offset::storage_type::serialization_info::packed_size +
            metadata::truck_channel_speed::storage_type::serialization_info::packed_size +
            metadata::truck_channel_engine_rpm::storage_type::serialization_info::packed_size +
            metadata::truck_channel_engine_gear::storage_type::serialization_info::packed_size +
            metadata::truck_channel_displayed_gear::storage_type::serialization_info::packed_size +
            metadata::truck_channel_input_steering::storage_type::serialization_info::packed_size +
            metadata::truck_channel_input_throttle::storage_type::serialization_info::packed_size +
            metadata::truck_channel_input_brake::storage_type::serialization_info::packed_size +
            metadata::truck_channel_input_clutch::storage_type::serialization_info::packed_size +
            metadata::truck_channel_effective_steering::storage_type::serialization_info::packed_size +
            metadata::truck_channel_effective_throttle::storage_type::serialization_info::packed_size +
            metadata::truck_channel_effective_brake::storage_type::serialization_info::packed_size +
            metadata::truck_channel_effective_clutch::storage_type::serialization_info::packed_size +
            metadata::truck_channel_cruise_control::storage_type::serialization_info::packed_size +
            metadata::truck_channel_hshifter_slot::storage_type::serialization_info::packed_size +
            metadata::truck_channel_hshifter_selector::storage_type::serialization_info::packed_size +
            metadata::truck_channel_parking_brake::storage_type::serialization_info::packed_size +
            metadata::truck_channel_motor_brake::storage_type::serialization_info::packed_size +
            metadata::truck_channel_retarder_level::storage_type::serialization_info::packed_size +
            metadata::truck_channel_brake_air_pressure::storage_type::serialization_info::packed_size +
            metadata::truck_channel_brake_air_pressure_warning::storage_type::serialization_info::packed_size +
            metadata::truck_channel_brake_air_pressure_emergency::storage_type::serialization_info::packed_size +
            metadata::truck_channel_brake_temperature::storage_type::serialization_info::packed_size +
            metadata::truck_channel_fuel::storage_type::serialization_info::packed_size +
            metadata::truck_channel_fuel_warning::storage_type::serialization_info::packed_size +
            metadata::truck_channel_fuel_average_consumption::storage_type::serialization_info::packed_size +
            metadata::truck_channel_fuel_range::storage_type::serialization_info::packed_size +
            metadata::truck_channel_adblue::storage_type::serialization_info::packed_size +
            metadata::truck_channel_adblue_warning::storage_type::serialization_info::packed_size +
            metadata::truck_channel_oil_pressure::storage_type::serialization_info::packed_size +
            metadata::truck_channel_oil_pressure_warning::storage_type::serialization_info::packed_size +
            metadata::truck_channel_oil_temperature::storage_type::serialization_info::packed_size +
            metadata::truck_channel_water_temperature::storage_type::serialization_info::packed_size +
            metadata::truck_channel_water_temperature_warning::storage_type::serialization_info::packed_size +
            metadata::truck_channel_battery_voltage::storage_type::serialization_info::packed_size +
            metadata::truck_channel_battery_voltage_warning::storage_type::serialization_info::packed_size +
            metadata::truck_channel_electric_enabled::storage_type::serialization_info::packed_size +
            metadata::truck_channel_engine_enabled::storage_type::serialization_info::packed_size +
            metadata::truck_channel_lblinker::storage_type::serialization_info::packed_size +
            metadata::truck_channel_rblinker::storage_type::serialization_info::packed_size +
            metadata::truck_channel_hazard_warning::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_lblinker::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_rblinker::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_parking::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_low_beam::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_high_beam::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_aux_front::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_aux_roof::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_beacon::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_brake::storage_type::serialization_info::packed_size +
            metadata::truck_channel_light_reverse::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wipers::storage_type::serialization_info::packed_size +
            metadata::truck_channel_dashboard_backlight::storage_type::serialization_info::packed_size +
            metadata::truck_channel_differential_lock::storage_type::serialization_info::packed_size +
            metadata::truck_channel_lift_axle::storage_type::serialization_info::packed_size +
            metadata::truck_channel_lift_axle_indicator::storage_type::serialization_info::packed_size +
            metadata::truck_channel_trailer_lift_axle::storage_type::serialization_info::packed_size +
            metadata::truck_channel_trailer_lift_axle_indicator::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wear_engine::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wear_transmission::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wear_cabin::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wear_chassis::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wear_wheels::storage_type::serialization_info::packed_size +
            metadata::truck_channel_odometer::storage_type::serialization_info::packed_size +
            metadata::truck_channel_navigation_distance::storage_type::serialization_info::packed_size +
            metadata::truck_channel_navigation_time::storage_type::serialization_info::packed_size +
            metadata::truck_channel_navigation_speed_limit::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_susp_deflection::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_on_ground::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_substance::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_velocity::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_steering::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_rotation::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_lift::storage_type::serialization_info::packed_size +
            metadata::truck_channel_wheel_lift_offset::storage_type::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_general = 
            metadata::channel_paused::storage_type::serialization_info::packed_size +
            metadata::channel_local_scale::storage_type::serialization_info::packed_size +
            metadata::channel_game_time::storage_type::serialization_info::packed_size +
            metadata::channel_multiplayer_time_offset::storage_type::serialization_info::packed_size +
            metadata::channel_next_rest_stop::storage_type::serialization_info::packed_size +
            metadata::job_channel_cargo_damage::storage_type::serialization_info::packed_size;

        constexpr const uint32_t packed_size_of_channels = 
            packed_size_of_general +
            packed_size_of_truck +
            packed_size_of_trailer;

        constexpr const uint32_t packed_size_of_gameplay = 
            packed_size_of_gameplay_job_cancelled_info +
            packed_size_of_gameplay_job_delivered_info +
            packed_size_of_gameplay_player_fined_info +
            packed_size_of_gameplay_player_tollgate_paid_info +
            packed_size_of_gameplay_player_use_ferry_info +
            packed_size_of_gameplay_player_use_train_info;

        constexpr const uint32_t packed_size_of_configuration = 
            packed_size_of_configuration_substances_info +
            packed_size_of_configuration_controls_info +
            packed_size_of_configuration_hshifter_info +
            packed_size_of_configuration_truck_info +
            packed_size_of_configuration_trailer_info +
            packed_size_of_configuration_job_info;

        constexpr const uint32_t packed_size_of_master = 
            packed_size_of_configuration +
            packed_size_of_gameplay +
            packed_size_of_channels;

        constexpr const uint32_t packed_size_of(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::master: return packed_size_of_master;
                case telemetry_id::configuration: return packed_size_of_configuration;
                case telemetry_id::gameplay: return packed_size_of_gameplay;
                case telemetry_id::channels: return packed_size_of_channels;
                case telemetry_id::general: return packed_size_of_general;
                case telemetry_id::truck: return packed_size_of_truck;
                case telemetry_id::trailer: return packed_size_of_trailer;
                case telemetry_id::configuration_substances_info: return packed_size_of_configuration_substances_info;
                case telemetry_id::configuration_controls_info: return packed_size_of_configuration_controls_info;
                case telemetry_id::configuration_hshifter_info: return packed_size_of_configuration_hshifter_info;
                case telemetry_id::configuration_truck_info: return packed_size_of_configuration_truck_info;
                case telemetry_id::configuration_trailer_info: return packed_size_of_configuration_trailer_info;
                case telemetry_id::configuration_job_info: return packed_size_of_configuration_job_info;
                case telemetry_id::gameplay_job_cancelled_info: return packed_size_of_gameplay_job_cancelled_info;
                case telemetry_id::gameplay_job_delivered_info: return packed_size_of_gameplay_job_delivered_info;
                case telemetry_id::gameplay_player_fined_info: return packed_size_of_gameplay_player_fined_info;
                case telemetry_id::gameplay_player_tollgate_paid_info: return packed_size_of_gameplay_player_tollgate_paid_info;
                case telemetry_id::gameplay_player_use_ferry_info: return packed_size_of_gameplay_player_use_ferry_info;
                case telemetry_id::gameplay_player_use_train_info: return packed_size_of_gameplay_player_use_train_info;
                case telemetry_id::channel_paused: return metadata::channel_paused::storage_type::serialization_info::packed_size;
                case telemetry_id::channel_local_scale: return metadata::channel_local_scale::storage_type::serialization_info::packed_size;
                case telemetry_id::channel_game_time: return metadata::channel_game_time::storage_type::serialization_info::packed_size;
                case telemetry_id::channel_multiplayer_time_offset: return metadata::channel_multiplayer_time_offset::storage_type::serialization_info::packed_size;
                case telemetry_id::channel_next_rest_stop: return metadata::channel_next_rest_stop::storage_type::serialization_info::packed_size;
                case telemetry_id::job_channel_cargo_damage: return metadata::job_channel_cargo_damage::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_connected: return metadata::trailer_channel_connected::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_cargo_damage: return metadata::trailer_channel_cargo_damage::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_world_placement: return metadata::trailer_channel_world_placement::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_local_linear_velocity: return metadata::trailer_channel_local_linear_velocity::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_local_angular_velocity: return metadata::trailer_channel_local_angular_velocity::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_local_linear_acceleration: return metadata::trailer_channel_local_linear_acceleration::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_local_angular_acceleration: return metadata::trailer_channel_local_angular_acceleration::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wear_body: return metadata::trailer_channel_wear_body::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wear_chassis: return metadata::trailer_channel_wear_chassis::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wear_wheels: return metadata::trailer_channel_wear_wheels::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return metadata::trailer_channel_wheel_susp_deflection::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_on_ground: return metadata::trailer_channel_wheel_on_ground::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_substance: return metadata::trailer_channel_wheel_substance::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_velocity: return metadata::trailer_channel_wheel_velocity::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_steering: return metadata::trailer_channel_wheel_steering::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_rotation: return metadata::trailer_channel_wheel_rotation::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_lift: return metadata::trailer_channel_wheel_lift::storage_type::serialization_info::packed_size;
                case telemetry_id::trailer_channel_wheel_lift_offset: return metadata::trailer_channel_wheel_lift_offset::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_world_placement: return metadata::truck_channel_world_placement::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_local_linear_velocity: return metadata::truck_channel_local_linear_velocity::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_local_angular_velocity: return metadata::truck_channel_local_angular_velocity::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_local_linear_acceleration: return metadata::truck_channel_local_linear_acceleration::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_local_angular_acceleration: return metadata::truck_channel_local_angular_acceleration::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_cabin_offset: return metadata::truck_channel_cabin_offset::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_cabin_angular_velocity: return metadata::truck_channel_cabin_angular_velocity::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return metadata::truck_channel_cabin_angular_acceleration::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_head_offset: return metadata::truck_channel_head_offset::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_speed: return metadata::truck_channel_speed::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_engine_rpm: return metadata::truck_channel_engine_rpm::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_engine_gear: return metadata::truck_channel_engine_gear::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_displayed_gear: return metadata::truck_channel_displayed_gear::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_input_steering: return metadata::truck_channel_input_steering::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_input_throttle: return metadata::truck_channel_input_throttle::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_input_brake: return metadata::truck_channel_input_brake::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_input_clutch: return metadata::truck_channel_input_clutch::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_effective_steering: return metadata::truck_channel_effective_steering::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_effective_throttle: return metadata::truck_channel_effective_throttle::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_effective_brake: return metadata::truck_channel_effective_brake::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_effective_clutch: return metadata::truck_channel_effective_clutch::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_cruise_control: return metadata::truck_channel_cruise_control::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_hshifter_slot: return metadata::truck_channel_hshifter_slot::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_hshifter_selector: return metadata::truck_channel_hshifter_selector::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_parking_brake: return metadata::truck_channel_parking_brake::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_motor_brake: return metadata::truck_channel_motor_brake::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_retarder_level: return metadata::truck_channel_retarder_level::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_brake_air_pressure: return metadata::truck_channel_brake_air_pressure::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return metadata::truck_channel_brake_air_pressure_warning::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return metadata::truck_channel_brake_air_pressure_emergency::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_brake_temperature: return metadata::truck_channel_brake_temperature::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_fuel: return metadata::truck_channel_fuel::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_fuel_warning: return metadata::truck_channel_fuel_warning::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_fuel_average_consumption: return metadata::truck_channel_fuel_average_consumption::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_fuel_range: return metadata::truck_channel_fuel_range::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_adblue: return metadata::truck_channel_adblue::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_adblue_warning: return metadata::truck_channel_adblue_warning::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_oil_pressure: return metadata::truck_channel_oil_pressure::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_oil_pressure_warning: return metadata::truck_channel_oil_pressure_warning::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_oil_temperature: return metadata::truck_channel_oil_temperature::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_water_temperature: return metadata::truck_channel_water_temperature::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_water_temperature_warning: return metadata::truck_channel_water_temperature_warning::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_battery_voltage: return metadata::truck_channel_battery_voltage::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_battery_voltage_warning: return metadata::truck_channel_battery_voltage_warning::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_electric_enabled: return metadata::truck_channel_electric_enabled::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_engine_enabled: return metadata::truck_channel_engine_enabled::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_lblinker: return metadata::truck_channel_lblinker::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_rblinker: return metadata::truck_channel_rblinker::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_hazard_warning: return metadata::truck_channel_hazard_warning::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_lblinker: return metadata::truck_channel_light_lblinker::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_rblinker: return metadata::truck_channel_light_rblinker::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_parking: return metadata::truck_channel_light_parking::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_low_beam: return metadata::truck_channel_light_low_beam::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_high_beam: return metadata::truck_channel_light_high_beam::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_aux_front: return metadata::truck_channel_light_aux_front::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_aux_roof: return metadata::truck_channel_light_aux_roof::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_beacon: return metadata::truck_channel_light_beacon::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_brake: return metadata::truck_channel_light_brake::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_light_reverse: return metadata::truck_channel_light_reverse::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wipers: return metadata::truck_channel_wipers::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_dashboard_backlight: return metadata::truck_channel_dashboard_backlight::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_differential_lock: return metadata::truck_channel_differential_lock::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_lift_axle: return metadata::truck_channel_lift_axle::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_lift_axle_indicator: return metadata::truck_channel_lift_axle_indicator::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_trailer_lift_axle: return metadata::truck_channel_trailer_lift_axle::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return metadata::truck_channel_trailer_lift_axle_indicator::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wear_engine: return metadata::truck_channel_wear_engine::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wear_transmission: return metadata::truck_channel_wear_transmission::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wear_cabin: return metadata::truck_channel_wear_cabin::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wear_chassis: return metadata::truck_channel_wear_chassis::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wear_wheels: return metadata::truck_channel_wear_wheels::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_odometer: return metadata::truck_channel_odometer::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_navigation_distance: return metadata::truck_channel_navigation_distance::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_navigation_time: return metadata::truck_channel_navigation_time::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_navigation_speed_limit: return metadata::truck_channel_navigation_speed_limit::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_susp_deflection: return metadata::truck_channel_wheel_susp_deflection::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_on_ground: return metadata::truck_channel_wheel_on_ground::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_substance: return metadata::truck_channel_wheel_substance::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_velocity: return metadata::truck_channel_wheel_velocity::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_steering: return metadata::truck_channel_wheel_steering::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_rotation: return metadata::truck_channel_wheel_rotation::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_lift: return metadata::truck_channel_wheel_lift::storage_type::serialization_info::packed_size;
                case telemetry_id::truck_channel_wheel_lift_offset: return metadata::truck_channel_wheel_lift_offset::storage_type::serialization_info::packed_size;
                default: return INVALID_OFFSET;
            }
        }
    }
}
