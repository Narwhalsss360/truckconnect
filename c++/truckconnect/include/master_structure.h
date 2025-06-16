#pragma once
#include "value_storage.h"
#include "scssdk/scssdk_value.h"

namespace truckconnect {
    struct master_storage {
        struct configuration_storage {
            struct configuration_substances_storage {
                value_storage<uint32_t> latest {};
                value_vector_storage<std::string> id {};
            } configuration_substances_info;

            struct configuration_controls_storage {
                value_storage<uint32_t> latest {};
                value_storage<std::string> shifter_type {};
            } configuration_controls_info;

            struct configuration_hshifter_storage {
                value_storage<uint32_t> latest {};
                value_storage<uint32_t> selector_count {};
                value_vector_storage<int32_t> slot_gear {};
                value_vector_storage<uint32_t> slot_handle_position {};
                value_vector_storage<uint32_t> slot_selectors {};
            } configuration_hshifter_info;

            struct configuration_truck_storage {
                value_storage<uint32_t> latest {};
                value_storage<std::string> brand_id {};
                value_storage<std::string> brand {};
                value_storage<std::string> id {};
                value_storage<std::string> name {};
                value_storage<float> fuel_capacity {};
                value_storage<float> fuel_warning_factor {};
                value_storage<float> adblue_capacity {};
                value_storage<float> adblue_warning_factor {};
                value_storage<float> air_pressure_warning {};
                value_storage<float> air_pressure_emergency {};
                value_storage<float> oil_pressure_warning {};
                value_storage<float> water_temperature_warning {};
                value_storage<float> battery_voltage_warning {};
                value_storage<float> rpm_limit {};
                value_storage<uint32_t> forward_gear_count {};
                value_storage<uint32_t> reverse_gear_count {};
                value_storage<float> differential_ratio {};
                value_storage<uint32_t> retarder_step_count {};
                value_storage<scs_value_fvector_t> cabin_position {};
                value_vector_storage<float> forward_ratio {};
                value_vector_storage<float> reverse_ratio {};
                value_storage<scs_value_fvector_t> head_position {};
                value_storage<scs_value_fvector_t> hook_position {};
                value_storage<std::string> license_plate {};
                value_storage<std::string> license_plate_country {};
                value_storage<std::string> license_plate_country_id {};
                value_storage<uint32_t> wheel_count {};
                value_vector_storage<scs_value_fvector_t> wheel_position {};
                value_vector_storage<bool> wheel_steerable {};
                value_vector_storage<bool> wheel_simulated {};
                value_vector_storage<float> wheel_radius {};
                value_vector_storage<bool> wheel_powered {};
                value_vector_storage<bool> wheel_liftable {};
            } configuration_truck_info;

            struct configuration_trailer_storage {
                value_storage<uint32_t> latest {};
                value_storage<std::string> id {};
                value_storage<std::string> cargo_accessory_id {};
                value_storage<scs_value_fvector_t> hook_position {};
                value_storage<std::string> brand_id {};
                value_storage<std::string> brand {};
                value_storage<std::string> name {};
                value_storage<std::string> chain_type {};
                value_storage<std::string> body_type {};
                value_storage<std::string> license_plate {};
                value_storage<std::string> license_plate_country {};
                value_storage<std::string> license_plate_country_id {};
                value_storage<uint32_t> wheel_count {};
                value_vector_storage<scs_value_fvector_t> wheel_position {};
                value_vector_storage<bool> wheel_steerable {};
                value_vector_storage<bool> wheel_simulated {};
                value_vector_storage<float> wheel_radius {};
                value_vector_storage<bool> wheel_powered {};
                value_vector_storage<bool> wheel_liftable {};
            }; std::array<configuration_trailer_storage, 10> configuration_trailer_info;

            struct configuration_job_storage {
                value_storage<uint32_t> latest {};
                value_storage<std::string> cargo_id {};
                value_storage<std::string> cargo {};
                value_storage<float> cargo_mass {};
                value_storage<std::string> destination_city_id {};
                value_storage<float> cargo_unit_mass {};
                value_storage<uint32_t> cargo_unit_count {};
                value_storage<std::string> destination_city {};
                value_storage<std::string> source_city_id {};
                value_storage<std::string> source_city {};
                value_storage<std::string> destination_company_id {};
                value_storage<std::string> destination_company {};
                value_storage<std::string> source_company_id {};
                value_storage<std::string> source_company {};
                value_storage<uint64_t> income {};
                value_storage<uint32_t> delivery_time {};
                value_storage<bool> is_cargo_loaded {};
                value_storage<std::string> job_market {};
                value_storage<bool> special_job {};
                value_storage<uint32_t> planned_distance_km {};
            } configuration_job_info;
        } configuration;

