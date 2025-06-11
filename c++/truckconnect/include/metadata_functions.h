#pragma once
#include "telemetry_metadata.h"

namespace truckconnect {
    namespace metadata {
        constexpr const telemetry_type& telemtry_type_of(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::master: return master::telemetry_type;
                case telemetry_id::configuration: return configuration::telemetry_type;
                case telemetry_id::gameplay: return gameplay::telemetry_type;
                case telemetry_id::channels: return channels::telemetry_type;
                case telemetry_id::general: return general::telemetry_type;
                case telemetry_id::truck: return truck::telemetry_type;
                case telemetry_id::trailer: return trailer::telemetry_type;
                case telemetry_id::configuration_substances_info: return configuration_substances_info::telemetry_type;
                case telemetry_id::configuration_controls_info: return configuration_controls_info::telemetry_type;
                case telemetry_id::configuration_hshifter_info: return configuration_hshifter_info::telemetry_type;
                case telemetry_id::configuration_truck_info: return configuration_truck_info::telemetry_type;
                case telemetry_id::configuration_trailer_info: return configuration_trailer_info::telemetry_type;
                case telemetry_id::configuration_job_info: return configuration_job_info::telemetry_type;
                case telemetry_id::gameplay_job_cancelled_info: return gameplay_job_cancelled_info::telemetry_type;
                case telemetry_id::gameplay_job_delivered_info: return gameplay_job_delivered_info::telemetry_type;
                case telemetry_id::gameplay_player_fined_info: return gameplay_player_fined_info::telemetry_type;
                case telemetry_id::gameplay_player_tollgate_paid_info: return gameplay_player_tollgate_paid_info::telemetry_type;
                case telemetry_id::gameplay_player_use_ferry_info: return gameplay_player_use_ferry_info::telemetry_type;
                case telemetry_id::gameplay_player_use_train_info: return gameplay_player_use_train_info::telemetry_type;
                case telemetry_id::channel_paused: return channel_paused::telemetry_type;
                case telemetry_id::channel_local_scale: return channel_local_scale::telemetry_type;
                case telemetry_id::channel_game_time: return channel_game_time::telemetry_type;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::telemetry_type;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::telemetry_type;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::telemetry_type;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::telemetry_type;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::telemetry_type;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::telemetry_type;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::telemetry_type;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::telemetry_type;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::telemetry_type;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::telemetry_type;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::telemetry_type;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::telemetry_type;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::telemetry_type;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::telemetry_type;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::telemetry_type;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::telemetry_type;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::telemetry_type;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::telemetry_type;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::telemetry_type;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::telemetry_type;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::telemetry_type;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::telemetry_type;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::telemetry_type;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::telemetry_type;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::telemetry_type;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::telemetry_type;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::telemetry_type;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::telemetry_type;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::telemetry_type;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::telemetry_type;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::telemetry_type;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::telemetry_type;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::telemetry_type;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::telemetry_type;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::telemetry_type;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::telemetry_type;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::telemetry_type;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::telemetry_type;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::telemetry_type;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::telemetry_type;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::telemetry_type;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::telemetry_type;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::telemetry_type;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::telemetry_type;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::telemetry_type;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::telemetry_type;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::telemetry_type;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::telemetry_type;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::telemetry_type;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::telemetry_type;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::telemetry_type;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::telemetry_type;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::telemetry_type;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::telemetry_type;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::telemetry_type;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::telemetry_type;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::telemetry_type;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::telemetry_type;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::telemetry_type;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::telemetry_type;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::telemetry_type;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::telemetry_type;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::telemetry_type;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::telemetry_type;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::telemetry_type;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::telemetry_type;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::telemetry_type;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::telemetry_type;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::telemetry_type;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::telemetry_type;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::telemetry_type;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::telemetry_type;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::telemetry_type;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::telemetry_type;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::telemetry_type;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::telemetry_type;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::telemetry_type;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::telemetry_type;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::telemetry_type;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::telemetry_type;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::telemetry_type;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::telemetry_type;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::telemetry_type;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::telemetry_type;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::telemetry_type;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::telemetry_type;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::telemetry_type;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::telemetry_type;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::telemetry_type;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::telemetry_type;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::telemetry_type;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::telemetry_type;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::telemetry_type;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::telemetry_type;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::telemetry_type;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::telemetry_type;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::telemetry_type;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::telemetry_type;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::telemetry_type;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::telemetry_type;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::telemetry_type;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::telemetry_type;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::telemetry_type;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::telemetry_type;
                default: return telemetry_type::invalid;
            }
        }

        constexpr const uint32_t master_offset_of(const telemetry_id& id, const uint32_t& trailer_index = INVALID_TRAILER_INDEX) {
            switch (id) {
                case telemetry_id::master: return master::master_offset;
                case telemetry_id::configuration: return configuration::master_offset;
                case telemetry_id::gameplay: return gameplay::master_offset;
                case telemetry_id::channels: return channels::master_offset;
                case telemetry_id::general: return general::master_offset;
                case telemetry_id::truck: return truck::master_offset;
                case telemetry_id::trailer: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer::master_offset + sizeof(master_storage::channels_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::configuration_substances_info: return configuration_substances_info::master_offset;
                case telemetry_id::configuration_controls_info: return configuration_controls_info::master_offset;
                case telemetry_id::configuration_hshifter_info: return configuration_hshifter_info::master_offset;
                case telemetry_id::configuration_truck_info: return configuration_truck_info::master_offset;
                case telemetry_id::configuration_trailer_info: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? configuration_trailer_info::master_offset + sizeof(master_storage::configuration_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::configuration_job_info: return configuration_job_info::master_offset;
                case telemetry_id::gameplay_job_cancelled_info: return gameplay_job_cancelled_info::master_offset;
                case telemetry_id::gameplay_job_delivered_info: return gameplay_job_delivered_info::master_offset;
                case telemetry_id::gameplay_player_fined_info: return gameplay_player_fined_info::master_offset;
                case telemetry_id::gameplay_player_tollgate_paid_info: return gameplay_player_tollgate_paid_info::master_offset;
                case telemetry_id::gameplay_player_use_ferry_info: return gameplay_player_use_ferry_info::master_offset;
                case telemetry_id::gameplay_player_use_train_info: return gameplay_player_use_train_info::master_offset;
                case telemetry_id::channel_paused: return channel_paused::master_offset;
                case telemetry_id::channel_local_scale: return channel_local_scale::master_offset;
                case telemetry_id::channel_game_time: return channel_game_time::master_offset;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::master_offset;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::master_offset;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::master_offset;
                case telemetry_id::trailer_channel_connected: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_connected::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_cargo_damage: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_cargo_damage::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_world_placement: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_world_placement::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_local_linear_velocity: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_local_linear_velocity::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_local_angular_velocity: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_local_angular_velocity::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_local_linear_acceleration: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_local_linear_acceleration::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_local_angular_acceleration: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_local_angular_acceleration::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wear_body: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wear_body::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wear_chassis: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wear_chassis::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wear_wheels: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wear_wheels::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_susp_deflection::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_on_ground: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_on_ground::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_substance: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_substance::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_velocity: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_velocity::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_steering: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_steering::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_rotation: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_rotation::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_lift: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_lift::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::trailer_channel_wheel_lift_offset: return 0 <= trailer_index && trailer_index <= SCS_TELEMETRY_trailers_count ? trailer_channel_wheel_lift_offset::master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index : INVALID_OFFSET;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::master_offset;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::master_offset;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::master_offset;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::master_offset;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::master_offset;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::master_offset;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::master_offset;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::master_offset;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::master_offset;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::master_offset;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::master_offset;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::master_offset;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::master_offset;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::master_offset;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::master_offset;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::master_offset;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::master_offset;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::master_offset;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::master_offset;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::master_offset;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::master_offset;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::master_offset;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::master_offset;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::master_offset;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::master_offset;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::master_offset;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::master_offset;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::master_offset;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::master_offset;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::master_offset;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::master_offset;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::master_offset;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::master_offset;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::master_offset;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::master_offset;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::master_offset;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::master_offset;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::master_offset;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::master_offset;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::master_offset;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::master_offset;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::master_offset;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::master_offset;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::master_offset;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::master_offset;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::master_offset;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::master_offset;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::master_offset;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::master_offset;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::master_offset;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::master_offset;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::master_offset;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::master_offset;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::master_offset;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::master_offset;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::master_offset;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::master_offset;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::master_offset;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::master_offset;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::master_offset;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::master_offset;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::master_offset;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::master_offset;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::master_offset;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::master_offset;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::master_offset;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::master_offset;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::master_offset;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::master_offset;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::master_offset;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::master_offset;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::master_offset;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::master_offset;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::master_offset;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::master_offset;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::master_offset;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::master_offset;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::master_offset;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::master_offset;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::master_offset;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::master_offset;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::master_offset;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::master_offset;
                default: return INVALID_OFFSET;
            }
        }

        constexpr const uint32_t& structure_offset_of(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::master: return master::structure_offset;
                case telemetry_id::configuration: return configuration::structure_offset;
                case telemetry_id::gameplay: return gameplay::structure_offset;
                case telemetry_id::channels: return channels::structure_offset;
                case telemetry_id::general: return general::structure_offset;
                case telemetry_id::truck: return truck::structure_offset;
                case telemetry_id::trailer: return trailer::structure_offset;
                case telemetry_id::configuration_substances_info: return configuration_substances_info::structure_offset;
                case telemetry_id::configuration_controls_info: return configuration_controls_info::structure_offset;
                case telemetry_id::configuration_hshifter_info: return configuration_hshifter_info::structure_offset;
                case telemetry_id::configuration_truck_info: return configuration_truck_info::structure_offset;
                case telemetry_id::configuration_trailer_info: return configuration_trailer_info::structure_offset;
                case telemetry_id::configuration_job_info: return configuration_job_info::structure_offset;
                case telemetry_id::gameplay_job_cancelled_info: return gameplay_job_cancelled_info::structure_offset;
                case telemetry_id::gameplay_job_delivered_info: return gameplay_job_delivered_info::structure_offset;
                case telemetry_id::gameplay_player_fined_info: return gameplay_player_fined_info::structure_offset;
                case telemetry_id::gameplay_player_tollgate_paid_info: return gameplay_player_tollgate_paid_info::structure_offset;
                case telemetry_id::gameplay_player_use_ferry_info: return gameplay_player_use_ferry_info::structure_offset;
                case telemetry_id::gameplay_player_use_train_info: return gameplay_player_use_train_info::structure_offset;
                case telemetry_id::channel_paused: return channel_paused::structure_offset;
                case telemetry_id::channel_local_scale: return channel_local_scale::structure_offset;
                case telemetry_id::channel_game_time: return channel_game_time::structure_offset;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::structure_offset;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::structure_offset;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::structure_offset;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::structure_offset;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::structure_offset;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::structure_offset;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::structure_offset;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::structure_offset;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::structure_offset;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::structure_offset;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::structure_offset;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::structure_offset;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::structure_offset;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::structure_offset;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::structure_offset;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::structure_offset;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::structure_offset;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::structure_offset;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::structure_offset;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::structure_offset;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::structure_offset;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::structure_offset;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::structure_offset;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::structure_offset;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::structure_offset;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::structure_offset;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::structure_offset;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::structure_offset;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::structure_offset;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::structure_offset;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::structure_offset;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::structure_offset;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::structure_offset;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::structure_offset;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::structure_offset;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::structure_offset;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::structure_offset;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::structure_offset;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::structure_offset;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::structure_offset;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::structure_offset;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::structure_offset;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::structure_offset;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::structure_offset;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::structure_offset;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::structure_offset;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::structure_offset;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::structure_offset;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::structure_offset;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::structure_offset;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::structure_offset;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::structure_offset;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::structure_offset;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::structure_offset;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::structure_offset;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::structure_offset;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::structure_offset;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::structure_offset;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::structure_offset;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::structure_offset;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::structure_offset;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::structure_offset;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::structure_offset;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::structure_offset;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::structure_offset;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::structure_offset;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::structure_offset;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::structure_offset;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::structure_offset;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::structure_offset;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::structure_offset;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::structure_offset;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::structure_offset;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::structure_offset;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::structure_offset;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::structure_offset;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::structure_offset;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::structure_offset;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::structure_offset;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::structure_offset;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::structure_offset;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::structure_offset;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::structure_offset;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::structure_offset;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::structure_offset;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::structure_offset;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::structure_offset;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::structure_offset;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::structure_offset;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::structure_offset;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::structure_offset;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::structure_offset;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::structure_offset;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::structure_offset;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::structure_offset;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::structure_offset;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::structure_offset;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::structure_offset;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::structure_offset;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::structure_offset;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::structure_offset;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::structure_offset;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::structure_offset;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::structure_offset;
                default: return INVALID_OFFSET;
            }
        }

        constexpr const bool& indexed(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::channel_paused: return channel_paused::indexed;
                case telemetry_id::channel_local_scale: return channel_local_scale::indexed;
                case telemetry_id::channel_game_time: return channel_game_time::indexed;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::indexed;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::indexed;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::indexed;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::indexed;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::indexed;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::indexed;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::indexed;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::indexed;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::indexed;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::indexed;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::indexed;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::indexed;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::indexed;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::indexed;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::indexed;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::indexed;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::indexed;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::indexed;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::indexed;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::indexed;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::indexed;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::indexed;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::indexed;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::indexed;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::indexed;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::indexed;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::indexed;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::indexed;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::indexed;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::indexed;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::indexed;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::indexed;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::indexed;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::indexed;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::indexed;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::indexed;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::indexed;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::indexed;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::indexed;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::indexed;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::indexed;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::indexed;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::indexed;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::indexed;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::indexed;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::indexed;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::indexed;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::indexed;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::indexed;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::indexed;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::indexed;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::indexed;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::indexed;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::indexed;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::indexed;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::indexed;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::indexed;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::indexed;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::indexed;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::indexed;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::indexed;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::indexed;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::indexed;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::indexed;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::indexed;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::indexed;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::indexed;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::indexed;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::indexed;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::indexed;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::indexed;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::indexed;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::indexed;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::indexed;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::indexed;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::indexed;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::indexed;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::indexed;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::indexed;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::indexed;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::indexed;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::indexed;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::indexed;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::indexed;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::indexed;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::indexed;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::indexed;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::indexed;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::indexed;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::indexed;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::indexed;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::indexed;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::indexed;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::indexed;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::indexed;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::indexed;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::indexed;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::indexed;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::indexed;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::indexed;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::indexed;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::indexed;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::indexed;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::indexed;
                default: return false;
            }
        }

        constexpr const uint32_t& max_count(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::channel_paused: return channel_paused::max_count;
                case telemetry_id::channel_local_scale: return channel_local_scale::max_count;
                case telemetry_id::channel_game_time: return channel_game_time::max_count;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::max_count;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::max_count;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::max_count;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::max_count;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::max_count;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::max_count;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::max_count;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::max_count;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::max_count;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::max_count;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::max_count;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::max_count;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::max_count;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::max_count;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::max_count;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::max_count;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::max_count;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::max_count;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::max_count;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::max_count;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::max_count;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::max_count;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::max_count;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::max_count;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::max_count;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::max_count;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::max_count;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::max_count;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::max_count;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::max_count;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::max_count;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::max_count;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::max_count;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::max_count;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::max_count;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::max_count;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::max_count;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::max_count;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::max_count;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::max_count;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::max_count;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::max_count;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::max_count;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::max_count;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::max_count;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::max_count;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::max_count;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::max_count;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::max_count;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::max_count;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::max_count;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::max_count;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::max_count;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::max_count;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::max_count;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::max_count;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::max_count;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::max_count;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::max_count;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::max_count;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::max_count;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::max_count;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::max_count;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::max_count;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::max_count;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::max_count;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::max_count;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::max_count;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::max_count;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::max_count;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::max_count;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::max_count;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::max_count;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::max_count;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::max_count;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::max_count;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::max_count;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::max_count;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::max_count;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::max_count;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::max_count;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::max_count;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::max_count;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::max_count;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::max_count;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::max_count;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::max_count;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::max_count;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::max_count;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::max_count;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::max_count;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::max_count;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::max_count;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::max_count;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::max_count;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::max_count;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::max_count;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::max_count;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::max_count;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::max_count;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::max_count;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::max_count;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::max_count;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::max_count;
                default: return 1;
            }
        }

        constexpr const bool& is_trailer_channel(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::channel_paused: return channel_paused::trailer_channel;
                case telemetry_id::channel_local_scale: return channel_local_scale::trailer_channel;
                case telemetry_id::channel_game_time: return channel_game_time::trailer_channel;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::trailer_channel;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::trailer_channel;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::trailer_channel;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::trailer_channel;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::trailer_channel;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::trailer_channel;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::trailer_channel;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::trailer_channel;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::trailer_channel;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::trailer_channel;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::trailer_channel;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::trailer_channel;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::trailer_channel;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::trailer_channel;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::trailer_channel;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::trailer_channel;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::trailer_channel;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::trailer_channel;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::trailer_channel;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::trailer_channel;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::trailer_channel;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::trailer_channel;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::trailer_channel;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::trailer_channel;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::trailer_channel;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::trailer_channel;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::trailer_channel;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::trailer_channel;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::trailer_channel;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::trailer_channel;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::trailer_channel;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::trailer_channel;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::trailer_channel;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::trailer_channel;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::trailer_channel;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::trailer_channel;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::trailer_channel;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::trailer_channel;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::trailer_channel;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::trailer_channel;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::trailer_channel;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::trailer_channel;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::trailer_channel;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::trailer_channel;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::trailer_channel;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::trailer_channel;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::trailer_channel;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::trailer_channel;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::trailer_channel;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::trailer_channel;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::trailer_channel;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::trailer_channel;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::trailer_channel;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::trailer_channel;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::trailer_channel;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::trailer_channel;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::trailer_channel;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::trailer_channel;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::trailer_channel;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::trailer_channel;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::trailer_channel;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::trailer_channel;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::trailer_channel;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::trailer_channel;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::trailer_channel;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::trailer_channel;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::trailer_channel;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::trailer_channel;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::trailer_channel;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::trailer_channel;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::trailer_channel;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::trailer_channel;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::trailer_channel;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::trailer_channel;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::trailer_channel;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::trailer_channel;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::trailer_channel;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::trailer_channel;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::trailer_channel;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::trailer_channel;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::trailer_channel;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::trailer_channel;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::trailer_channel;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::trailer_channel;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::trailer_channel;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::trailer_channel;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::trailer_channel;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::trailer_channel;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::trailer_channel;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::trailer_channel;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::trailer_channel;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::trailer_channel;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::trailer_channel;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::trailer_channel;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::trailer_channel;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::trailer_channel;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::trailer_channel;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::trailer_channel;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::trailer_channel;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::trailer_channel;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::trailer_channel;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::trailer_channel;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::trailer_channel;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::trailer_channel;
                default: return false;
            }
        }

        constexpr const scs_value_type_t& scs_type_id_of(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::channel_paused: return channel_paused::scs_type_id;
                case telemetry_id::channel_local_scale: return channel_local_scale::scs_type_id;
                case telemetry_id::channel_game_time: return channel_game_time::scs_type_id;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::scs_type_id;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::scs_type_id;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::scs_type_id;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::scs_type_id;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::scs_type_id;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::scs_type_id;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::scs_type_id;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::scs_type_id;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::scs_type_id;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::scs_type_id;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::scs_type_id;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::scs_type_id;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::scs_type_id;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::scs_type_id;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::scs_type_id;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::scs_type_id;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::scs_type_id;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::scs_type_id;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::scs_type_id;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::scs_type_id;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::scs_type_id;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::scs_type_id;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::scs_type_id;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::scs_type_id;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::scs_type_id;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::scs_type_id;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::scs_type_id;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::scs_type_id;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::scs_type_id;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::scs_type_id;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::scs_type_id;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::scs_type_id;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::scs_type_id;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::scs_type_id;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::scs_type_id;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::scs_type_id;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::scs_type_id;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::scs_type_id;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::scs_type_id;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::scs_type_id;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::scs_type_id;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::scs_type_id;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::scs_type_id;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::scs_type_id;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::scs_type_id;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::scs_type_id;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::scs_type_id;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::scs_type_id;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::scs_type_id;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::scs_type_id;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::scs_type_id;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::scs_type_id;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::scs_type_id;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::scs_type_id;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::scs_type_id;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::scs_type_id;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::scs_type_id;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::scs_type_id;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::scs_type_id;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::scs_type_id;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::scs_type_id;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::scs_type_id;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::scs_type_id;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::scs_type_id;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::scs_type_id;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::scs_type_id;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::scs_type_id;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::scs_type_id;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::scs_type_id;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::scs_type_id;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::scs_type_id;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::scs_type_id;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::scs_type_id;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::scs_type_id;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::scs_type_id;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::scs_type_id;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::scs_type_id;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::scs_type_id;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::scs_type_id;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::scs_type_id;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::scs_type_id;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::scs_type_id;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::scs_type_id;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::scs_type_id;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::scs_type_id;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::scs_type_id;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::scs_type_id;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::scs_type_id;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::scs_type_id;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::scs_type_id;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::scs_type_id;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::scs_type_id;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::scs_type_id;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::scs_type_id;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::scs_type_id;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::scs_type_id;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::scs_type_id;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::scs_type_id;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::scs_type_id;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::scs_type_id;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::scs_type_id;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::scs_type_id;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::scs_type_id;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::scs_type_id;
                default: return SCS_VALUE_TYPE_INVALID;
            }
        }

        constexpr bool streq(char const* a, char const* b) {
            return *a == *b && (*a == '\0' || streq(a + 1, b + 1));
        }

        constexpr const telemetry_id& id_of(const char* const macro) {
            return
                streq(macro, "master") ? master::id :
                streq(macro, "configuration") ? configuration::id :
                streq(macro, "gameplay") ? gameplay::id :
                streq(macro, "channels") ? channels::id :
                streq(macro, "general") ? general::id :
                streq(macro, "truck") ? truck::id :
                streq(macro, "trailer") ? trailer::id :
                streq(macro, "configuration_substances_info") || streq(macro, configuration_substances_info::macro) ? configuration_substances_info::id :
                streq(macro, "configuration_controls_info") || streq(macro, configuration_controls_info::macro) ? configuration_controls_info::id :
                streq(macro, "configuration_hshifter_info") || streq(macro, configuration_hshifter_info::macro) ? configuration_hshifter_info::id :
                streq(macro, "configuration_truck_info") || streq(macro, configuration_truck_info::macro) ? configuration_truck_info::id :
                streq(macro, "configuration_trailer_info") || streq(macro, configuration_trailer_info::macro) ? configuration_trailer_info::id :
                streq(macro, "configuration_job_info") || streq(macro, configuration_job_info::macro) ? configuration_job_info::id :
                streq(macro, "gameplay_job_cancelled_info") || streq(macro, gameplay_job_cancelled_info::macro) ? gameplay_job_cancelled_info::id :
                streq(macro, "gameplay_job_delivered_info") || streq(macro, gameplay_job_delivered_info::macro) ? gameplay_job_delivered_info::id :
                streq(macro, "gameplay_player_fined_info") || streq(macro, gameplay_player_fined_info::macro) ? gameplay_player_fined_info::id :
                streq(macro, "gameplay_player_tollgate_paid_info") || streq(macro, gameplay_player_tollgate_paid_info::macro) ? gameplay_player_tollgate_paid_info::id :
                streq(macro, "gameplay_player_use_ferry_info") || streq(macro, gameplay_player_use_ferry_info::macro) ? gameplay_player_use_ferry_info::id :
                streq(macro, "gameplay_player_use_train_info") || streq(macro, gameplay_player_use_train_info::macro) ? gameplay_player_use_train_info::id :
                streq(macro, "channel_paused") || streq(macro, channel_paused::macro) ? channel_paused::id :
                streq(macro, "channel_local_scale") || streq(macro, channel_local_scale::macro) ? channel_local_scale::id :
                streq(macro, "channel_game_time") || streq(macro, channel_game_time::macro) ? channel_game_time::id :
                streq(macro, "channel_multiplayer_time_offset") || streq(macro, channel_multiplayer_time_offset::macro) ? channel_multiplayer_time_offset::id :
                streq(macro, "channel_next_rest_stop") || streq(macro, channel_next_rest_stop::macro) ? channel_next_rest_stop::id :
                streq(macro, "job_channel_cargo_damage") || streq(macro, job_channel_cargo_damage::macro) ? job_channel_cargo_damage::id :
                    streq(macro, "trailer_channel_connected") ||
                    streq(macro, "trailer_channel_connected.0") ||
                    streq(macro, "trailer_channel_connected.1") ||
                    streq(macro, "trailer_channel_connected.2") ||
                    streq(macro, "trailer_channel_connected.3") ||
                    streq(macro, "trailer_channel_connected.4") ||
                    streq(macro, "trailer_channel_connected.5") ||
                    streq(macro, "trailer_channel_connected.6") ||
                    streq(macro, "trailer_channel_connected.7") ||
                    streq(macro, "trailer_channel_connected.8") ||
                    streq(macro, "trailer_channel_connected.9") ? trailer_channel_connected::id :
                    streq(macro, "trailer_channel_cargo_damage") ||
                    streq(macro, "trailer_channel_cargo_damage.0") ||
                    streq(macro, "trailer_channel_cargo_damage.1") ||
                    streq(macro, "trailer_channel_cargo_damage.2") ||
                    streq(macro, "trailer_channel_cargo_damage.3") ||
                    streq(macro, "trailer_channel_cargo_damage.4") ||
                    streq(macro, "trailer_channel_cargo_damage.5") ||
                    streq(macro, "trailer_channel_cargo_damage.6") ||
                    streq(macro, "trailer_channel_cargo_damage.7") ||
                    streq(macro, "trailer_channel_cargo_damage.8") ||
                    streq(macro, "trailer_channel_cargo_damage.9") ? trailer_channel_cargo_damage::id :
                    streq(macro, "trailer_channel_world_placement") ||
                    streq(macro, "trailer_channel_world_placement.0") ||
                    streq(macro, "trailer_channel_world_placement.1") ||
                    streq(macro, "trailer_channel_world_placement.2") ||
                    streq(macro, "trailer_channel_world_placement.3") ||
                    streq(macro, "trailer_channel_world_placement.4") ||
                    streq(macro, "trailer_channel_world_placement.5") ||
                    streq(macro, "trailer_channel_world_placement.6") ||
                    streq(macro, "trailer_channel_world_placement.7") ||
                    streq(macro, "trailer_channel_world_placement.8") ||
                    streq(macro, "trailer_channel_world_placement.9") ? trailer_channel_world_placement::id :
                    streq(macro, "trailer_channel_local_linear_velocity") ||
                    streq(macro, "trailer_channel_local_linear_velocity.0") ||
                    streq(macro, "trailer_channel_local_linear_velocity.1") ||
                    streq(macro, "trailer_channel_local_linear_velocity.2") ||
                    streq(macro, "trailer_channel_local_linear_velocity.3") ||
                    streq(macro, "trailer_channel_local_linear_velocity.4") ||
                    streq(macro, "trailer_channel_local_linear_velocity.5") ||
                    streq(macro, "trailer_channel_local_linear_velocity.6") ||
                    streq(macro, "trailer_channel_local_linear_velocity.7") ||
                    streq(macro, "trailer_channel_local_linear_velocity.8") ||
                    streq(macro, "trailer_channel_local_linear_velocity.9") ? trailer_channel_local_linear_velocity::id :
                    streq(macro, "trailer_channel_local_angular_velocity") ||
                    streq(macro, "trailer_channel_local_angular_velocity.0") ||
                    streq(macro, "trailer_channel_local_angular_velocity.1") ||
                    streq(macro, "trailer_channel_local_angular_velocity.2") ||
                    streq(macro, "trailer_channel_local_angular_velocity.3") ||
                    streq(macro, "trailer_channel_local_angular_velocity.4") ||
                    streq(macro, "trailer_channel_local_angular_velocity.5") ||
                    streq(macro, "trailer_channel_local_angular_velocity.6") ||
                    streq(macro, "trailer_channel_local_angular_velocity.7") ||
                    streq(macro, "trailer_channel_local_angular_velocity.8") ||
                    streq(macro, "trailer_channel_local_angular_velocity.9") ? trailer_channel_local_angular_velocity::id :
                    streq(macro, "trailer_channel_local_linear_acceleration") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.0") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.1") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.2") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.3") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.4") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.5") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.6") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.7") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.8") ||
                    streq(macro, "trailer_channel_local_linear_acceleration.9") ? trailer_channel_local_linear_acceleration::id :
                    streq(macro, "trailer_channel_local_angular_acceleration") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.0") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.1") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.2") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.3") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.4") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.5") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.6") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.7") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.8") ||
                    streq(macro, "trailer_channel_local_angular_acceleration.9") ? trailer_channel_local_angular_acceleration::id :
                    streq(macro, "trailer_channel_wear_body") ||
                    streq(macro, "trailer_channel_wear_body.0") ||
                    streq(macro, "trailer_channel_wear_body.1") ||
                    streq(macro, "trailer_channel_wear_body.2") ||
                    streq(macro, "trailer_channel_wear_body.3") ||
                    streq(macro, "trailer_channel_wear_body.4") ||
                    streq(macro, "trailer_channel_wear_body.5") ||
                    streq(macro, "trailer_channel_wear_body.6") ||
                    streq(macro, "trailer_channel_wear_body.7") ||
                    streq(macro, "trailer_channel_wear_body.8") ||
                    streq(macro, "trailer_channel_wear_body.9") ? trailer_channel_wear_body::id :
                    streq(macro, "trailer_channel_wear_chassis") ||
                    streq(macro, "trailer_channel_wear_chassis.0") ||
                    streq(macro, "trailer_channel_wear_chassis.1") ||
                    streq(macro, "trailer_channel_wear_chassis.2") ||
                    streq(macro, "trailer_channel_wear_chassis.3") ||
                    streq(macro, "trailer_channel_wear_chassis.4") ||
                    streq(macro, "trailer_channel_wear_chassis.5") ||
                    streq(macro, "trailer_channel_wear_chassis.6") ||
                    streq(macro, "trailer_channel_wear_chassis.7") ||
                    streq(macro, "trailer_channel_wear_chassis.8") ||
                    streq(macro, "trailer_channel_wear_chassis.9") ? trailer_channel_wear_chassis::id :
                    streq(macro, "trailer_channel_wear_wheels") ||
                    streq(macro, "trailer_channel_wear_wheels.0") ||
                    streq(macro, "trailer_channel_wear_wheels.1") ||
                    streq(macro, "trailer_channel_wear_wheels.2") ||
                    streq(macro, "trailer_channel_wear_wheels.3") ||
                    streq(macro, "trailer_channel_wear_wheels.4") ||
                    streq(macro, "trailer_channel_wear_wheels.5") ||
                    streq(macro, "trailer_channel_wear_wheels.6") ||
                    streq(macro, "trailer_channel_wear_wheels.7") ||
                    streq(macro, "trailer_channel_wear_wheels.8") ||
                    streq(macro, "trailer_channel_wear_wheels.9") ? trailer_channel_wear_wheels::id :
                    streq(macro, "trailer_channel_wheel_susp_deflection") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.0") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.1") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.2") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.3") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.4") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.5") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.6") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.7") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.8") ||
                    streq(macro, "trailer_channel_wheel_susp_deflection.9") ? trailer_channel_wheel_susp_deflection::id :
                    streq(macro, "trailer_channel_wheel_on_ground") ||
                    streq(macro, "trailer_channel_wheel_on_ground.0") ||
                    streq(macro, "trailer_channel_wheel_on_ground.1") ||
                    streq(macro, "trailer_channel_wheel_on_ground.2") ||
                    streq(macro, "trailer_channel_wheel_on_ground.3") ||
                    streq(macro, "trailer_channel_wheel_on_ground.4") ||
                    streq(macro, "trailer_channel_wheel_on_ground.5") ||
                    streq(macro, "trailer_channel_wheel_on_ground.6") ||
                    streq(macro, "trailer_channel_wheel_on_ground.7") ||
                    streq(macro, "trailer_channel_wheel_on_ground.8") ||
                    streq(macro, "trailer_channel_wheel_on_ground.9") ? trailer_channel_wheel_on_ground::id :
                    streq(macro, "trailer_channel_wheel_substance") ||
                    streq(macro, "trailer_channel_wheel_substance.0") ||
                    streq(macro, "trailer_channel_wheel_substance.1") ||
                    streq(macro, "trailer_channel_wheel_substance.2") ||
                    streq(macro, "trailer_channel_wheel_substance.3") ||
                    streq(macro, "trailer_channel_wheel_substance.4") ||
                    streq(macro, "trailer_channel_wheel_substance.5") ||
                    streq(macro, "trailer_channel_wheel_substance.6") ||
                    streq(macro, "trailer_channel_wheel_substance.7") ||
                    streq(macro, "trailer_channel_wheel_substance.8") ||
                    streq(macro, "trailer_channel_wheel_substance.9") ? trailer_channel_wheel_substance::id :
                    streq(macro, "trailer_channel_wheel_velocity") ||
                    streq(macro, "trailer_channel_wheel_velocity.0") ||
                    streq(macro, "trailer_channel_wheel_velocity.1") ||
                    streq(macro, "trailer_channel_wheel_velocity.2") ||
                    streq(macro, "trailer_channel_wheel_velocity.3") ||
                    streq(macro, "trailer_channel_wheel_velocity.4") ||
                    streq(macro, "trailer_channel_wheel_velocity.5") ||
                    streq(macro, "trailer_channel_wheel_velocity.6") ||
                    streq(macro, "trailer_channel_wheel_velocity.7") ||
                    streq(macro, "trailer_channel_wheel_velocity.8") ||
                    streq(macro, "trailer_channel_wheel_velocity.9") ? trailer_channel_wheel_velocity::id :
                    streq(macro, "trailer_channel_wheel_steering") ||
                    streq(macro, "trailer_channel_wheel_steering.0") ||
                    streq(macro, "trailer_channel_wheel_steering.1") ||
                    streq(macro, "trailer_channel_wheel_steering.2") ||
                    streq(macro, "trailer_channel_wheel_steering.3") ||
                    streq(macro, "trailer_channel_wheel_steering.4") ||
                    streq(macro, "trailer_channel_wheel_steering.5") ||
                    streq(macro, "trailer_channel_wheel_steering.6") ||
                    streq(macro, "trailer_channel_wheel_steering.7") ||
                    streq(macro, "trailer_channel_wheel_steering.8") ||
                    streq(macro, "trailer_channel_wheel_steering.9") ? trailer_channel_wheel_steering::id :
                    streq(macro, "trailer_channel_wheel_rotation") ||
                    streq(macro, "trailer_channel_wheel_rotation.0") ||
                    streq(macro, "trailer_channel_wheel_rotation.1") ||
                    streq(macro, "trailer_channel_wheel_rotation.2") ||
                    streq(macro, "trailer_channel_wheel_rotation.3") ||
                    streq(macro, "trailer_channel_wheel_rotation.4") ||
                    streq(macro, "trailer_channel_wheel_rotation.5") ||
                    streq(macro, "trailer_channel_wheel_rotation.6") ||
                    streq(macro, "trailer_channel_wheel_rotation.7") ||
                    streq(macro, "trailer_channel_wheel_rotation.8") ||
                    streq(macro, "trailer_channel_wheel_rotation.9") ? trailer_channel_wheel_rotation::id :
                    streq(macro, "trailer_channel_wheel_lift") ||
                    streq(macro, "trailer_channel_wheel_lift.0") ||
                    streq(macro, "trailer_channel_wheel_lift.1") ||
                    streq(macro, "trailer_channel_wheel_lift.2") ||
                    streq(macro, "trailer_channel_wheel_lift.3") ||
                    streq(macro, "trailer_channel_wheel_lift.4") ||
                    streq(macro, "trailer_channel_wheel_lift.5") ||
                    streq(macro, "trailer_channel_wheel_lift.6") ||
                    streq(macro, "trailer_channel_wheel_lift.7") ||
                    streq(macro, "trailer_channel_wheel_lift.8") ||
                    streq(macro, "trailer_channel_wheel_lift.9") ? trailer_channel_wheel_lift::id :
                    streq(macro, "trailer_channel_wheel_lift_offset") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.0") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.1") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.2") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.3") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.4") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.5") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.6") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.7") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.8") ||
                    streq(macro, "trailer_channel_wheel_lift_offset.9") ? trailer_channel_wheel_lift_offset::id :
                streq(macro, "truck_channel_world_placement") || streq(macro, truck_channel_world_placement::macro) ? truck_channel_world_placement::id :
                streq(macro, "truck_channel_local_linear_velocity") || streq(macro, truck_channel_local_linear_velocity::macro) ? truck_channel_local_linear_velocity::id :
                streq(macro, "truck_channel_local_angular_velocity") || streq(macro, truck_channel_local_angular_velocity::macro) ? truck_channel_local_angular_velocity::id :
                streq(macro, "truck_channel_local_linear_acceleration") || streq(macro, truck_channel_local_linear_acceleration::macro) ? truck_channel_local_linear_acceleration::id :
                streq(macro, "truck_channel_local_angular_acceleration") || streq(macro, truck_channel_local_angular_acceleration::macro) ? truck_channel_local_angular_acceleration::id :
                streq(macro, "truck_channel_cabin_offset") || streq(macro, truck_channel_cabin_offset::macro) ? truck_channel_cabin_offset::id :
                streq(macro, "truck_channel_cabin_angular_velocity") || streq(macro, truck_channel_cabin_angular_velocity::macro) ? truck_channel_cabin_angular_velocity::id :
                streq(macro, "truck_channel_cabin_angular_acceleration") || streq(macro, truck_channel_cabin_angular_acceleration::macro) ? truck_channel_cabin_angular_acceleration::id :
                streq(macro, "truck_channel_head_offset") || streq(macro, truck_channel_head_offset::macro) ? truck_channel_head_offset::id :
                streq(macro, "truck_channel_speed") || streq(macro, truck_channel_speed::macro) ? truck_channel_speed::id :
                streq(macro, "truck_channel_engine_rpm") || streq(macro, truck_channel_engine_rpm::macro) ? truck_channel_engine_rpm::id :
                streq(macro, "truck_channel_engine_gear") || streq(macro, truck_channel_engine_gear::macro) ? truck_channel_engine_gear::id :
                streq(macro, "truck_channel_displayed_gear") || streq(macro, truck_channel_displayed_gear::macro) ? truck_channel_displayed_gear::id :
                streq(macro, "truck_channel_input_steering") || streq(macro, truck_channel_input_steering::macro) ? truck_channel_input_steering::id :
                streq(macro, "truck_channel_input_throttle") || streq(macro, truck_channel_input_throttle::macro) ? truck_channel_input_throttle::id :
                streq(macro, "truck_channel_input_brake") || streq(macro, truck_channel_input_brake::macro) ? truck_channel_input_brake::id :
                streq(macro, "truck_channel_input_clutch") || streq(macro, truck_channel_input_clutch::macro) ? truck_channel_input_clutch::id :
                streq(macro, "truck_channel_effective_steering") || streq(macro, truck_channel_effective_steering::macro) ? truck_channel_effective_steering::id :
                streq(macro, "truck_channel_effective_throttle") || streq(macro, truck_channel_effective_throttle::macro) ? truck_channel_effective_throttle::id :
                streq(macro, "truck_channel_effective_brake") || streq(macro, truck_channel_effective_brake::macro) ? truck_channel_effective_brake::id :
                streq(macro, "truck_channel_effective_clutch") || streq(macro, truck_channel_effective_clutch::macro) ? truck_channel_effective_clutch::id :
                streq(macro, "truck_channel_cruise_control") || streq(macro, truck_channel_cruise_control::macro) ? truck_channel_cruise_control::id :
                streq(macro, "truck_channel_hshifter_slot") || streq(macro, truck_channel_hshifter_slot::macro) ? truck_channel_hshifter_slot::id :
                streq(macro, "truck_channel_hshifter_selector") || streq(macro, truck_channel_hshifter_selector::macro) ? truck_channel_hshifter_selector::id :
                streq(macro, "truck_channel_parking_brake") || streq(macro, truck_channel_parking_brake::macro) ? truck_channel_parking_brake::id :
                streq(macro, "truck_channel_motor_brake") || streq(macro, truck_channel_motor_brake::macro) ? truck_channel_motor_brake::id :
                streq(macro, "truck_channel_retarder_level") || streq(macro, truck_channel_retarder_level::macro) ? truck_channel_retarder_level::id :
                streq(macro, "truck_channel_brake_air_pressure") || streq(macro, truck_channel_brake_air_pressure::macro) ? truck_channel_brake_air_pressure::id :
                streq(macro, "truck_channel_brake_air_pressure_warning") || streq(macro, truck_channel_brake_air_pressure_warning::macro) ? truck_channel_brake_air_pressure_warning::id :
                streq(macro, "truck_channel_brake_air_pressure_emergency") || streq(macro, truck_channel_brake_air_pressure_emergency::macro) ? truck_channel_brake_air_pressure_emergency::id :
                streq(macro, "truck_channel_brake_temperature") || streq(macro, truck_channel_brake_temperature::macro) ? truck_channel_brake_temperature::id :
                streq(macro, "truck_channel_fuel") || streq(macro, truck_channel_fuel::macro) ? truck_channel_fuel::id :
                streq(macro, "truck_channel_fuel_warning") || streq(macro, truck_channel_fuel_warning::macro) ? truck_channel_fuel_warning::id :
                streq(macro, "truck_channel_fuel_average_consumption") || streq(macro, truck_channel_fuel_average_consumption::macro) ? truck_channel_fuel_average_consumption::id :
                streq(macro, "truck_channel_fuel_range") || streq(macro, truck_channel_fuel_range::macro) ? truck_channel_fuel_range::id :
                streq(macro, "truck_channel_adblue") || streq(macro, truck_channel_adblue::macro) ? truck_channel_adblue::id :
                streq(macro, "truck_channel_adblue_warning") || streq(macro, truck_channel_adblue_warning::macro) ? truck_channel_adblue_warning::id :
                streq(macro, "truck_channel_oil_pressure") || streq(macro, truck_channel_oil_pressure::macro) ? truck_channel_oil_pressure::id :
                streq(macro, "truck_channel_oil_pressure_warning") || streq(macro, truck_channel_oil_pressure_warning::macro) ? truck_channel_oil_pressure_warning::id :
                streq(macro, "truck_channel_oil_temperature") || streq(macro, truck_channel_oil_temperature::macro) ? truck_channel_oil_temperature::id :
                streq(macro, "truck_channel_water_temperature") || streq(macro, truck_channel_water_temperature::macro) ? truck_channel_water_temperature::id :
                streq(macro, "truck_channel_water_temperature_warning") || streq(macro, truck_channel_water_temperature_warning::macro) ? truck_channel_water_temperature_warning::id :
                streq(macro, "truck_channel_battery_voltage") || streq(macro, truck_channel_battery_voltage::macro) ? truck_channel_battery_voltage::id :
                streq(macro, "truck_channel_battery_voltage_warning") || streq(macro, truck_channel_battery_voltage_warning::macro) ? truck_channel_battery_voltage_warning::id :
                streq(macro, "truck_channel_electric_enabled") || streq(macro, truck_channel_electric_enabled::macro) ? truck_channel_electric_enabled::id :
                streq(macro, "truck_channel_engine_enabled") || streq(macro, truck_channel_engine_enabled::macro) ? truck_channel_engine_enabled::id :
                streq(macro, "truck_channel_lblinker") || streq(macro, truck_channel_lblinker::macro) ? truck_channel_lblinker::id :
                streq(macro, "truck_channel_rblinker") || streq(macro, truck_channel_rblinker::macro) ? truck_channel_rblinker::id :
                streq(macro, "truck_channel_hazard_warning") || streq(macro, truck_channel_hazard_warning::macro) ? truck_channel_hazard_warning::id :
                streq(macro, "truck_channel_light_lblinker") || streq(macro, truck_channel_light_lblinker::macro) ? truck_channel_light_lblinker::id :
                streq(macro, "truck_channel_light_rblinker") || streq(macro, truck_channel_light_rblinker::macro) ? truck_channel_light_rblinker::id :
                streq(macro, "truck_channel_light_parking") || streq(macro, truck_channel_light_parking::macro) ? truck_channel_light_parking::id :
                streq(macro, "truck_channel_light_low_beam") || streq(macro, truck_channel_light_low_beam::macro) ? truck_channel_light_low_beam::id :
                streq(macro, "truck_channel_light_high_beam") || streq(macro, truck_channel_light_high_beam::macro) ? truck_channel_light_high_beam::id :
                streq(macro, "truck_channel_light_aux_front") || streq(macro, truck_channel_light_aux_front::macro) ? truck_channel_light_aux_front::id :
                streq(macro, "truck_channel_light_aux_roof") || streq(macro, truck_channel_light_aux_roof::macro) ? truck_channel_light_aux_roof::id :
                streq(macro, "truck_channel_light_beacon") || streq(macro, truck_channel_light_beacon::macro) ? truck_channel_light_beacon::id :
                streq(macro, "truck_channel_light_brake") || streq(macro, truck_channel_light_brake::macro) ? truck_channel_light_brake::id :
                streq(macro, "truck_channel_light_reverse") || streq(macro, truck_channel_light_reverse::macro) ? truck_channel_light_reverse::id :
                streq(macro, "truck_channel_wipers") || streq(macro, truck_channel_wipers::macro) ? truck_channel_wipers::id :
                streq(macro, "truck_channel_dashboard_backlight") || streq(macro, truck_channel_dashboard_backlight::macro) ? truck_channel_dashboard_backlight::id :
                streq(macro, "truck_channel_differential_lock") || streq(macro, truck_channel_differential_lock::macro) ? truck_channel_differential_lock::id :
                streq(macro, "truck_channel_lift_axle") || streq(macro, truck_channel_lift_axle::macro) ? truck_channel_lift_axle::id :
                streq(macro, "truck_channel_lift_axle_indicator") || streq(macro, truck_channel_lift_axle_indicator::macro) ? truck_channel_lift_axle_indicator::id :
                streq(macro, "truck_channel_trailer_lift_axle") || streq(macro, truck_channel_trailer_lift_axle::macro) ? truck_channel_trailer_lift_axle::id :
                streq(macro, "truck_channel_trailer_lift_axle_indicator") || streq(macro, truck_channel_trailer_lift_axle_indicator::macro) ? truck_channel_trailer_lift_axle_indicator::id :
                streq(macro, "truck_channel_wear_engine") || streq(macro, truck_channel_wear_engine::macro) ? truck_channel_wear_engine::id :
                streq(macro, "truck_channel_wear_transmission") || streq(macro, truck_channel_wear_transmission::macro) ? truck_channel_wear_transmission::id :
                streq(macro, "truck_channel_wear_cabin") || streq(macro, truck_channel_wear_cabin::macro) ? truck_channel_wear_cabin::id :
                streq(macro, "truck_channel_wear_chassis") || streq(macro, truck_channel_wear_chassis::macro) ? truck_channel_wear_chassis::id :
                streq(macro, "truck_channel_wear_wheels") || streq(macro, truck_channel_wear_wheels::macro) ? truck_channel_wear_wheels::id :
                streq(macro, "truck_channel_odometer") || streq(macro, truck_channel_odometer::macro) ? truck_channel_odometer::id :
                streq(macro, "truck_channel_navigation_distance") || streq(macro, truck_channel_navigation_distance::macro) ? truck_channel_navigation_distance::id :
                streq(macro, "truck_channel_navigation_time") || streq(macro, truck_channel_navigation_time::macro) ? truck_channel_navigation_time::id :
                streq(macro, "truck_channel_navigation_speed_limit") || streq(macro, truck_channel_navigation_speed_limit::macro) ? truck_channel_navigation_speed_limit::id :
                streq(macro, "truck_channel_wheel_susp_deflection") || streq(macro, truck_channel_wheel_susp_deflection::macro) ? truck_channel_wheel_susp_deflection::id :
                streq(macro, "truck_channel_wheel_on_ground") || streq(macro, truck_channel_wheel_on_ground::macro) ? truck_channel_wheel_on_ground::id :
                streq(macro, "truck_channel_wheel_substance") || streq(macro, truck_channel_wheel_substance::macro) ? truck_channel_wheel_substance::id :
                streq(macro, "truck_channel_wheel_velocity") || streq(macro, truck_channel_wheel_velocity::macro) ? truck_channel_wheel_velocity::id :
                streq(macro, "truck_channel_wheel_steering") || streq(macro, truck_channel_wheel_steering::macro) ? truck_channel_wheel_steering::id :
                streq(macro, "truck_channel_wheel_rotation") || streq(macro, truck_channel_wheel_rotation::macro) ? truck_channel_wheel_rotation::id :
                streq(macro, "truck_channel_wheel_lift") || streq(macro, truck_channel_wheel_lift::macro) ? truck_channel_wheel_lift::id :
                streq(macro, "truck_channel_wheel_lift_offset") || streq(macro, truck_channel_wheel_lift_offset::macro) ? truck_channel_wheel_lift_offset::id :
                LIFETIME_INVALID_ID;
        }

        constexpr const char* const name_of(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::master: return "master";
                case telemetry_id::configuration: return "configuration";
                case telemetry_id::gameplay: return "gameplay";
                case telemetry_id::channels: return "channels";
                case telemetry_id::general: return "general";
                case telemetry_id::truck: return "truck";
                case telemetry_id::trailer: return "trailer";
                case telemetry_id::configuration_substances_info: return "configuration_substances_info";
                case telemetry_id::configuration_controls_info: return "configuration_controls_info";
                case telemetry_id::configuration_hshifter_info: return "configuration_hshifter_info";
                case telemetry_id::configuration_truck_info: return "configuration_truck_info";
                case telemetry_id::configuration_trailer_info: return "configuration_trailer_info";
                case telemetry_id::configuration_job_info: return "configuration_job_info";
                case telemetry_id::gameplay_job_cancelled_info: return "gameplay_job_cancelled_info";
                case telemetry_id::gameplay_job_delivered_info: return "gameplay_job_delivered_info";
                case telemetry_id::gameplay_player_fined_info: return "gameplay_player_fined_info";
                case telemetry_id::gameplay_player_tollgate_paid_info: return "gameplay_player_tollgate_paid_info";
                case telemetry_id::gameplay_player_use_ferry_info: return "gameplay_player_use_ferry_info";
                case telemetry_id::gameplay_player_use_train_info: return "gameplay_player_use_train_info";
                case telemetry_id::channel_paused: return "channel_paused";
                case telemetry_id::channel_local_scale: return "channel_local_scale";
                case telemetry_id::channel_game_time: return "channel_game_time";
                case telemetry_id::channel_multiplayer_time_offset: return "channel_multiplayer_time_offset";
                case telemetry_id::channel_next_rest_stop: return "channel_next_rest_stop";
                case telemetry_id::job_channel_cargo_damage: return "job_channel_cargo_damage";
                case telemetry_id::trailer_channel_connected: return "trailer_channel_connected";
                case telemetry_id::trailer_channel_cargo_damage: return "trailer_channel_cargo_damage";
                case telemetry_id::trailer_channel_world_placement: return "trailer_channel_world_placement";
                case telemetry_id::trailer_channel_local_linear_velocity: return "trailer_channel_local_linear_velocity";
                case telemetry_id::trailer_channel_local_angular_velocity: return "trailer_channel_local_angular_velocity";
                case telemetry_id::trailer_channel_local_linear_acceleration: return "trailer_channel_local_linear_acceleration";
                case telemetry_id::trailer_channel_local_angular_acceleration: return "trailer_channel_local_angular_acceleration";
                case telemetry_id::trailer_channel_wear_body: return "trailer_channel_wear_body";
                case telemetry_id::trailer_channel_wear_chassis: return "trailer_channel_wear_chassis";
                case telemetry_id::trailer_channel_wear_wheels: return "trailer_channel_wear_wheels";
                case telemetry_id::trailer_channel_wheel_susp_deflection: return "trailer_channel_wheel_susp_deflection";
                case telemetry_id::trailer_channel_wheel_on_ground: return "trailer_channel_wheel_on_ground";
                case telemetry_id::trailer_channel_wheel_substance: return "trailer_channel_wheel_substance";
                case telemetry_id::trailer_channel_wheel_velocity: return "trailer_channel_wheel_velocity";
                case telemetry_id::trailer_channel_wheel_steering: return "trailer_channel_wheel_steering";
                case telemetry_id::trailer_channel_wheel_rotation: return "trailer_channel_wheel_rotation";
                case telemetry_id::trailer_channel_wheel_lift: return "trailer_channel_wheel_lift";
                case telemetry_id::trailer_channel_wheel_lift_offset: return "trailer_channel_wheel_lift_offset";
                case telemetry_id::truck_channel_world_placement: return "truck_channel_world_placement";
                case telemetry_id::truck_channel_local_linear_velocity: return "truck_channel_local_linear_velocity";
                case telemetry_id::truck_channel_local_angular_velocity: return "truck_channel_local_angular_velocity";
                case telemetry_id::truck_channel_local_linear_acceleration: return "truck_channel_local_linear_acceleration";
                case telemetry_id::truck_channel_local_angular_acceleration: return "truck_channel_local_angular_acceleration";
                case telemetry_id::truck_channel_cabin_offset: return "truck_channel_cabin_offset";
                case telemetry_id::truck_channel_cabin_angular_velocity: return "truck_channel_cabin_angular_velocity";
                case telemetry_id::truck_channel_cabin_angular_acceleration: return "truck_channel_cabin_angular_acceleration";
                case telemetry_id::truck_channel_head_offset: return "truck_channel_head_offset";
                case telemetry_id::truck_channel_speed: return "truck_channel_speed";
                case telemetry_id::truck_channel_engine_rpm: return "truck_channel_engine_rpm";
                case telemetry_id::truck_channel_engine_gear: return "truck_channel_engine_gear";
                case telemetry_id::truck_channel_displayed_gear: return "truck_channel_displayed_gear";
                case telemetry_id::truck_channel_input_steering: return "truck_channel_input_steering";
                case telemetry_id::truck_channel_input_throttle: return "truck_channel_input_throttle";
                case telemetry_id::truck_channel_input_brake: return "truck_channel_input_brake";
                case telemetry_id::truck_channel_input_clutch: return "truck_channel_input_clutch";
                case telemetry_id::truck_channel_effective_steering: return "truck_channel_effective_steering";
                case telemetry_id::truck_channel_effective_throttle: return "truck_channel_effective_throttle";
                case telemetry_id::truck_channel_effective_brake: return "truck_channel_effective_brake";
                case telemetry_id::truck_channel_effective_clutch: return "truck_channel_effective_clutch";
                case telemetry_id::truck_channel_cruise_control: return "truck_channel_cruise_control";
                case telemetry_id::truck_channel_hshifter_slot: return "truck_channel_hshifter_slot";
                case telemetry_id::truck_channel_hshifter_selector: return "truck_channel_hshifter_selector";
                case telemetry_id::truck_channel_parking_brake: return "truck_channel_parking_brake";
                case telemetry_id::truck_channel_motor_brake: return "truck_channel_motor_brake";
                case telemetry_id::truck_channel_retarder_level: return "truck_channel_retarder_level";
                case telemetry_id::truck_channel_brake_air_pressure: return "truck_channel_brake_air_pressure";
                case telemetry_id::truck_channel_brake_air_pressure_warning: return "truck_channel_brake_air_pressure_warning";
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return "truck_channel_brake_air_pressure_emergency";
                case telemetry_id::truck_channel_brake_temperature: return "truck_channel_brake_temperature";
                case telemetry_id::truck_channel_fuel: return "truck_channel_fuel";
                case telemetry_id::truck_channel_fuel_warning: return "truck_channel_fuel_warning";
                case telemetry_id::truck_channel_fuel_average_consumption: return "truck_channel_fuel_average_consumption";
                case telemetry_id::truck_channel_fuel_range: return "truck_channel_fuel_range";
                case telemetry_id::truck_channel_adblue: return "truck_channel_adblue";
                case telemetry_id::truck_channel_adblue_warning: return "truck_channel_adblue_warning";
                case telemetry_id::truck_channel_oil_pressure: return "truck_channel_oil_pressure";
                case telemetry_id::truck_channel_oil_pressure_warning: return "truck_channel_oil_pressure_warning";
                case telemetry_id::truck_channel_oil_temperature: return "truck_channel_oil_temperature";
                case telemetry_id::truck_channel_water_temperature: return "truck_channel_water_temperature";
                case telemetry_id::truck_channel_water_temperature_warning: return "truck_channel_water_temperature_warning";
                case telemetry_id::truck_channel_battery_voltage: return "truck_channel_battery_voltage";
                case telemetry_id::truck_channel_battery_voltage_warning: return "truck_channel_battery_voltage_warning";
                case telemetry_id::truck_channel_electric_enabled: return "truck_channel_electric_enabled";
                case telemetry_id::truck_channel_engine_enabled: return "truck_channel_engine_enabled";
                case telemetry_id::truck_channel_lblinker: return "truck_channel_lblinker";
                case telemetry_id::truck_channel_rblinker: return "truck_channel_rblinker";
                case telemetry_id::truck_channel_hazard_warning: return "truck_channel_hazard_warning";
                case telemetry_id::truck_channel_light_lblinker: return "truck_channel_light_lblinker";
                case telemetry_id::truck_channel_light_rblinker: return "truck_channel_light_rblinker";
                case telemetry_id::truck_channel_light_parking: return "truck_channel_light_parking";
                case telemetry_id::truck_channel_light_low_beam: return "truck_channel_light_low_beam";
                case telemetry_id::truck_channel_light_high_beam: return "truck_channel_light_high_beam";
                case telemetry_id::truck_channel_light_aux_front: return "truck_channel_light_aux_front";
                case telemetry_id::truck_channel_light_aux_roof: return "truck_channel_light_aux_roof";
                case telemetry_id::truck_channel_light_beacon: return "truck_channel_light_beacon";
                case telemetry_id::truck_channel_light_brake: return "truck_channel_light_brake";
                case telemetry_id::truck_channel_light_reverse: return "truck_channel_light_reverse";
                case telemetry_id::truck_channel_wipers: return "truck_channel_wipers";
                case telemetry_id::truck_channel_dashboard_backlight: return "truck_channel_dashboard_backlight";
                case telemetry_id::truck_channel_differential_lock: return "truck_channel_differential_lock";
                case telemetry_id::truck_channel_lift_axle: return "truck_channel_lift_axle";
                case telemetry_id::truck_channel_lift_axle_indicator: return "truck_channel_lift_axle_indicator";
                case telemetry_id::truck_channel_trailer_lift_axle: return "truck_channel_trailer_lift_axle";
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return "truck_channel_trailer_lift_axle_indicator";
                case telemetry_id::truck_channel_wear_engine: return "truck_channel_wear_engine";
                case telemetry_id::truck_channel_wear_transmission: return "truck_channel_wear_transmission";
                case telemetry_id::truck_channel_wear_cabin: return "truck_channel_wear_cabin";
                case telemetry_id::truck_channel_wear_chassis: return "truck_channel_wear_chassis";
                case telemetry_id::truck_channel_wear_wheels: return "truck_channel_wear_wheels";
                case telemetry_id::truck_channel_odometer: return "truck_channel_odometer";
                case telemetry_id::truck_channel_navigation_distance: return "truck_channel_navigation_distance";
                case telemetry_id::truck_channel_navigation_time: return "truck_channel_navigation_time";
                case telemetry_id::truck_channel_navigation_speed_limit: return "truck_channel_navigation_speed_limit";
                case telemetry_id::truck_channel_wheel_susp_deflection: return "truck_channel_wheel_susp_deflection";
                case telemetry_id::truck_channel_wheel_on_ground: return "truck_channel_wheel_on_ground";
                case telemetry_id::truck_channel_wheel_substance: return "truck_channel_wheel_substance";
                case telemetry_id::truck_channel_wheel_velocity: return "truck_channel_wheel_velocity";
                case telemetry_id::truck_channel_wheel_steering: return "truck_channel_wheel_steering";
                case telemetry_id::truck_channel_wheel_rotation: return "truck_channel_wheel_rotation";
                case telemetry_id::truck_channel_wheel_lift: return "truck_channel_wheel_lift";
                case telemetry_id::truck_channel_wheel_lift_offset: return "truck_channel_wheel_lift_offset";
                default: return nullptr;
            }
        }

        constexpr const uint32_t size_of(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::master: return sizeof(master::storage_type);
                case telemetry_id::configuration: return sizeof(configuration::storage_type);
                case telemetry_id::gameplay: return sizeof(gameplay::storage_type);
                case telemetry_id::channels: return sizeof(channels::storage_type);
                case telemetry_id::general: return sizeof(general::storage_type);
                case telemetry_id::truck: return sizeof(truck::storage_type);
                case telemetry_id::trailer: return sizeof(trailer::storage_type);
                case telemetry_id::configuration_substances_info: return sizeof(configuration_substances_info::storage_type);
                case telemetry_id::configuration_controls_info: return sizeof(configuration_controls_info::storage_type);
                case telemetry_id::configuration_hshifter_info: return sizeof(configuration_hshifter_info::storage_type);
                case telemetry_id::configuration_truck_info: return sizeof(configuration_truck_info::storage_type);
                case telemetry_id::configuration_trailer_info: return sizeof(configuration_trailer_info::storage_type);
                case telemetry_id::configuration_job_info: return sizeof(configuration_job_info::storage_type);
                case telemetry_id::gameplay_job_cancelled_info: return sizeof(gameplay_job_cancelled_info::storage_type);
                case telemetry_id::gameplay_job_delivered_info: return sizeof(gameplay_job_delivered_info::storage_type);
                case telemetry_id::gameplay_player_fined_info: return sizeof(gameplay_player_fined_info::storage_type);
                case telemetry_id::gameplay_player_tollgate_paid_info: return sizeof(gameplay_player_tollgate_paid_info::storage_type);
                case telemetry_id::gameplay_player_use_ferry_info: return sizeof(gameplay_player_use_ferry_info::storage_type);
                case telemetry_id::gameplay_player_use_train_info: return sizeof(gameplay_player_use_train_info::storage_type);
                case telemetry_id::channel_paused: return sizeof(channel_paused::storage_type);
                case telemetry_id::channel_local_scale: return sizeof(channel_local_scale::storage_type);
                case telemetry_id::channel_game_time: return sizeof(channel_game_time::storage_type);
                case telemetry_id::channel_multiplayer_time_offset: return sizeof(channel_multiplayer_time_offset::storage_type);
                case telemetry_id::channel_next_rest_stop: return sizeof(channel_next_rest_stop::storage_type);
                case telemetry_id::job_channel_cargo_damage: return sizeof(job_channel_cargo_damage::storage_type);
                case telemetry_id::trailer_channel_connected: return sizeof(trailer_channel_connected::storage_type);
                case telemetry_id::trailer_channel_cargo_damage: return sizeof(trailer_channel_cargo_damage::storage_type);
                case telemetry_id::trailer_channel_world_placement: return sizeof(trailer_channel_world_placement::storage_type);
                case telemetry_id::trailer_channel_local_linear_velocity: return sizeof(trailer_channel_local_linear_velocity::storage_type);
                case telemetry_id::trailer_channel_local_angular_velocity: return sizeof(trailer_channel_local_angular_velocity::storage_type);
                case telemetry_id::trailer_channel_local_linear_acceleration: return sizeof(trailer_channel_local_linear_acceleration::storage_type);
                case telemetry_id::trailer_channel_local_angular_acceleration: return sizeof(trailer_channel_local_angular_acceleration::storage_type);
                case telemetry_id::trailer_channel_wear_body: return sizeof(trailer_channel_wear_body::storage_type);
                case telemetry_id::trailer_channel_wear_chassis: return sizeof(trailer_channel_wear_chassis::storage_type);
                case telemetry_id::trailer_channel_wear_wheels: return sizeof(trailer_channel_wear_wheels::storage_type);
                case telemetry_id::trailer_channel_wheel_susp_deflection: return sizeof(trailer_channel_wheel_susp_deflection::storage_type);
                case telemetry_id::trailer_channel_wheel_on_ground: return sizeof(trailer_channel_wheel_on_ground::storage_type);
                case telemetry_id::trailer_channel_wheel_substance: return sizeof(trailer_channel_wheel_substance::storage_type);
                case telemetry_id::trailer_channel_wheel_velocity: return sizeof(trailer_channel_wheel_velocity::storage_type);
                case telemetry_id::trailer_channel_wheel_steering: return sizeof(trailer_channel_wheel_steering::storage_type);
                case telemetry_id::trailer_channel_wheel_rotation: return sizeof(trailer_channel_wheel_rotation::storage_type);
                case telemetry_id::trailer_channel_wheel_lift: return sizeof(trailer_channel_wheel_lift::storage_type);
                case telemetry_id::trailer_channel_wheel_lift_offset: return sizeof(trailer_channel_wheel_lift_offset::storage_type);
                case telemetry_id::truck_channel_world_placement: return sizeof(truck_channel_world_placement::storage_type);
                case telemetry_id::truck_channel_local_linear_velocity: return sizeof(truck_channel_local_linear_velocity::storage_type);
                case telemetry_id::truck_channel_local_angular_velocity: return sizeof(truck_channel_local_angular_velocity::storage_type);
                case telemetry_id::truck_channel_local_linear_acceleration: return sizeof(truck_channel_local_linear_acceleration::storage_type);
                case telemetry_id::truck_channel_local_angular_acceleration: return sizeof(truck_channel_local_angular_acceleration::storage_type);
                case telemetry_id::truck_channel_cabin_offset: return sizeof(truck_channel_cabin_offset::storage_type);
                case telemetry_id::truck_channel_cabin_angular_velocity: return sizeof(truck_channel_cabin_angular_velocity::storage_type);
                case telemetry_id::truck_channel_cabin_angular_acceleration: return sizeof(truck_channel_cabin_angular_acceleration::storage_type);
                case telemetry_id::truck_channel_head_offset: return sizeof(truck_channel_head_offset::storage_type);
                case telemetry_id::truck_channel_speed: return sizeof(truck_channel_speed::storage_type);
                case telemetry_id::truck_channel_engine_rpm: return sizeof(truck_channel_engine_rpm::storage_type);
                case telemetry_id::truck_channel_engine_gear: return sizeof(truck_channel_engine_gear::storage_type);
                case telemetry_id::truck_channel_displayed_gear: return sizeof(truck_channel_displayed_gear::storage_type);
                case telemetry_id::truck_channel_input_steering: return sizeof(truck_channel_input_steering::storage_type);
                case telemetry_id::truck_channel_input_throttle: return sizeof(truck_channel_input_throttle::storage_type);
                case telemetry_id::truck_channel_input_brake: return sizeof(truck_channel_input_brake::storage_type);
                case telemetry_id::truck_channel_input_clutch: return sizeof(truck_channel_input_clutch::storage_type);
                case telemetry_id::truck_channel_effective_steering: return sizeof(truck_channel_effective_steering::storage_type);
                case telemetry_id::truck_channel_effective_throttle: return sizeof(truck_channel_effective_throttle::storage_type);
                case telemetry_id::truck_channel_effective_brake: return sizeof(truck_channel_effective_brake::storage_type);
                case telemetry_id::truck_channel_effective_clutch: return sizeof(truck_channel_effective_clutch::storage_type);
                case telemetry_id::truck_channel_cruise_control: return sizeof(truck_channel_cruise_control::storage_type);
                case telemetry_id::truck_channel_hshifter_slot: return sizeof(truck_channel_hshifter_slot::storage_type);
                case telemetry_id::truck_channel_hshifter_selector: return sizeof(truck_channel_hshifter_selector::storage_type);
                case telemetry_id::truck_channel_parking_brake: return sizeof(truck_channel_parking_brake::storage_type);
                case telemetry_id::truck_channel_motor_brake: return sizeof(truck_channel_motor_brake::storage_type);
                case telemetry_id::truck_channel_retarder_level: return sizeof(truck_channel_retarder_level::storage_type);
                case telemetry_id::truck_channel_brake_air_pressure: return sizeof(truck_channel_brake_air_pressure::storage_type);
                case telemetry_id::truck_channel_brake_air_pressure_warning: return sizeof(truck_channel_brake_air_pressure_warning::storage_type);
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return sizeof(truck_channel_brake_air_pressure_emergency::storage_type);
                case telemetry_id::truck_channel_brake_temperature: return sizeof(truck_channel_brake_temperature::storage_type);
                case telemetry_id::truck_channel_fuel: return sizeof(truck_channel_fuel::storage_type);
                case telemetry_id::truck_channel_fuel_warning: return sizeof(truck_channel_fuel_warning::storage_type);
                case telemetry_id::truck_channel_fuel_average_consumption: return sizeof(truck_channel_fuel_average_consumption::storage_type);
                case telemetry_id::truck_channel_fuel_range: return sizeof(truck_channel_fuel_range::storage_type);
                case telemetry_id::truck_channel_adblue: return sizeof(truck_channel_adblue::storage_type);
                case telemetry_id::truck_channel_adblue_warning: return sizeof(truck_channel_adblue_warning::storage_type);
                case telemetry_id::truck_channel_oil_pressure: return sizeof(truck_channel_oil_pressure::storage_type);
                case telemetry_id::truck_channel_oil_pressure_warning: return sizeof(truck_channel_oil_pressure_warning::storage_type);
                case telemetry_id::truck_channel_oil_temperature: return sizeof(truck_channel_oil_temperature::storage_type);
                case telemetry_id::truck_channel_water_temperature: return sizeof(truck_channel_water_temperature::storage_type);
                case telemetry_id::truck_channel_water_temperature_warning: return sizeof(truck_channel_water_temperature_warning::storage_type);
                case telemetry_id::truck_channel_battery_voltage: return sizeof(truck_channel_battery_voltage::storage_type);
                case telemetry_id::truck_channel_battery_voltage_warning: return sizeof(truck_channel_battery_voltage_warning::storage_type);
                case telemetry_id::truck_channel_electric_enabled: return sizeof(truck_channel_electric_enabled::storage_type);
                case telemetry_id::truck_channel_engine_enabled: return sizeof(truck_channel_engine_enabled::storage_type);
                case telemetry_id::truck_channel_lblinker: return sizeof(truck_channel_lblinker::storage_type);
                case telemetry_id::truck_channel_rblinker: return sizeof(truck_channel_rblinker::storage_type);
                case telemetry_id::truck_channel_hazard_warning: return sizeof(truck_channel_hazard_warning::storage_type);
                case telemetry_id::truck_channel_light_lblinker: return sizeof(truck_channel_light_lblinker::storage_type);
                case telemetry_id::truck_channel_light_rblinker: return sizeof(truck_channel_light_rblinker::storage_type);
                case telemetry_id::truck_channel_light_parking: return sizeof(truck_channel_light_parking::storage_type);
                case telemetry_id::truck_channel_light_low_beam: return sizeof(truck_channel_light_low_beam::storage_type);
                case telemetry_id::truck_channel_light_high_beam: return sizeof(truck_channel_light_high_beam::storage_type);
                case telemetry_id::truck_channel_light_aux_front: return sizeof(truck_channel_light_aux_front::storage_type);
                case telemetry_id::truck_channel_light_aux_roof: return sizeof(truck_channel_light_aux_roof::storage_type);
                case telemetry_id::truck_channel_light_beacon: return sizeof(truck_channel_light_beacon::storage_type);
                case telemetry_id::truck_channel_light_brake: return sizeof(truck_channel_light_brake::storage_type);
                case telemetry_id::truck_channel_light_reverse: return sizeof(truck_channel_light_reverse::storage_type);
                case telemetry_id::truck_channel_wipers: return sizeof(truck_channel_wipers::storage_type);
                case telemetry_id::truck_channel_dashboard_backlight: return sizeof(truck_channel_dashboard_backlight::storage_type);
                case telemetry_id::truck_channel_differential_lock: return sizeof(truck_channel_differential_lock::storage_type);
                case telemetry_id::truck_channel_lift_axle: return sizeof(truck_channel_lift_axle::storage_type);
                case telemetry_id::truck_channel_lift_axle_indicator: return sizeof(truck_channel_lift_axle_indicator::storage_type);
                case telemetry_id::truck_channel_trailer_lift_axle: return sizeof(truck_channel_trailer_lift_axle::storage_type);
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return sizeof(truck_channel_trailer_lift_axle_indicator::storage_type);
                case telemetry_id::truck_channel_wear_engine: return sizeof(truck_channel_wear_engine::storage_type);
                case telemetry_id::truck_channel_wear_transmission: return sizeof(truck_channel_wear_transmission::storage_type);
                case telemetry_id::truck_channel_wear_cabin: return sizeof(truck_channel_wear_cabin::storage_type);
                case telemetry_id::truck_channel_wear_chassis: return sizeof(truck_channel_wear_chassis::storage_type);
                case telemetry_id::truck_channel_wear_wheels: return sizeof(truck_channel_wear_wheels::storage_type);
                case telemetry_id::truck_channel_odometer: return sizeof(truck_channel_odometer::storage_type);
                case telemetry_id::truck_channel_navigation_distance: return sizeof(truck_channel_navigation_distance::storage_type);
                case telemetry_id::truck_channel_navigation_time: return sizeof(truck_channel_navigation_time::storage_type);
                case telemetry_id::truck_channel_navigation_speed_limit: return sizeof(truck_channel_navigation_speed_limit::storage_type);
                case telemetry_id::truck_channel_wheel_susp_deflection: return sizeof(truck_channel_wheel_susp_deflection::storage_type);
                case telemetry_id::truck_channel_wheel_on_ground: return sizeof(truck_channel_wheel_on_ground::storage_type);
                case telemetry_id::truck_channel_wheel_substance: return sizeof(truck_channel_wheel_substance::storage_type);
                case telemetry_id::truck_channel_wheel_velocity: return sizeof(truck_channel_wheel_velocity::storage_type);
                case telemetry_id::truck_channel_wheel_steering: return sizeof(truck_channel_wheel_steering::storage_type);
                case telemetry_id::truck_channel_wheel_rotation: return sizeof(truck_channel_wheel_rotation::storage_type);
                case telemetry_id::truck_channel_wheel_lift: return sizeof(truck_channel_wheel_lift::storage_type);
                case telemetry_id::truck_channel_wheel_lift_offset: return sizeof(truck_channel_wheel_lift_offset::storage_type);
                default: return INVALID_SIZE;
            }
        }

        constexpr const uint32_t offset_of_latest(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::configuration_substances_info: return offsetof(configuration_substances_info::storage_type, latest);
                case telemetry_id::configuration_controls_info: return offsetof(configuration_controls_info::storage_type, latest);
                case telemetry_id::configuration_hshifter_info: return offsetof(configuration_hshifter_info::storage_type, latest);
                case telemetry_id::configuration_truck_info: return offsetof(configuration_truck_info::storage_type, latest);
                case telemetry_id::configuration_trailer_info: return offsetof(configuration_trailer_info::storage_type, latest);
                case telemetry_id::configuration_job_info: return offsetof(configuration_job_info::storage_type, latest);
                case telemetry_id::gameplay_job_cancelled_info: return offsetof(gameplay_job_cancelled_info::storage_type, latest);
                case telemetry_id::gameplay_job_delivered_info: return offsetof(gameplay_job_delivered_info::storage_type, latest);
                case telemetry_id::gameplay_player_fined_info: return offsetof(gameplay_player_fined_info::storage_type, latest);
                case telemetry_id::gameplay_player_tollgate_paid_info: return offsetof(gameplay_player_tollgate_paid_info::storage_type, latest);
                case telemetry_id::gameplay_player_use_ferry_info: return offsetof(gameplay_player_use_ferry_info::storage_type, latest);
                case telemetry_id::gameplay_player_use_train_info: return offsetof(gameplay_player_use_train_info::storage_type, latest);
                default: return INVALID_OFFSET;
            }
        }

        constexpr const uint32_t event_info_member_offset_of(const telemetry_id& id, const char* const member) {
            switch (id) {
                case telemetry_id::configuration_substances_info:
                    return
                        streq(member, "latest") ? offsetof(configuration_substances_info::storage_type, latest) :
                        streq(member, "id") ? offsetof(configuration_substances_info::storage_type, id) :
                        INVALID_OFFSET;
                case telemetry_id::configuration_controls_info:
                    return
                        streq(member, "latest") ? offsetof(configuration_controls_info::storage_type, latest) :
                        streq(member, "shifter_type") ? offsetof(configuration_controls_info::storage_type, shifter_type) :
                        INVALID_OFFSET;
                case telemetry_id::configuration_hshifter_info:
                    return
                        streq(member, "latest") ? offsetof(configuration_hshifter_info::storage_type, latest) :
                        streq(member, "selector_count") ? offsetof(configuration_hshifter_info::storage_type, selector_count) :
                        streq(member, "slot_gear") ? offsetof(configuration_hshifter_info::storage_type, slot_gear) :
                        streq(member, "slot_handle_position") ? offsetof(configuration_hshifter_info::storage_type, slot_handle_position) :
                        streq(member, "slot_selectors") ? offsetof(configuration_hshifter_info::storage_type, slot_selectors) :
                        INVALID_OFFSET;
                case telemetry_id::configuration_truck_info:
                    return
                        streq(member, "latest") ? offsetof(configuration_truck_info::storage_type, latest) :
                        streq(member, "brand_id") ? offsetof(configuration_truck_info::storage_type, brand_id) :
                        streq(member, "brand") ? offsetof(configuration_truck_info::storage_type, brand) :
                        streq(member, "id") ? offsetof(configuration_truck_info::storage_type, id) :
                        streq(member, "name") ? offsetof(configuration_truck_info::storage_type, name) :
                        streq(member, "fuel_capacity") ? offsetof(configuration_truck_info::storage_type, fuel_capacity) :
                        streq(member, "fuel_warning_factor") ? offsetof(configuration_truck_info::storage_type, fuel_warning_factor) :
                        streq(member, "adblue_capacity") ? offsetof(configuration_truck_info::storage_type, adblue_capacity) :
                        streq(member, "adblue_warning_factor") ? offsetof(configuration_truck_info::storage_type, adblue_warning_factor) :
                        streq(member, "air_pressure_warning") ? offsetof(configuration_truck_info::storage_type, air_pressure_warning) :
                        streq(member, "air_pressure_emergency") ? offsetof(configuration_truck_info::storage_type, air_pressure_emergency) :
                        streq(member, "oil_pressure_warning") ? offsetof(configuration_truck_info::storage_type, oil_pressure_warning) :
                        streq(member, "water_temperature_warning") ? offsetof(configuration_truck_info::storage_type, water_temperature_warning) :
                        streq(member, "battery_voltage_warning") ? offsetof(configuration_truck_info::storage_type, battery_voltage_warning) :
                        streq(member, "rpm_limit") ? offsetof(configuration_truck_info::storage_type, rpm_limit) :
                        streq(member, "forward_gear_count") ? offsetof(configuration_truck_info::storage_type, forward_gear_count) :
                        streq(member, "reverse_gear_count") ? offsetof(configuration_truck_info::storage_type, reverse_gear_count) :
                        streq(member, "differential_ratio") ? offsetof(configuration_truck_info::storage_type, differential_ratio) :
                        streq(member, "retarder_step_count") ? offsetof(configuration_truck_info::storage_type, retarder_step_count) :
                        streq(member, "cabin_position") ? offsetof(configuration_truck_info::storage_type, cabin_position) :
                        streq(member, "forward_ratio") ? offsetof(configuration_truck_info::storage_type, forward_ratio) :
                        streq(member, "reverse_ratio") ? offsetof(configuration_truck_info::storage_type, reverse_ratio) :
                        streq(member, "head_position") ? offsetof(configuration_truck_info::storage_type, head_position) :
                        streq(member, "hook_position") ? offsetof(configuration_truck_info::storage_type, hook_position) :
                        streq(member, "license_plate") ? offsetof(configuration_truck_info::storage_type, license_plate) :
                        streq(member, "license_plate_country") ? offsetof(configuration_truck_info::storage_type, license_plate_country) :
                        streq(member, "license_plate_country_id") ? offsetof(configuration_truck_info::storage_type, license_plate_country_id) :
                        streq(member, "wheel_count") ? offsetof(configuration_truck_info::storage_type, wheel_count) :
                        streq(member, "wheel_position") ? offsetof(configuration_truck_info::storage_type, wheel_position) :
                        streq(member, "wheel_steerable") ? offsetof(configuration_truck_info::storage_type, wheel_steerable) :
                        streq(member, "wheel_simulated") ? offsetof(configuration_truck_info::storage_type, wheel_simulated) :
                        streq(member, "wheel_radius") ? offsetof(configuration_truck_info::storage_type, wheel_radius) :
                        streq(member, "wheel_powered") ? offsetof(configuration_truck_info::storage_type, wheel_powered) :
                        streq(member, "wheel_liftable") ? offsetof(configuration_truck_info::storage_type, wheel_liftable) :
                        INVALID_OFFSET;
                case telemetry_id::configuration_trailer_info:
                    return
                        streq(member, "latest") ? offsetof(configuration_trailer_info::storage_type, latest) :
                        streq(member, "id") ? offsetof(configuration_trailer_info::storage_type, id) :
                        streq(member, "cargo_accessory_id") ? offsetof(configuration_trailer_info::storage_type, cargo_accessory_id) :
                        streq(member, "hook_position") ? offsetof(configuration_trailer_info::storage_type, hook_position) :
                        streq(member, "brand_id") ? offsetof(configuration_trailer_info::storage_type, brand_id) :
                        streq(member, "brand") ? offsetof(configuration_trailer_info::storage_type, brand) :
                        streq(member, "name") ? offsetof(configuration_trailer_info::storage_type, name) :
                        streq(member, "chain_type") ? offsetof(configuration_trailer_info::storage_type, chain_type) :
                        streq(member, "body_type") ? offsetof(configuration_trailer_info::storage_type, body_type) :
                        streq(member, "license_plate") ? offsetof(configuration_trailer_info::storage_type, license_plate) :
                        streq(member, "license_plate_country") ? offsetof(configuration_trailer_info::storage_type, license_plate_country) :
                        streq(member, "license_plate_country_id") ? offsetof(configuration_trailer_info::storage_type, license_plate_country_id) :
                        streq(member, "wheel_count") ? offsetof(configuration_trailer_info::storage_type, wheel_count) :
                        streq(member, "wheel_position") ? offsetof(configuration_trailer_info::storage_type, wheel_position) :
                        streq(member, "wheel_steerable") ? offsetof(configuration_trailer_info::storage_type, wheel_steerable) :
                        streq(member, "wheel_simulated") ? offsetof(configuration_trailer_info::storage_type, wheel_simulated) :
                        streq(member, "wheel_radius") ? offsetof(configuration_trailer_info::storage_type, wheel_radius) :
                        streq(member, "wheel_powered") ? offsetof(configuration_trailer_info::storage_type, wheel_powered) :
                        streq(member, "wheel_liftable") ? offsetof(configuration_trailer_info::storage_type, wheel_liftable) :
                        INVALID_OFFSET;
                case telemetry_id::configuration_job_info:
                    return
                        streq(member, "latest") ? offsetof(configuration_job_info::storage_type, latest) :
                        streq(member, "cargo_id") ? offsetof(configuration_job_info::storage_type, cargo_id) :
                        streq(member, "cargo") ? offsetof(configuration_job_info::storage_type, cargo) :
                        streq(member, "cargo_mass") ? offsetof(configuration_job_info::storage_type, cargo_mass) :
                        streq(member, "destination_city_id") ? offsetof(configuration_job_info::storage_type, destination_city_id) :
                        streq(member, "cargo_unit_mass") ? offsetof(configuration_job_info::storage_type, cargo_unit_mass) :
                        streq(member, "cargo_unit_count") ? offsetof(configuration_job_info::storage_type, cargo_unit_count) :
                        streq(member, "destination_city") ? offsetof(configuration_job_info::storage_type, destination_city) :
                        streq(member, "source_city_id") ? offsetof(configuration_job_info::storage_type, source_city_id) :
                        streq(member, "source_city") ? offsetof(configuration_job_info::storage_type, source_city) :
                        streq(member, "destination_company_id") ? offsetof(configuration_job_info::storage_type, destination_company_id) :
                        streq(member, "destination_company") ? offsetof(configuration_job_info::storage_type, destination_company) :
                        streq(member, "source_company_id") ? offsetof(configuration_job_info::storage_type, source_company_id) :
                        streq(member, "source_company") ? offsetof(configuration_job_info::storage_type, source_company) :
                        streq(member, "income") ? offsetof(configuration_job_info::storage_type, income) :
                        streq(member, "delivery_time") ? offsetof(configuration_job_info::storage_type, delivery_time) :
                        streq(member, "is_cargo_loaded") ? offsetof(configuration_job_info::storage_type, is_cargo_loaded) :
                        streq(member, "job_market") ? offsetof(configuration_job_info::storage_type, job_market) :
                        streq(member, "special_job") ? offsetof(configuration_job_info::storage_type, special_job) :
                        streq(member, "planned_distance_km") ? offsetof(configuration_job_info::storage_type, planned_distance_km) :
                        INVALID_OFFSET;
                case telemetry_id::gameplay_job_cancelled_info:
                    return
                        streq(member, "latest") ? offsetof(gameplay_job_cancelled_info::storage_type, latest) :
                        streq(member, "cancel_penalty") ? offsetof(gameplay_job_cancelled_info::storage_type, cancel_penalty) :
                        INVALID_OFFSET;
                case telemetry_id::gameplay_job_delivered_info:
                    return
                        streq(member, "latest") ? offsetof(gameplay_job_delivered_info::storage_type, latest) :
                        streq(member, "revenue") ? offsetof(gameplay_job_delivered_info::storage_type, revenue) :
                        streq(member, "earned_xp") ? offsetof(gameplay_job_delivered_info::storage_type, earned_xp) :
                        streq(member, "cargo_damage") ? offsetof(gameplay_job_delivered_info::storage_type, cargo_damage) :
                        streq(member, "distance_km") ? offsetof(gameplay_job_delivered_info::storage_type, distance_km) :
                        streq(member, "delivery_time") ? offsetof(gameplay_job_delivered_info::storage_type, delivery_time) :
                        streq(member, "auto_park_used") ? offsetof(gameplay_job_delivered_info::storage_type, auto_park_used) :
                        streq(member, "auto_load_used") ? offsetof(gameplay_job_delivered_info::storage_type, auto_load_used) :
                        INVALID_OFFSET;
                case telemetry_id::gameplay_player_fined_info:
                    return
                        streq(member, "latest") ? offsetof(gameplay_player_fined_info::storage_type, latest) :
                        streq(member, "fine_offence") ? offsetof(gameplay_player_fined_info::storage_type, fine_offence) :
                        streq(member, "fine_amount") ? offsetof(gameplay_player_fined_info::storage_type, fine_amount) :
                        INVALID_OFFSET;
                case telemetry_id::gameplay_player_tollgate_paid_info:
                    return
                        streq(member, "latest") ? offsetof(gameplay_player_tollgate_paid_info::storage_type, latest) :
                        streq(member, "pay_amount") ? offsetof(gameplay_player_tollgate_paid_info::storage_type, pay_amount) :
                        INVALID_OFFSET;
                case telemetry_id::gameplay_player_use_ferry_info:
                    return
                        streq(member, "latest") ? offsetof(gameplay_player_use_ferry_info::storage_type, latest) :
                        streq(member, "pay_amount") ? offsetof(gameplay_player_use_ferry_info::storage_type, pay_amount) :
                        streq(member, "source_name") ? offsetof(gameplay_player_use_ferry_info::storage_type, source_name) :
                        streq(member, "target_name") ? offsetof(gameplay_player_use_ferry_info::storage_type, target_name) :
                        streq(member, "source_id") ? offsetof(gameplay_player_use_ferry_info::storage_type, source_id) :
                        streq(member, "target_id") ? offsetof(gameplay_player_use_ferry_info::storage_type, target_id) :
                        INVALID_OFFSET;
                case telemetry_id::gameplay_player_use_train_info:
                    return
                        streq(member, "latest") ? offsetof(gameplay_player_use_train_info::storage_type, latest) :
                        streq(member, "pay_amount") ? offsetof(gameplay_player_use_train_info::storage_type, pay_amount) :
                        streq(member, "source_name") ? offsetof(gameplay_player_use_train_info::storage_type, source_name) :
                        streq(member, "target_name") ? offsetof(gameplay_player_use_train_info::storage_type, target_name) :
                        streq(member, "source_id") ? offsetof(gameplay_player_use_train_info::storage_type, source_id) :
                        streq(member, "target_id") ? offsetof(gameplay_player_use_train_info::storage_type, target_id) :
                        INVALID_OFFSET;
                default: return INVALID_OFFSET;
            }
        }

        constexpr const scs_value_type_t event_info_member_scs_type_id(const telemetry_id& id, const char* const member) {
            switch (id) {
                case telemetry_id::configuration_substances_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "id") ? SCS_VALUE_TYPE_string :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::configuration_controls_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "shifter_type") ? SCS_VALUE_TYPE_string :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::configuration_hshifter_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "selector_count") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "slot_gear") ? SCS_VALUE_TYPE_s32 :
                        streq(member, "slot_handle_position") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "slot_selectors") ? SCS_VALUE_TYPE_u32 :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::configuration_truck_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "brand_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "brand") ? SCS_VALUE_TYPE_string :
                        streq(member, "id") ? SCS_VALUE_TYPE_string :
                        streq(member, "name") ? SCS_VALUE_TYPE_string :
                        streq(member, "fuel_capacity") ? SCS_VALUE_TYPE_float :
                        streq(member, "fuel_warning_factor") ? SCS_VALUE_TYPE_float :
                        streq(member, "adblue_capacity") ? SCS_VALUE_TYPE_float :
                        streq(member, "adblue_warning_factor") ? SCS_VALUE_TYPE_float :
                        streq(member, "air_pressure_warning") ? SCS_VALUE_TYPE_float :
                        streq(member, "air_pressure_emergency") ? SCS_VALUE_TYPE_float :
                        streq(member, "oil_pressure_warning") ? SCS_VALUE_TYPE_float :
                        streq(member, "water_temperature_warning") ? SCS_VALUE_TYPE_float :
                        streq(member, "battery_voltage_warning") ? SCS_VALUE_TYPE_float :
                        streq(member, "rpm_limit") ? SCS_VALUE_TYPE_float :
                        streq(member, "forward_gear_count") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "reverse_gear_count") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "differential_ratio") ? SCS_VALUE_TYPE_float :
                        streq(member, "retarder_step_count") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "cabin_position") ? SCS_VALUE_TYPE_fvector :
                        streq(member, "forward_ratio") ? SCS_VALUE_TYPE_float :
                        streq(member, "reverse_ratio") ? SCS_VALUE_TYPE_float :
                        streq(member, "head_position") ? SCS_VALUE_TYPE_fvector :
                        streq(member, "hook_position") ? SCS_VALUE_TYPE_fvector :
                        streq(member, "license_plate") ? SCS_VALUE_TYPE_string :
                        streq(member, "license_plate_country") ? SCS_VALUE_TYPE_string :
                        streq(member, "license_plate_country_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "wheel_count") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "wheel_position") ? SCS_VALUE_TYPE_fvector :
                        streq(member, "wheel_steerable") ? SCS_VALUE_TYPE_bool :
                        streq(member, "wheel_simulated") ? SCS_VALUE_TYPE_bool :
                        streq(member, "wheel_radius") ? SCS_VALUE_TYPE_float :
                        streq(member, "wheel_powered") ? SCS_VALUE_TYPE_bool :
                        streq(member, "wheel_liftable") ? SCS_VALUE_TYPE_bool :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::configuration_trailer_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "id") ? SCS_VALUE_TYPE_string :
                        streq(member, "cargo_accessory_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "hook_position") ? SCS_VALUE_TYPE_fvector :
                        streq(member, "brand_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "brand") ? SCS_VALUE_TYPE_string :
                        streq(member, "name") ? SCS_VALUE_TYPE_string :
                        streq(member, "chain_type") ? SCS_VALUE_TYPE_string :
                        streq(member, "body_type") ? SCS_VALUE_TYPE_string :
                        streq(member, "license_plate") ? SCS_VALUE_TYPE_string :
                        streq(member, "license_plate_country") ? SCS_VALUE_TYPE_string :
                        streq(member, "license_plate_country_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "wheel_count") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "wheel_position") ? SCS_VALUE_TYPE_fvector :
                        streq(member, "wheel_steerable") ? SCS_VALUE_TYPE_bool :
                        streq(member, "wheel_simulated") ? SCS_VALUE_TYPE_bool :
                        streq(member, "wheel_radius") ? SCS_VALUE_TYPE_float :
                        streq(member, "wheel_powered") ? SCS_VALUE_TYPE_bool :
                        streq(member, "wheel_liftable") ? SCS_VALUE_TYPE_bool :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::configuration_job_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "cargo_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "cargo") ? SCS_VALUE_TYPE_string :
                        streq(member, "cargo_mass") ? SCS_VALUE_TYPE_float :
                        streq(member, "destination_city_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "cargo_unit_mass") ? SCS_VALUE_TYPE_float :
                        streq(member, "cargo_unit_count") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "destination_city") ? SCS_VALUE_TYPE_string :
                        streq(member, "source_city_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "source_city") ? SCS_VALUE_TYPE_string :
                        streq(member, "destination_company_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "destination_company") ? SCS_VALUE_TYPE_string :
                        streq(member, "source_company_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "source_company") ? SCS_VALUE_TYPE_string :
                        streq(member, "income") ? SCS_VALUE_TYPE_u64 :
                        streq(member, "delivery_time") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "is_cargo_loaded") ? SCS_VALUE_TYPE_bool :
                        streq(member, "job_market") ? SCS_VALUE_TYPE_string :
                        streq(member, "special_job") ? SCS_VALUE_TYPE_bool :
                        streq(member, "planned_distance_km") ? SCS_VALUE_TYPE_u32 :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::gameplay_job_cancelled_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "cancel_penalty") ? SCS_VALUE_TYPE_s64 :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::gameplay_job_delivered_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "revenue") ? SCS_VALUE_TYPE_s64 :
                        streq(member, "earned_xp") ? SCS_VALUE_TYPE_s32 :
                        streq(member, "cargo_damage") ? SCS_VALUE_TYPE_float :
                        streq(member, "distance_km") ? SCS_VALUE_TYPE_float :
                        streq(member, "delivery_time") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "auto_park_used") ? SCS_VALUE_TYPE_bool :
                        streq(member, "auto_load_used") ? SCS_VALUE_TYPE_bool :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::gameplay_player_fined_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "fine_offence") ? SCS_VALUE_TYPE_string :
                        streq(member, "fine_amount") ? SCS_VALUE_TYPE_s64 :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::gameplay_player_tollgate_paid_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "pay_amount") ? SCS_VALUE_TYPE_s64 :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::gameplay_player_use_ferry_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "pay_amount") ? SCS_VALUE_TYPE_s64 :
                        streq(member, "source_name") ? SCS_VALUE_TYPE_string :
                        streq(member, "target_name") ? SCS_VALUE_TYPE_string :
                        streq(member, "source_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "target_id") ? SCS_VALUE_TYPE_string :
                        SCS_VALUE_TYPE_INVALID;
                case telemetry_id::gameplay_player_use_train_info:
                    return
                        streq(member, "latest") ? SCS_VALUE_TYPE_u32 :
                        streq(member, "pay_amount") ? SCS_VALUE_TYPE_s64 :
                        streq(member, "source_name") ? SCS_VALUE_TYPE_string :
                        streq(member, "target_name") ? SCS_VALUE_TYPE_string :
                        streq(member, "source_id") ? SCS_VALUE_TYPE_string :
                        streq(member, "target_id") ? SCS_VALUE_TYPE_string :
                        SCS_VALUE_TYPE_INVALID;
                default: return SCS_VALUE_TYPE_INVALID;
            }
        }

        constexpr const bool is_custom_channel(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::channel_paused: return channel_paused::custom_channel;
                case telemetry_id::channel_local_scale: return channel_local_scale::custom_channel;
                case telemetry_id::channel_game_time: return channel_game_time::custom_channel;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::custom_channel;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::custom_channel;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::custom_channel;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::custom_channel;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::custom_channel;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::custom_channel;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::custom_channel;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::custom_channel;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::custom_channel;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::custom_channel;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::custom_channel;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::custom_channel;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::custom_channel;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::custom_channel;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::custom_channel;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::custom_channel;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::custom_channel;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::custom_channel;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::custom_channel;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::custom_channel;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::custom_channel;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::custom_channel;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::custom_channel;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::custom_channel;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::custom_channel;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::custom_channel;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::custom_channel;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::custom_channel;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::custom_channel;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::custom_channel;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::custom_channel;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::custom_channel;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::custom_channel;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::custom_channel;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::custom_channel;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::custom_channel;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::custom_channel;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::custom_channel;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::custom_channel;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::custom_channel;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::custom_channel;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::custom_channel;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::custom_channel;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::custom_channel;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::custom_channel;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::custom_channel;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::custom_channel;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::custom_channel;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::custom_channel;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::custom_channel;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::custom_channel;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::custom_channel;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::custom_channel;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::custom_channel;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::custom_channel;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::custom_channel;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::custom_channel;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::custom_channel;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::custom_channel;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::custom_channel;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::custom_channel;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::custom_channel;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::custom_channel;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::custom_channel;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::custom_channel;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::custom_channel;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::custom_channel;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::custom_channel;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::custom_channel;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::custom_channel;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::custom_channel;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::custom_channel;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::custom_channel;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::custom_channel;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::custom_channel;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::custom_channel;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::custom_channel;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::custom_channel;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::custom_channel;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::custom_channel;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::custom_channel;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::custom_channel;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::custom_channel;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::custom_channel;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::custom_channel;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::custom_channel;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::custom_channel;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::custom_channel;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::custom_channel;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::custom_channel;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::custom_channel;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::custom_channel;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::custom_channel;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::custom_channel;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::custom_channel;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::custom_channel;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::custom_channel;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::custom_channel;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::custom_channel;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::custom_channel;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::custom_channel;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::custom_channel;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::custom_channel;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::custom_channel;
                default: return false;
            }
        }

        constexpr const metadata_value& metadata_value_of(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::master: return master::metadata_value;
                case telemetry_id::configuration: return configuration::metadata_value;
                case telemetry_id::gameplay: return gameplay::metadata_value;
                case telemetry_id::channels: return channels::metadata_value;
                case telemetry_id::general: return general::metadata_value;
                case telemetry_id::truck: return truck::metadata_value;
                case telemetry_id::trailer: return trailer::metadata_value;
                case telemetry_id::configuration_substances_info: return configuration_substances_info::metadata_value;
                case telemetry_id::configuration_controls_info: return configuration_controls_info::metadata_value;
                case telemetry_id::configuration_hshifter_info: return configuration_hshifter_info::metadata_value;
                case telemetry_id::configuration_truck_info: return configuration_truck_info::metadata_value;
                case telemetry_id::configuration_trailer_info: return configuration_trailer_info::metadata_value;
                case telemetry_id::configuration_job_info: return configuration_job_info::metadata_value;
                case telemetry_id::gameplay_job_cancelled_info: return gameplay_job_cancelled_info::metadata_value;
                case telemetry_id::gameplay_job_delivered_info: return gameplay_job_delivered_info::metadata_value;
                case telemetry_id::gameplay_player_fined_info: return gameplay_player_fined_info::metadata_value;
                case telemetry_id::gameplay_player_tollgate_paid_info: return gameplay_player_tollgate_paid_info::metadata_value;
                case telemetry_id::gameplay_player_use_ferry_info: return gameplay_player_use_ferry_info::metadata_value;
                case telemetry_id::gameplay_player_use_train_info: return gameplay_player_use_train_info::metadata_value;
                case telemetry_id::channel_paused: return channel_paused::metadata_value;
                case telemetry_id::channel_local_scale: return channel_local_scale::metadata_value;
                case telemetry_id::channel_game_time: return channel_game_time::metadata_value;
                case telemetry_id::channel_multiplayer_time_offset: return channel_multiplayer_time_offset::metadata_value;
                case telemetry_id::channel_next_rest_stop: return channel_next_rest_stop::metadata_value;
                case telemetry_id::job_channel_cargo_damage: return job_channel_cargo_damage::metadata_value;
                case telemetry_id::trailer_channel_connected: return trailer_channel_connected::metadata_value;
                case telemetry_id::trailer_channel_cargo_damage: return trailer_channel_cargo_damage::metadata_value;
                case telemetry_id::trailer_channel_world_placement: return trailer_channel_world_placement::metadata_value;
                case telemetry_id::trailer_channel_local_linear_velocity: return trailer_channel_local_linear_velocity::metadata_value;
                case telemetry_id::trailer_channel_local_angular_velocity: return trailer_channel_local_angular_velocity::metadata_value;
                case telemetry_id::trailer_channel_local_linear_acceleration: return trailer_channel_local_linear_acceleration::metadata_value;
                case telemetry_id::trailer_channel_local_angular_acceleration: return trailer_channel_local_angular_acceleration::metadata_value;
                case telemetry_id::trailer_channel_wear_body: return trailer_channel_wear_body::metadata_value;
                case telemetry_id::trailer_channel_wear_chassis: return trailer_channel_wear_chassis::metadata_value;
                case telemetry_id::trailer_channel_wear_wheels: return trailer_channel_wear_wheels::metadata_value;
                case telemetry_id::trailer_channel_wheel_susp_deflection: return trailer_channel_wheel_susp_deflection::metadata_value;
                case telemetry_id::trailer_channel_wheel_on_ground: return trailer_channel_wheel_on_ground::metadata_value;
                case telemetry_id::trailer_channel_wheel_substance: return trailer_channel_wheel_substance::metadata_value;
                case telemetry_id::trailer_channel_wheel_velocity: return trailer_channel_wheel_velocity::metadata_value;
                case telemetry_id::trailer_channel_wheel_steering: return trailer_channel_wheel_steering::metadata_value;
                case telemetry_id::trailer_channel_wheel_rotation: return trailer_channel_wheel_rotation::metadata_value;
                case telemetry_id::trailer_channel_wheel_lift: return trailer_channel_wheel_lift::metadata_value;
                case telemetry_id::trailer_channel_wheel_lift_offset: return trailer_channel_wheel_lift_offset::metadata_value;
                case telemetry_id::truck_channel_world_placement: return truck_channel_world_placement::metadata_value;
                case telemetry_id::truck_channel_local_linear_velocity: return truck_channel_local_linear_velocity::metadata_value;
                case telemetry_id::truck_channel_local_angular_velocity: return truck_channel_local_angular_velocity::metadata_value;
                case telemetry_id::truck_channel_local_linear_acceleration: return truck_channel_local_linear_acceleration::metadata_value;
                case telemetry_id::truck_channel_local_angular_acceleration: return truck_channel_local_angular_acceleration::metadata_value;
                case telemetry_id::truck_channel_cabin_offset: return truck_channel_cabin_offset::metadata_value;
                case telemetry_id::truck_channel_cabin_angular_velocity: return truck_channel_cabin_angular_velocity::metadata_value;
                case telemetry_id::truck_channel_cabin_angular_acceleration: return truck_channel_cabin_angular_acceleration::metadata_value;
                case telemetry_id::truck_channel_head_offset: return truck_channel_head_offset::metadata_value;
                case telemetry_id::truck_channel_speed: return truck_channel_speed::metadata_value;
                case telemetry_id::truck_channel_engine_rpm: return truck_channel_engine_rpm::metadata_value;
                case telemetry_id::truck_channel_engine_gear: return truck_channel_engine_gear::metadata_value;
                case telemetry_id::truck_channel_displayed_gear: return truck_channel_displayed_gear::metadata_value;
                case telemetry_id::truck_channel_input_steering: return truck_channel_input_steering::metadata_value;
                case telemetry_id::truck_channel_input_throttle: return truck_channel_input_throttle::metadata_value;
                case telemetry_id::truck_channel_input_brake: return truck_channel_input_brake::metadata_value;
                case telemetry_id::truck_channel_input_clutch: return truck_channel_input_clutch::metadata_value;
                case telemetry_id::truck_channel_effective_steering: return truck_channel_effective_steering::metadata_value;
                case telemetry_id::truck_channel_effective_throttle: return truck_channel_effective_throttle::metadata_value;
                case telemetry_id::truck_channel_effective_brake: return truck_channel_effective_brake::metadata_value;
                case telemetry_id::truck_channel_effective_clutch: return truck_channel_effective_clutch::metadata_value;
                case telemetry_id::truck_channel_cruise_control: return truck_channel_cruise_control::metadata_value;
                case telemetry_id::truck_channel_hshifter_slot: return truck_channel_hshifter_slot::metadata_value;
                case telemetry_id::truck_channel_hshifter_selector: return truck_channel_hshifter_selector::metadata_value;
                case telemetry_id::truck_channel_parking_brake: return truck_channel_parking_brake::metadata_value;
                case telemetry_id::truck_channel_motor_brake: return truck_channel_motor_brake::metadata_value;
                case telemetry_id::truck_channel_retarder_level: return truck_channel_retarder_level::metadata_value;
                case telemetry_id::truck_channel_brake_air_pressure: return truck_channel_brake_air_pressure::metadata_value;
                case telemetry_id::truck_channel_brake_air_pressure_warning: return truck_channel_brake_air_pressure_warning::metadata_value;
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return truck_channel_brake_air_pressure_emergency::metadata_value;
                case telemetry_id::truck_channel_brake_temperature: return truck_channel_brake_temperature::metadata_value;
                case telemetry_id::truck_channel_fuel: return truck_channel_fuel::metadata_value;
                case telemetry_id::truck_channel_fuel_warning: return truck_channel_fuel_warning::metadata_value;
                case telemetry_id::truck_channel_fuel_average_consumption: return truck_channel_fuel_average_consumption::metadata_value;
                case telemetry_id::truck_channel_fuel_range: return truck_channel_fuel_range::metadata_value;
                case telemetry_id::truck_channel_adblue: return truck_channel_adblue::metadata_value;
                case telemetry_id::truck_channel_adblue_warning: return truck_channel_adblue_warning::metadata_value;
                case telemetry_id::truck_channel_oil_pressure: return truck_channel_oil_pressure::metadata_value;
                case telemetry_id::truck_channel_oil_pressure_warning: return truck_channel_oil_pressure_warning::metadata_value;
                case telemetry_id::truck_channel_oil_temperature: return truck_channel_oil_temperature::metadata_value;
                case telemetry_id::truck_channel_water_temperature: return truck_channel_water_temperature::metadata_value;
                case telemetry_id::truck_channel_water_temperature_warning: return truck_channel_water_temperature_warning::metadata_value;
                case telemetry_id::truck_channel_battery_voltage: return truck_channel_battery_voltage::metadata_value;
                case telemetry_id::truck_channel_battery_voltage_warning: return truck_channel_battery_voltage_warning::metadata_value;
                case telemetry_id::truck_channel_electric_enabled: return truck_channel_electric_enabled::metadata_value;
                case telemetry_id::truck_channel_engine_enabled: return truck_channel_engine_enabled::metadata_value;
                case telemetry_id::truck_channel_lblinker: return truck_channel_lblinker::metadata_value;
                case telemetry_id::truck_channel_rblinker: return truck_channel_rblinker::metadata_value;
                case telemetry_id::truck_channel_hazard_warning: return truck_channel_hazard_warning::metadata_value;
                case telemetry_id::truck_channel_light_lblinker: return truck_channel_light_lblinker::metadata_value;
                case telemetry_id::truck_channel_light_rblinker: return truck_channel_light_rblinker::metadata_value;
                case telemetry_id::truck_channel_light_parking: return truck_channel_light_parking::metadata_value;
                case telemetry_id::truck_channel_light_low_beam: return truck_channel_light_low_beam::metadata_value;
                case telemetry_id::truck_channel_light_high_beam: return truck_channel_light_high_beam::metadata_value;
                case telemetry_id::truck_channel_light_aux_front: return truck_channel_light_aux_front::metadata_value;
                case telemetry_id::truck_channel_light_aux_roof: return truck_channel_light_aux_roof::metadata_value;
                case telemetry_id::truck_channel_light_beacon: return truck_channel_light_beacon::metadata_value;
                case telemetry_id::truck_channel_light_brake: return truck_channel_light_brake::metadata_value;
                case telemetry_id::truck_channel_light_reverse: return truck_channel_light_reverse::metadata_value;
                case telemetry_id::truck_channel_wipers: return truck_channel_wipers::metadata_value;
                case telemetry_id::truck_channel_dashboard_backlight: return truck_channel_dashboard_backlight::metadata_value;
                case telemetry_id::truck_channel_differential_lock: return truck_channel_differential_lock::metadata_value;
                case telemetry_id::truck_channel_lift_axle: return truck_channel_lift_axle::metadata_value;
                case telemetry_id::truck_channel_lift_axle_indicator: return truck_channel_lift_axle_indicator::metadata_value;
                case telemetry_id::truck_channel_trailer_lift_axle: return truck_channel_trailer_lift_axle::metadata_value;
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return truck_channel_trailer_lift_axle_indicator::metadata_value;
                case telemetry_id::truck_channel_wear_engine: return truck_channel_wear_engine::metadata_value;
                case telemetry_id::truck_channel_wear_transmission: return truck_channel_wear_transmission::metadata_value;
                case telemetry_id::truck_channel_wear_cabin: return truck_channel_wear_cabin::metadata_value;
                case telemetry_id::truck_channel_wear_chassis: return truck_channel_wear_chassis::metadata_value;
                case telemetry_id::truck_channel_wear_wheels: return truck_channel_wear_wheels::metadata_value;
                case telemetry_id::truck_channel_odometer: return truck_channel_odometer::metadata_value;
                case telemetry_id::truck_channel_navigation_distance: return truck_channel_navigation_distance::metadata_value;
                case telemetry_id::truck_channel_navigation_time: return truck_channel_navigation_time::metadata_value;
                case telemetry_id::truck_channel_navigation_speed_limit: return truck_channel_navigation_speed_limit::metadata_value;
                case telemetry_id::truck_channel_wheel_susp_deflection: return truck_channel_wheel_susp_deflection::metadata_value;
                case telemetry_id::truck_channel_wheel_on_ground: return truck_channel_wheel_on_ground::metadata_value;
                case telemetry_id::truck_channel_wheel_substance: return truck_channel_wheel_substance::metadata_value;
                case telemetry_id::truck_channel_wheel_velocity: return truck_channel_wheel_velocity::metadata_value;
                case telemetry_id::truck_channel_wheel_steering: return truck_channel_wheel_steering::metadata_value;
                case telemetry_id::truck_channel_wheel_rotation: return truck_channel_wheel_rotation::metadata_value;
                case telemetry_id::truck_channel_wheel_lift: return truck_channel_wheel_lift::metadata_value;
                case telemetry_id::truck_channel_wheel_lift_offset: return truck_channel_wheel_lift_offset::metadata_value;
                default: return INVALID_METADATA;
            }
        }

        constexpr const char* const id_name(const telemetry_id& id) {
            switch (id) {
                case telemetry_id::master: return "master";
                case telemetry_id::configuration: return "configuration";
                case telemetry_id::gameplay: return "gameplay";
                case telemetry_id::channels: return "channels";
                case telemetry_id::general: return "general";
                case telemetry_id::truck: return "truck";
                case telemetry_id::trailer: return "trailer";
                case telemetry_id::configuration_substances_info: return "configuration_substances_info";
                case telemetry_id::configuration_controls_info: return "configuration_controls_info";
                case telemetry_id::configuration_hshifter_info: return "configuration_hshifter_info";
                case telemetry_id::configuration_truck_info: return "configuration_truck_info";
                case telemetry_id::configuration_trailer_info: return "configuration_trailer_info";
                case telemetry_id::configuration_job_info: return "configuration_job_info";
                case telemetry_id::gameplay_job_cancelled_info: return "gameplay_job_cancelled_info";
                case telemetry_id::gameplay_job_delivered_info: return "gameplay_job_delivered_info";
                case telemetry_id::gameplay_player_fined_info: return "gameplay_player_fined_info";
                case telemetry_id::gameplay_player_tollgate_paid_info: return "gameplay_player_tollgate_paid_info";
                case telemetry_id::gameplay_player_use_ferry_info: return "gameplay_player_use_ferry_info";
                case telemetry_id::gameplay_player_use_train_info: return "gameplay_player_use_train_info";
                case telemetry_id::channel_paused: return "channel_paused";
                case telemetry_id::channel_local_scale: return "channel_local_scale";
                case telemetry_id::channel_game_time: return "channel_game_time";
                case telemetry_id::channel_multiplayer_time_offset: return "channel_multiplayer_time_offset";
                case telemetry_id::channel_next_rest_stop: return "channel_next_rest_stop";
                case telemetry_id::job_channel_cargo_damage: return "job_channel_cargo_damage";
                case telemetry_id::trailer_channel_connected: return "trailer_channel_connected";
                case telemetry_id::trailer_channel_cargo_damage: return "trailer_channel_cargo_damage";
                case telemetry_id::trailer_channel_world_placement: return "trailer_channel_world_placement";
                case telemetry_id::trailer_channel_local_linear_velocity: return "trailer_channel_local_linear_velocity";
                case telemetry_id::trailer_channel_local_angular_velocity: return "trailer_channel_local_angular_velocity";
                case telemetry_id::trailer_channel_local_linear_acceleration: return "trailer_channel_local_linear_acceleration";
                case telemetry_id::trailer_channel_local_angular_acceleration: return "trailer_channel_local_angular_acceleration";
                case telemetry_id::trailer_channel_wear_body: return "trailer_channel_wear_body";
                case telemetry_id::trailer_channel_wear_chassis: return "trailer_channel_wear_chassis";
                case telemetry_id::trailer_channel_wear_wheels: return "trailer_channel_wear_wheels";
                case telemetry_id::trailer_channel_wheel_susp_deflection: return "trailer_channel_wheel_susp_deflection";
                case telemetry_id::trailer_channel_wheel_on_ground: return "trailer_channel_wheel_on_ground";
                case telemetry_id::trailer_channel_wheel_substance: return "trailer_channel_wheel_substance";
                case telemetry_id::trailer_channel_wheel_velocity: return "trailer_channel_wheel_velocity";
                case telemetry_id::trailer_channel_wheel_steering: return "trailer_channel_wheel_steering";
                case telemetry_id::trailer_channel_wheel_rotation: return "trailer_channel_wheel_rotation";
                case telemetry_id::trailer_channel_wheel_lift: return "trailer_channel_wheel_lift";
                case telemetry_id::trailer_channel_wheel_lift_offset: return "trailer_channel_wheel_lift_offset";
                case telemetry_id::truck_channel_world_placement: return "truck_channel_world_placement";
                case telemetry_id::truck_channel_local_linear_velocity: return "truck_channel_local_linear_velocity";
                case telemetry_id::truck_channel_local_angular_velocity: return "truck_channel_local_angular_velocity";
                case telemetry_id::truck_channel_local_linear_acceleration: return "truck_channel_local_linear_acceleration";
                case telemetry_id::truck_channel_local_angular_acceleration: return "truck_channel_local_angular_acceleration";
                case telemetry_id::truck_channel_cabin_offset: return "truck_channel_cabin_offset";
                case telemetry_id::truck_channel_cabin_angular_velocity: return "truck_channel_cabin_angular_velocity";
                case telemetry_id::truck_channel_cabin_angular_acceleration: return "truck_channel_cabin_angular_acceleration";
                case telemetry_id::truck_channel_head_offset: return "truck_channel_head_offset";
                case telemetry_id::truck_channel_speed: return "truck_channel_speed";
                case telemetry_id::truck_channel_engine_rpm: return "truck_channel_engine_rpm";
                case telemetry_id::truck_channel_engine_gear: return "truck_channel_engine_gear";
                case telemetry_id::truck_channel_displayed_gear: return "truck_channel_displayed_gear";
                case telemetry_id::truck_channel_input_steering: return "truck_channel_input_steering";
                case telemetry_id::truck_channel_input_throttle: return "truck_channel_input_throttle";
                case telemetry_id::truck_channel_input_brake: return "truck_channel_input_brake";
                case telemetry_id::truck_channel_input_clutch: return "truck_channel_input_clutch";
                case telemetry_id::truck_channel_effective_steering: return "truck_channel_effective_steering";
                case telemetry_id::truck_channel_effective_throttle: return "truck_channel_effective_throttle";
                case telemetry_id::truck_channel_effective_brake: return "truck_channel_effective_brake";
                case telemetry_id::truck_channel_effective_clutch: return "truck_channel_effective_clutch";
                case telemetry_id::truck_channel_cruise_control: return "truck_channel_cruise_control";
                case telemetry_id::truck_channel_hshifter_slot: return "truck_channel_hshifter_slot";
                case telemetry_id::truck_channel_hshifter_selector: return "truck_channel_hshifter_selector";
                case telemetry_id::truck_channel_parking_brake: return "truck_channel_parking_brake";
                case telemetry_id::truck_channel_motor_brake: return "truck_channel_motor_brake";
                case telemetry_id::truck_channel_retarder_level: return "truck_channel_retarder_level";
                case telemetry_id::truck_channel_brake_air_pressure: return "truck_channel_brake_air_pressure";
                case telemetry_id::truck_channel_brake_air_pressure_warning: return "truck_channel_brake_air_pressure_warning";
                case telemetry_id::truck_channel_brake_air_pressure_emergency: return "truck_channel_brake_air_pressure_emergency";
                case telemetry_id::truck_channel_brake_temperature: return "truck_channel_brake_temperature";
                case telemetry_id::truck_channel_fuel: return "truck_channel_fuel";
                case telemetry_id::truck_channel_fuel_warning: return "truck_channel_fuel_warning";
                case telemetry_id::truck_channel_fuel_average_consumption: return "truck_channel_fuel_average_consumption";
                case telemetry_id::truck_channel_fuel_range: return "truck_channel_fuel_range";
                case telemetry_id::truck_channel_adblue: return "truck_channel_adblue";
                case telemetry_id::truck_channel_adblue_warning: return "truck_channel_adblue_warning";
                case telemetry_id::truck_channel_oil_pressure: return "truck_channel_oil_pressure";
                case telemetry_id::truck_channel_oil_pressure_warning: return "truck_channel_oil_pressure_warning";
                case telemetry_id::truck_channel_oil_temperature: return "truck_channel_oil_temperature";
                case telemetry_id::truck_channel_water_temperature: return "truck_channel_water_temperature";
                case telemetry_id::truck_channel_water_temperature_warning: return "truck_channel_water_temperature_warning";
                case telemetry_id::truck_channel_battery_voltage: return "truck_channel_battery_voltage";
                case telemetry_id::truck_channel_battery_voltage_warning: return "truck_channel_battery_voltage_warning";
                case telemetry_id::truck_channel_electric_enabled: return "truck_channel_electric_enabled";
                case telemetry_id::truck_channel_engine_enabled: return "truck_channel_engine_enabled";
                case telemetry_id::truck_channel_lblinker: return "truck_channel_lblinker";
                case telemetry_id::truck_channel_rblinker: return "truck_channel_rblinker";
                case telemetry_id::truck_channel_hazard_warning: return "truck_channel_hazard_warning";
                case telemetry_id::truck_channel_light_lblinker: return "truck_channel_light_lblinker";
                case telemetry_id::truck_channel_light_rblinker: return "truck_channel_light_rblinker";
                case telemetry_id::truck_channel_light_parking: return "truck_channel_light_parking";
                case telemetry_id::truck_channel_light_low_beam: return "truck_channel_light_low_beam";
                case telemetry_id::truck_channel_light_high_beam: return "truck_channel_light_high_beam";
                case telemetry_id::truck_channel_light_aux_front: return "truck_channel_light_aux_front";
                case telemetry_id::truck_channel_light_aux_roof: return "truck_channel_light_aux_roof";
                case telemetry_id::truck_channel_light_beacon: return "truck_channel_light_beacon";
                case telemetry_id::truck_channel_light_brake: return "truck_channel_light_brake";
                case telemetry_id::truck_channel_light_reverse: return "truck_channel_light_reverse";
                case telemetry_id::truck_channel_wipers: return "truck_channel_wipers";
                case telemetry_id::truck_channel_dashboard_backlight: return "truck_channel_dashboard_backlight";
                case telemetry_id::truck_channel_differential_lock: return "truck_channel_differential_lock";
                case telemetry_id::truck_channel_lift_axle: return "truck_channel_lift_axle";
                case telemetry_id::truck_channel_lift_axle_indicator: return "truck_channel_lift_axle_indicator";
                case telemetry_id::truck_channel_trailer_lift_axle: return "truck_channel_trailer_lift_axle";
                case telemetry_id::truck_channel_trailer_lift_axle_indicator: return "truck_channel_trailer_lift_axle_indicator";
                case telemetry_id::truck_channel_wear_engine: return "truck_channel_wear_engine";
                case telemetry_id::truck_channel_wear_transmission: return "truck_channel_wear_transmission";
                case telemetry_id::truck_channel_wear_cabin: return "truck_channel_wear_cabin";
                case telemetry_id::truck_channel_wear_chassis: return "truck_channel_wear_chassis";
                case telemetry_id::truck_channel_wear_wheels: return "truck_channel_wear_wheels";
                case telemetry_id::truck_channel_odometer: return "truck_channel_odometer";
                case telemetry_id::truck_channel_navigation_distance: return "truck_channel_navigation_distance";
                case telemetry_id::truck_channel_navigation_time: return "truck_channel_navigation_time";
                case telemetry_id::truck_channel_navigation_speed_limit: return "truck_channel_navigation_speed_limit";
                case telemetry_id::truck_channel_wheel_susp_deflection: return "truck_channel_wheel_susp_deflection";
                case telemetry_id::truck_channel_wheel_on_ground: return "truck_channel_wheel_on_ground";
                case telemetry_id::truck_channel_wheel_substance: return "truck_channel_wheel_substance";
                case telemetry_id::truck_channel_wheel_velocity: return "truck_channel_wheel_velocity";
                case telemetry_id::truck_channel_wheel_steering: return "truck_channel_wheel_steering";
                case telemetry_id::truck_channel_wheel_rotation: return "truck_channel_wheel_rotation";
                case telemetry_id::truck_channel_wheel_lift: return "truck_channel_wheel_lift";
                case telemetry_id::truck_channel_wheel_lift_offset: return "truck_channel_wheel_lift_offset";
                default: return "invalid";
            }
        }
    }
}