        struct gameplay_storage {
            struct gameplay_job_cancelled_storage {
                value_storage<uint32_t> latest {};
                value_storage<int64_t> cancel_penalty {};
            } gameplay_job_cancelled_info;

            struct gameplay_job_delivered_storage {
                value_storage<uint32_t> latest {};
                value_storage<int64_t> revenue {};
                value_storage<int32_t> earned_xp {};
                value_storage<float> cargo_damage {};
                value_storage<float> distance_km {};
                value_storage<uint32_t> delivery_time {};
                value_storage<bool> auto_park_used {};
                value_storage<bool> auto_load_used {};
            } gameplay_job_delivered_info;

            struct gameplay_player_fined_storage {
                value_storage<uint32_t> latest {};
                value_storage<std::string> fine_offence {};
                value_storage<int64_t> fine_amount {};
            } gameplay_player_fined_info;

            struct gameplay_player_tollgate_paid_storage {
                value_storage<uint32_t> latest {};
                value_storage<int64_t> pay_amount {};
            } gameplay_player_tollgate_paid_info;

            struct gameplay_player_use_ferry_storage {
                value_storage<uint32_t> latest {};
                value_storage<int64_t> pay_amount {};
                value_storage<std::string> source_name {};
                value_storage<std::string> target_name {};
                value_storage<std::string> source_id {};
                value_storage<std::string> target_id {};
            } gameplay_player_use_ferry_info;

            struct gameplay_player_use_train_storage {
                value_storage<uint32_t> latest {};
                value_storage<int64_t> pay_amount {};
                value_storage<std::string> source_name {};
                value_storage<std::string> target_name {};
                value_storage<std::string> source_id {};
                value_storage<std::string> target_id {};
            } gameplay_player_use_train_info;
        } gameplay;

        struct channels_storage {
            struct general_storage {
                value_storage<bool> channel_paused {};
                value_storage<float> channel_local_scale {};
                value_storage<uint32_t> channel_game_time {};
                value_storage<int32_t> channel_multiplayer_time_offset {};
                value_storage<int32_t> channel_next_rest_stop {};
                value_storage<float> job_channel_cargo_damage {};
            } general;

            struct truck_storage {
                value_storage<scs_value_dplacement_t> truck_channel_world_placement {};
                value_storage<scs_value_fvector_t> truck_channel_local_linear_velocity {};
                value_storage<scs_value_fvector_t> truck_channel_local_angular_velocity {};
                value_storage<scs_value_fvector_t> truck_channel_local_linear_acceleration {};
                value_storage<scs_value_fvector_t> truck_channel_local_angular_acceleration {};
                value_storage<scs_value_fplacement_t> truck_channel_cabin_offset {};
                value_storage<scs_value_fvector_t> truck_channel_cabin_angular_velocity {};
                value_storage<scs_value_fvector_t> truck_channel_cabin_angular_acceleration {};
                value_storage<scs_value_fplacement_t> truck_channel_head_offset {};
                value_storage<float> truck_channel_speed {};
                value_storage<float> truck_channel_engine_rpm {};
                value_storage<int32_t> truck_channel_engine_gear {};
                value_storage<int32_t> truck_channel_displayed_gear {};
                value_storage<float> truck_channel_input_steering {};
                value_storage<float> truck_channel_input_throttle {};
                value_storage<float> truck_channel_input_brake {};
                value_storage<float> truck_channel_input_clutch {};
                value_storage<float> truck_channel_effective_steering {};
                value_storage<float> truck_channel_effective_throttle {};
                value_storage<float> truck_channel_effective_brake {};
                value_storage<float> truck_channel_effective_clutch {};
                value_storage<float> truck_channel_cruise_control {};
                value_storage<uint32_t> truck_channel_hshifter_slot {};
                value_array_storage<bool, 2> truck_channel_hshifter_selector {};
                value_storage<bool> truck_channel_parking_brake {};
                value_storage<bool> truck_channel_motor_brake {};
                value_storage<uint32_t> truck_channel_retarder_level {};
                value_storage<float> truck_channel_brake_air_pressure {};
                value_storage<bool> truck_channel_brake_air_pressure_warning {};
                value_storage<bool> truck_channel_brake_air_pressure_emergency {};
                value_storage<float> truck_channel_brake_temperature {};
                value_storage<float> truck_channel_fuel {};
                value_storage<bool> truck_channel_fuel_warning {};
                value_storage<float> truck_channel_fuel_average_consumption {};
                value_storage<float> truck_channel_fuel_range {};
                value_storage<float> truck_channel_adblue {};
                value_storage<bool> truck_channel_adblue_warning {};
                value_storage<float> truck_channel_oil_pressure {};
                value_storage<bool> truck_channel_oil_pressure_warning {};
                value_storage<float> truck_channel_oil_temperature {};
                value_storage<float> truck_channel_water_temperature {};
                value_storage<bool> truck_channel_water_temperature_warning {};
                value_storage<float> truck_channel_battery_voltage {};
                value_storage<bool> truck_channel_battery_voltage_warning {};
                value_storage<bool> truck_channel_electric_enabled {};
                value_storage<bool> truck_channel_engine_enabled {};
                value_storage<bool> truck_channel_lblinker {};
                value_storage<bool> truck_channel_rblinker {};
                value_storage<bool> truck_channel_hazard_warning {};
                value_storage<bool> truck_channel_light_lblinker {};
                value_storage<bool> truck_channel_light_rblinker {};
                value_storage<bool> truck_channel_light_parking {};
                value_storage<bool> truck_channel_light_low_beam {};
                value_storage<bool> truck_channel_light_high_beam {};
                value_storage<uint32_t> truck_channel_light_aux_front {};
                value_storage<uint32_t> truck_channel_light_aux_roof {};
                value_storage<bool> truck_channel_light_beacon {};
                value_storage<bool> truck_channel_light_brake {};
                value_storage<bool> truck_channel_light_reverse {};
                value_storage<bool> truck_channel_wipers {};
                value_storage<float> truck_channel_dashboard_backlight {};
                value_storage<bool> truck_channel_differential_lock {};
                value_storage<bool> truck_channel_lift_axle {};
                value_storage<bool> truck_channel_lift_axle_indicator {};
                value_storage<bool> truck_channel_trailer_lift_axle {};
                value_storage<bool> truck_channel_trailer_lift_axle_indicator {};
                value_storage<float> truck_channel_wear_engine {};
                value_storage<float> truck_channel_wear_transmission {};
                value_storage<float> truck_channel_wear_cabin {};
                value_storage<float> truck_channel_wear_chassis {};
                value_storage<float> truck_channel_wear_wheels {};
                value_storage<float> truck_channel_odometer {};
                value_storage<float> truck_channel_navigation_distance {};
                value_storage<float> truck_channel_navigation_time {};
                value_storage<float> truck_channel_navigation_speed_limit {};
                value_array_storage<float, 14> truck_channel_wheel_susp_deflection {};
                value_array_storage<bool, 14> truck_channel_wheel_on_ground {};
                value_array_storage<uint32_t, 14> truck_channel_wheel_substance {};
                value_array_storage<float, 14> truck_channel_wheel_velocity {};
                value_array_storage<float, 14> truck_channel_wheel_steering {};
                value_array_storage<float, 14> truck_channel_wheel_rotation {};
                value_array_storage<float, 14> truck_channel_wheel_lift {};
                value_array_storage<float, 14> truck_channel_wheel_lift_offset {};
            } truck;

            struct trailer_storage {
                value_storage<bool> trailer_channel_connected {};
                value_storage<float> trailer_channel_cargo_damage {};
                value_storage<scs_value_dplacement_t> trailer_channel_world_placement {};
                value_storage<scs_value_fvector_t> trailer_channel_local_linear_velocity {};
                value_storage<scs_value_fvector_t> trailer_channel_local_angular_velocity {};
                value_storage<scs_value_fvector_t> trailer_channel_local_linear_acceleration {};
                value_storage<scs_value_fvector_t> trailer_channel_local_angular_acceleration {};
                value_storage<float> trailer_channel_wear_body {};
                value_storage<float> trailer_channel_wear_chassis {};
                value_storage<float> trailer_channel_wear_wheels {};
                value_array_storage<float, 19> trailer_channel_wheel_susp_deflection {};
                value_array_storage<bool, 19> trailer_channel_wheel_on_ground {};
                value_array_storage<uint32_t, 19> trailer_channel_wheel_substance {};
                value_array_storage<float, 19> trailer_channel_wheel_velocity {};
                value_array_storage<float, 19> trailer_channel_wheel_steering {};
                value_array_storage<float, 19> trailer_channel_wheel_rotation {};
                value_array_storage<float, 19> trailer_channel_wheel_lift {};
                value_array_storage<float, 19> trailer_channel_wheel_lift_offset {};
            }; std::array<trailer_storage, 10> trailer;
        } channels;
    };

    const uint32_t memory_usage(const master_storage& master);
}
