#pragma once
#include "master_structure.h"
#include "scssdk/common/scssdk_telemetry_common_configs.h"

namespace truckconnect {
    namespace telemetry_ids {
        enum telemetry_id : uint8_t {
            master = 0,
            configuration = 1,
            gameplay = 2,
            channels = 3,
            general = 4,
            truck = 5,
            trailer = 6,
            configuration_substances_info = 7,
            configuration_controls_info = 8,
            configuration_hshifter_info = 9,
            configuration_truck_info = 10,
            configuration_trailer_info = 11,
            configuration_job_info = 12,
            gameplay_job_cancelled_info = 13,
            gameplay_job_delivered_info = 14,
            gameplay_player_fined_info = 15,
            gameplay_player_tollgate_paid_info = 16,
            gameplay_player_use_ferry_info = 17,
            gameplay_player_use_train_info = 18,
            channel_paused = 19,
            channel_local_scale = 20,
            channel_game_time = 21,
            channel_multiplayer_time_offset = 22,
            channel_next_rest_stop = 23,
            job_channel_cargo_damage = 24,
            trailer_channel_connected = 25,
            trailer_channel_cargo_damage = 26,
            trailer_channel_world_placement = 27,
            trailer_channel_local_linear_velocity = 28,
            trailer_channel_local_angular_velocity = 29,
            trailer_channel_local_linear_acceleration = 30,
            trailer_channel_local_angular_acceleration = 31,
            trailer_channel_wear_body = 32,
            trailer_channel_wear_chassis = 33,
            trailer_channel_wear_wheels = 34,
            trailer_channel_wheel_susp_deflection = 35,
            trailer_channel_wheel_on_ground = 36,
            trailer_channel_wheel_substance = 37,
            trailer_channel_wheel_velocity = 38,
            trailer_channel_wheel_steering = 39,
            trailer_channel_wheel_rotation = 40,
            trailer_channel_wheel_lift = 41,
            trailer_channel_wheel_lift_offset = 42,
            truck_channel_world_placement = 43,
            truck_channel_local_linear_velocity = 44,
            truck_channel_local_angular_velocity = 45,
            truck_channel_local_linear_acceleration = 46,
            truck_channel_local_angular_acceleration = 47,
            truck_channel_cabin_offset = 48,
            truck_channel_cabin_angular_velocity = 49,
            truck_channel_cabin_angular_acceleration = 50,
            truck_channel_head_offset = 51,
            truck_channel_speed = 52,
            truck_channel_engine_rpm = 53,
            truck_channel_engine_gear = 54,
            truck_channel_displayed_gear = 55,
            truck_channel_input_steering = 56,
            truck_channel_input_throttle = 57,
            truck_channel_input_brake = 58,
            truck_channel_input_clutch = 59,
            truck_channel_effective_steering = 60,
            truck_channel_effective_throttle = 61,
            truck_channel_effective_brake = 62,
            truck_channel_effective_clutch = 63,
            truck_channel_cruise_control = 64,
            truck_channel_hshifter_slot = 65,
            truck_channel_hshifter_selector = 66,
            truck_channel_parking_brake = 67,
            truck_channel_motor_brake = 68,
            truck_channel_retarder_level = 69,
            truck_channel_brake_air_pressure = 70,
            truck_channel_brake_air_pressure_warning = 71,
            truck_channel_brake_air_pressure_emergency = 72,
            truck_channel_brake_temperature = 73,
            truck_channel_fuel = 74,
            truck_channel_fuel_warning = 75,
            truck_channel_fuel_average_consumption = 76,
            truck_channel_fuel_range = 77,
            truck_channel_adblue = 78,
            truck_channel_adblue_warning = 79,
            truck_channel_oil_pressure = 80,
            truck_channel_oil_pressure_warning = 81,
            truck_channel_oil_temperature = 82,
            truck_channel_water_temperature = 83,
            truck_channel_water_temperature_warning = 84,
            truck_channel_battery_voltage = 85,
            truck_channel_battery_voltage_warning = 86,
            truck_channel_electric_enabled = 87,
            truck_channel_engine_enabled = 88,
            truck_channel_lblinker = 89,
            truck_channel_rblinker = 90,
            truck_channel_hazard_warning = 91,
            truck_channel_light_lblinker = 92,
            truck_channel_light_rblinker = 93,
            truck_channel_light_parking = 94,
            truck_channel_light_low_beam = 95,
            truck_channel_light_high_beam = 96,
            truck_channel_light_aux_front = 97,
            truck_channel_light_aux_roof = 98,
            truck_channel_light_beacon = 99,
            truck_channel_light_brake = 100,
            truck_channel_light_reverse = 101,
            truck_channel_wipers = 102,
            truck_channel_dashboard_backlight = 103,
            truck_channel_differential_lock = 104,
            truck_channel_lift_axle = 105,
            truck_channel_lift_axle_indicator = 106,
            truck_channel_trailer_lift_axle = 107,
            truck_channel_trailer_lift_axle_indicator = 108,
            truck_channel_wear_engine = 109,
            truck_channel_wear_transmission = 110,
            truck_channel_wear_cabin = 111,
            truck_channel_wear_chassis = 112,
            truck_channel_wear_wheels = 113,
            truck_channel_odometer = 114,
            truck_channel_navigation_distance = 115,
            truck_channel_navigation_time = 116,
            truck_channel_navigation_speed_limit = 117,
            truck_channel_wheel_susp_deflection = 118,
            truck_channel_wheel_on_ground = 119,
            truck_channel_wheel_substance = 120,
            truck_channel_wheel_velocity = 121,
            truck_channel_wheel_steering = 122,
            truck_channel_wheel_rotation = 123,
            truck_channel_wheel_lift = 124,
            truck_channel_wheel_lift_offset = 125,
            invalid = static_cast<telemetry_id>(-1)
        };
    };

    using telemetry_ids::telemetry_id;

    namespace metadata {
        enum class telemetry_type : uint8_t {
            structure,
            event_info,
            channel,
            invalid = static_cast<telemetry_type>(-1),
        };

        constexpr const uint32_t INVALID_OFFSET = static_cast<uint32_t>(-1);

        constexpr const uint32_t INVALID_TRAILER_INDEX = static_cast<uint32_t>(-1);

        constexpr const uint32_t INVALID_SIZE = 0;

        constexpr const telemetry_id LIFETIME_INVALID_ID = telemetry_id::invalid;

        struct metadata_value {
            telemetry_id id;
            telemetry_type telemetry_type;
            uint32_t master_offset;
            uint32_t structure_offset;
            uint32_t storage_size;
            const char* macro_identifier;
            const char* macro;
            bool indexed;
            uint32_t max_count;
            bool trailer_channel;
            scs_value_type_t scs_type_id;
            bool custom_channel;

            constexpr metadata_value(
            telemetry_id id = telemetry_id::invalid,
            metadata::telemetry_type telemetry_type = truckconnect::metadata::telemetry_type::invalid,
            uint32_t master_offset = INVALID_OFFSET,
            uint32_t structure_offset = INVALID_OFFSET,
            uint32_t storage_size = INVALID_SIZE,
            const char* macro_identifier = nullptr,
            const char* macro = nullptr,
            bool indexed = false,
            uint32_t max_count = 1,
            bool trailer_channel = false,
            scs_value_type_t scs_type_id = SCS_VALUE_TYPE_INVALID,
            bool custom_channel = SCS_VALUE_TYPE_INVALID
        ) :
            id(id),
            telemetry_type(telemetry_type),
            master_offset(master_offset),
            structure_offset(structure_offset),
            storage_size(storage_size),
            macro_identifier(macro_identifier),
            macro(macro),
            indexed(indexed),
            max_count(max_count),
            trailer_channel(trailer_channel),
            scs_type_id(scs_type_id),
            custom_channel(custom_channel) {}
        };

        constexpr const size_t extract_trailer_index(const char* const cstr, const bool reversing = true, size_t count = 0) {
            return (
                reversing ?
                    extract_trailer_index(cstr + 1, *(cstr + 1) != '\0', count + 1) :
                    count == 0 ?
                        INVALID_OFFSET :
                        '0' <= *cstr && *cstr <= '9' ?
                            *cstr - '0' :
                            extract_trailer_index(cstr - 1, false, count - 1)
                );
        }

        constexpr const metadata_value INVALID_METADATA = metadata_value();

        struct master {
            static constexpr const telemetry_id id = telemetry_id::master;
            static constexpr const telemetry_type telemetry_type = telemetry_type::structure;
            static constexpr const uint32_t master_offset = 0;
            static constexpr const uint32_t structure_offset = 0;
            using storage_type = master_storage;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type));
        };

        struct configuration {
            static constexpr const telemetry_id id = telemetry_id::configuration;
            static constexpr const telemetry_type telemetry_type = telemetry_type::structure;
            static constexpr const uint32_t master_offset = offsetof(master_storage, configuration);
            using storage_type = master_storage::configuration_storage;
            static constexpr const uint32_t structure_offset = offsetof(master_storage, configuration);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type));
        };

        struct gameplay {
            static constexpr const telemetry_id id = telemetry_id::gameplay;
            static constexpr const telemetry_type telemetry_type = telemetry_type::structure;
            static constexpr const uint32_t master_offset = offsetof(master_storage, gameplay);
            using storage_type = master_storage::gameplay_storage;
            static constexpr const uint32_t structure_offset = offsetof(master_storage, gameplay);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type));
        };

        struct channels {
            static constexpr const telemetry_id id = telemetry_id::channels;
            static constexpr const telemetry_type telemetry_type = telemetry_type::structure;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels);
            using storage_type = master_storage::channels_storage;
            static constexpr const uint32_t structure_offset = offsetof(master_storage, channels);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type));
        };

        struct general {
            static constexpr const telemetry_id id = telemetry_id::general;
            static constexpr const telemetry_type telemetry_type = telemetry_type::structure;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.general);
            using storage_type = master_storage::channels_storage::general_storage;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage, general);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type));
        };

        struct truck {
            static constexpr const telemetry_id id = telemetry_id::truck;
            static constexpr const telemetry_type telemetry_type = telemetry_type::structure;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck);
            using storage_type = master_storage::channels_storage::truck_storage;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage, truck);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type));
        };

        struct trailer {
            static constexpr const telemetry_id id = telemetry_id::trailer;
            static constexpr const telemetry_type telemetry_type = telemetry_type::structure;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer);
            using storage_type = master_storage::channels_storage::trailer_storage;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage, trailer);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type));
        };

        struct configuration_substances_info {
            static constexpr const telemetry_id id = telemetry_id::configuration_substances_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, configuration.configuration_substances_info);
            using storage_type = master_storage::configuration_storage::configuration_substances_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CONFIG_substances";
            static constexpr const char* const macro = "substances";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::configuration_storage, configuration_substances_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct configuration_controls_info {
            static constexpr const telemetry_id id = telemetry_id::configuration_controls_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, configuration.configuration_controls_info);
            using storage_type = master_storage::configuration_storage::configuration_controls_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CONFIG_controls";
            static constexpr const char* const macro = "controls";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::configuration_storage, configuration_controls_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct configuration_hshifter_info {
            static constexpr const telemetry_id id = telemetry_id::configuration_hshifter_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, configuration.configuration_hshifter_info);
            using storage_type = master_storage::configuration_storage::configuration_hshifter_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CONFIG_hshifter";
            static constexpr const char* const macro = "hshifter";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::configuration_storage, configuration_hshifter_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct configuration_truck_info {
            static constexpr const telemetry_id id = telemetry_id::configuration_truck_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, configuration.configuration_truck_info);
            using storage_type = master_storage::configuration_storage::configuration_truck_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CONFIG_truck";
            static constexpr const char* const macro = "truck";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::configuration_storage, configuration_truck_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct configuration_trailer_info {
            static constexpr const telemetry_id id = telemetry_id::configuration_trailer_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, configuration.configuration_trailer_info);
            using storage_type = master_storage::configuration_storage::configuration_trailer_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CONFIG_trailer";
            static constexpr const char* const macro = "trailer";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::configuration_storage, configuration_trailer_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct configuration_job_info {
            static constexpr const telemetry_id id = telemetry_id::configuration_job_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, configuration.configuration_job_info);
            using storage_type = master_storage::configuration_storage::configuration_job_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CONFIG_job";
            static constexpr const char* const macro = "job";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::configuration_storage, configuration_job_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct gameplay_job_cancelled_info {
            static constexpr const telemetry_id id = telemetry_id::gameplay_job_cancelled_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, gameplay.gameplay_job_cancelled_info);
            using storage_type = master_storage::gameplay_storage::gameplay_job_cancelled_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_GAMEPLAY_EVENT_job_cancelled";
            static constexpr const char* const macro = "job.cancelled";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::gameplay_storage, gameplay_job_cancelled_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct gameplay_job_delivered_info {
            static constexpr const telemetry_id id = telemetry_id::gameplay_job_delivered_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, gameplay.gameplay_job_delivered_info);
            using storage_type = master_storage::gameplay_storage::gameplay_job_delivered_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_GAMEPLAY_EVENT_job_delivered";
            static constexpr const char* const macro = "job.delivered";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::gameplay_storage, gameplay_job_delivered_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct gameplay_player_fined_info {
            static constexpr const telemetry_id id = telemetry_id::gameplay_player_fined_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, gameplay.gameplay_player_fined_info);
            using storage_type = master_storage::gameplay_storage::gameplay_player_fined_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_GAMEPLAY_EVENT_player_fined";
            static constexpr const char* const macro = "player.fined";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::gameplay_storage, gameplay_player_fined_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct gameplay_player_tollgate_paid_info {
            static constexpr const telemetry_id id = telemetry_id::gameplay_player_tollgate_paid_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, gameplay.gameplay_player_tollgate_paid_info);
            using storage_type = master_storage::gameplay_storage::gameplay_player_tollgate_paid_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_GAMEPLAY_EVENT_player_tollgate_paid";
            static constexpr const char* const macro = "player.tollgate.paid";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::gameplay_storage, gameplay_player_tollgate_paid_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct gameplay_player_use_ferry_info {
            static constexpr const telemetry_id id = telemetry_id::gameplay_player_use_ferry_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, gameplay.gameplay_player_use_ferry_info);
            using storage_type = master_storage::gameplay_storage::gameplay_player_use_ferry_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_GAMEPLAY_EVENT_player_use_ferry";
            static constexpr const char* const macro = "player.use.ferry";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::gameplay_storage, gameplay_player_use_ferry_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct gameplay_player_use_train_info {
            static constexpr const telemetry_id id = telemetry_id::gameplay_player_use_train_info;
            static constexpr const telemetry_type telemetry_type = telemetry_type::event_info;
            static constexpr const uint32_t master_offset = offsetof(master_storage, gameplay.gameplay_player_use_train_info);
            using storage_type = master_storage::gameplay_storage::gameplay_player_use_train_storage;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_GAMEPLAY_EVENT_player_use_train";
            static constexpr const char* const macro = "player.use.train";
            static constexpr const uint32_t structure_offset = offsetof(master_storage::gameplay_storage, gameplay_player_use_train_info);
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro);
        };

        struct channel_paused {
            static constexpr const telemetry_id id = telemetry_id::channel_paused;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.general.channel_paused);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "channel_paused";
            static constexpr const char* const macro = "";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::general_storage, channel_paused);
            static constexpr const bool custom_channel = true;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct channel_local_scale {
            static constexpr const telemetry_id id = telemetry_id::channel_local_scale;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.general.channel_local_scale);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CHANNEL_local_scale";
            static constexpr const char* const macro = "local.scale";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::general_storage, channel_local_scale);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct channel_game_time {
            static constexpr const telemetry_id id = telemetry_id::channel_game_time;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.general.channel_game_time);
            using storage_type = value_storage<uint32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CHANNEL_game_time";
            static constexpr const char* const macro = "game.time";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_u32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_u32;
            using primitive_type = uint32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::general_storage, channel_game_time);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct channel_multiplayer_time_offset {
            static constexpr const telemetry_id id = telemetry_id::channel_multiplayer_time_offset;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.general.channel_multiplayer_time_offset);
            using storage_type = value_storage<int32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CHANNEL_multiplayer_time_offset";
            static constexpr const char* const macro = "multiplayer.time.offset";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_s32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_s32;
            using primitive_type = int32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::general_storage, channel_multiplayer_time_offset);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct channel_next_rest_stop {
            static constexpr const telemetry_id id = telemetry_id::channel_next_rest_stop;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.general.channel_next_rest_stop);
            using storage_type = value_storage<int32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_CHANNEL_next_rest_stop";
            static constexpr const char* const macro = "rest.stop";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_s32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_s32;
            using primitive_type = int32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::general_storage, channel_next_rest_stop);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct job_channel_cargo_damage {
            static constexpr const telemetry_id id = telemetry_id::job_channel_cargo_damage;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.general.job_channel_cargo_damage);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_JOB_CHANNEL_cargo_damage";
            static constexpr const char* const macro = "job.cargo.damage";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::general_storage, job_channel_cargo_damage);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct trailer_channel_connected {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_connected;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_connected);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_connected";
            static constexpr const char* const macro = "trailer.connected";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_connected);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_cargo_damage {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_cargo_damage;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_cargo_damage);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_cargo_damage";
            static constexpr const char* const macro = "trailer.cargo.damage";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_cargo_damage);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_world_placement {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_world_placement;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_world_placement);
            using storage_type = value_storage<scs_value_dplacement_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_world_placement";
            static constexpr const char* const macro = "trailer.world.placement";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_dplacement_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_dplacement;
            using primitive_type = scs_value_dplacement_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_world_placement);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_local_linear_velocity {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_linear_velocity;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_local_linear_velocity);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_velocity";
            static constexpr const char* const macro = "trailer.velocity.linear";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_local_linear_velocity);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_local_angular_velocity {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_angular_velocity;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_local_angular_velocity);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_velocity";
            static constexpr const char* const macro = "trailer.velocity.angular";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_local_angular_velocity);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_local_linear_acceleration {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_linear_acceleration;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_local_linear_acceleration);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_local_linear_acceleration";
            static constexpr const char* const macro = "trailer.acceleration.linear";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_local_linear_acceleration);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_local_angular_acceleration {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_local_angular_acceleration;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_local_angular_acceleration);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_local_angular_acceleration";
            static constexpr const char* const macro = "trailer.acceleration.angular";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_local_angular_acceleration);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wear_body {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wear_body;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wear_body);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wear_body";
            static constexpr const char* const macro = "trailer.wear.body";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wear_body);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wear_chassis {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wear_chassis;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wear_chassis);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wear_chassis";
            static constexpr const char* const macro = "trailer.wear.chassis";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wear_chassis);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wear_wheels {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wear_wheels;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wear_wheels);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wear_wheels";
            static constexpr const char* const macro = "trailer.wear.wheels";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wear_wheels);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_susp_deflection {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_susp_deflection;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_susp_deflection);
            using storage_type = value_array_storage<float, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_susp_deflection";
            static constexpr const char* const macro = "trailer.wheel.suspension.deflection";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_susp_deflection);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_on_ground {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_on_ground;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_on_ground);
            using storage_type = value_array_storage<bool, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_on_ground";
            static constexpr const char* const macro = "trailer.wheel.on_ground";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_on_ground);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_substance {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_substance;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_substance);
            using storage_type = value_array_storage<uint32_t, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_substance";
            static constexpr const char* const macro = "trailer.wheel.substance";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_u32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_u32;
            using primitive_type = uint32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_substance);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_velocity {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_velocity;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_velocity);
            using storage_type = value_array_storage<float, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_velocity";
            static constexpr const char* const macro = "trailer.wheel.angular_velocity";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_velocity);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_steering {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_steering;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_steering);
            using storage_type = value_array_storage<float, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_steering";
            static constexpr const char* const macro = "trailer.wheel.steering";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_steering);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_rotation {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_rotation;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_rotation);
            using storage_type = value_array_storage<float, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_rotation";
            static constexpr const char* const macro = "trailer.wheel.rotation";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_rotation);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_lift {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_lift;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_lift);
            using storage_type = value_array_storage<float, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift";
            static constexpr const char* const macro = "trailer.wheel.lift";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_lift);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct trailer_channel_wheel_lift_offset {
            static constexpr const telemetry_id id = telemetry_id::trailer_channel_wheel_lift_offset;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.trailer._Elems[0].trailer_channel_wheel_lift_offset);
            using storage_type = value_array_storage<float, 19>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRAILER_CHANNEL_wheel_lift_offset";
            static constexpr const char* const macro = "trailer.wheel.lift.offset";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 19;
            static constexpr const bool trailer_channel = true;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::trailer_storage, trailer_channel_wheel_lift_offset);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
            static constexpr const uint32_t master_offset_of_trailer_index(const uint32_t& trailer_index) { return 0 <= trailer_index &&  trailer_index < SCS_TELEMETRY_trailers_count ? (master_offset + sizeof(master_storage::channels_storage::trailer_storage) * trailer_index) : INVALID_OFFSET; }
        };

        struct truck_channel_world_placement {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_world_placement;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_world_placement);
            using storage_type = value_storage<scs_value_dplacement_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_world_placement";
            static constexpr const char* const macro = "truck.world.placement";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_dplacement_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_dplacement;
            using primitive_type = scs_value_dplacement_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_world_placement);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_local_linear_velocity {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_local_linear_velocity;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_local_linear_velocity);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_velocity";
            static constexpr const char* const macro = "truck.local.velocity.linear";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_local_linear_velocity);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_local_angular_velocity {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_local_angular_velocity;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_local_angular_velocity);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_velocity";
            static constexpr const char* const macro = "truck.local.velocity.angular";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_local_angular_velocity);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_local_linear_acceleration {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_local_linear_acceleration;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_local_linear_acceleration);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_acceleration";
            static constexpr const char* const macro = "truck.local.acceleration.linear";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_local_linear_acceleration);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_local_angular_acceleration {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_local_angular_acceleration;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_local_angular_acceleration);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_acceleration";
            static constexpr const char* const macro = "truck.local.acceleration.angular";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_local_angular_acceleration);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_cabin_offset {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_cabin_offset;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_cabin_offset);
            using storage_type = value_storage<scs_value_fplacement_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_cabin_offset";
            static constexpr const char* const macro = "truck.cabin.offset";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fplacement_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fplacement;
            using primitive_type = scs_value_fplacement_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_cabin_offset);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_cabin_angular_velocity {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_cabin_angular_velocity;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_cabin_angular_velocity);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_velocity";
            static constexpr const char* const macro = "truck.cabin.velocity.angular";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_cabin_angular_velocity);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_cabin_angular_acceleration {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_cabin_angular_acceleration;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_cabin_angular_acceleration);
            using storage_type = value_storage<scs_value_fvector_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_acceleration";
            static constexpr const char* const macro = "truck.cabin.acceleration.angular";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fvector_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fvector;
            using primitive_type = scs_value_fvector_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_cabin_angular_acceleration);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_head_offset {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_head_offset;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_head_offset);
            using storage_type = value_storage<scs_value_fplacement_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_head_offset";
            static constexpr const char* const macro = "truck.head.offset";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_fplacement_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_fplacement;
            using primitive_type = scs_value_fplacement_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_head_offset);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_speed {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_speed;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_speed);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_speed";
            static constexpr const char* const macro = "truck.speed";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_speed);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_engine_rpm {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_engine_rpm;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_engine_rpm);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm";
            static constexpr const char* const macro = "truck.engine.rpm";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_engine_rpm);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_engine_gear {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_engine_gear;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_engine_gear);
            using storage_type = value_storage<int32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_engine_gear";
            static constexpr const char* const macro = "truck.engine.gear";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_s32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_s32;
            using primitive_type = int32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_engine_gear);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_displayed_gear {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_displayed_gear;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_displayed_gear);
            using storage_type = value_storage<int32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_displayed_gear";
            static constexpr const char* const macro = "truck.displayed.gear";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_s32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_s32;
            using primitive_type = int32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_displayed_gear);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_input_steering {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_input_steering;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_input_steering);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_input_steering";
            static constexpr const char* const macro = "truck.input.steering";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_input_steering);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_input_throttle {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_input_throttle;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_input_throttle);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_input_throttle";
            static constexpr const char* const macro = "truck.input.throttle";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_input_throttle);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_input_brake {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_input_brake;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_input_brake);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_input_brake";
            static constexpr const char* const macro = "truck.input.brake";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_input_brake);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_input_clutch {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_input_clutch;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_input_clutch);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_input_clutch";
            static constexpr const char* const macro = "truck.input.clutch";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_input_clutch);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_effective_steering {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_steering;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_effective_steering);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_effective_steering";
            static constexpr const char* const macro = "truck.effective.steering";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_effective_steering);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_effective_throttle {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_throttle;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_effective_throttle);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_effective_throttle";
            static constexpr const char* const macro = "truck.effective.throttle";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_effective_throttle);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_effective_brake {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_brake;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_effective_brake);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_effective_brake";
            static constexpr const char* const macro = "truck.effective.brake";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_effective_brake);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_effective_clutch {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_effective_clutch;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_effective_clutch);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_effective_clutch";
            static constexpr const char* const macro = "truck.effective.clutch";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_effective_clutch);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_cruise_control {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_cruise_control;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_cruise_control);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_cruise_control";
            static constexpr const char* const macro = "truck.cruise_control";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_cruise_control);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_hshifter_slot {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_hshifter_slot;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_hshifter_slot);
            using storage_type = value_storage<uint32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_slot";
            static constexpr const char* const macro = "truck.hshifter.slot";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_u32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_u32;
            using primitive_type = uint32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_hshifter_slot);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_hshifter_selector {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_hshifter_selector;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_hshifter_selector);
            using storage_type = value_array_storage<bool, 2>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_selector";
            static constexpr const char* const macro = "truck.hshifter.select";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 2;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_hshifter_selector);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_parking_brake {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_parking_brake;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_parking_brake);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_parking_brake";
            static constexpr const char* const macro = "truck.brake.parking";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_parking_brake);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_motor_brake {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_motor_brake;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_motor_brake);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_motor_brake";
            static constexpr const char* const macro = "truck.brake.motor";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_motor_brake);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_retarder_level {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_retarder_level;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_retarder_level);
            using storage_type = value_storage<uint32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_retarder_level";
            static constexpr const char* const macro = "truck.brake.retarder";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_u32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_u32;
            using primitive_type = uint32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_retarder_level);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_brake_air_pressure {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_air_pressure;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_brake_air_pressure);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure";
            static constexpr const char* const macro = "truck.brake.air.pressure";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_brake_air_pressure);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_brake_air_pressure_warning {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_air_pressure_warning;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_brake_air_pressure_warning);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_warning";
            static constexpr const char* const macro = "truck.brake.air.pressure.warning";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_brake_air_pressure_warning);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_brake_air_pressure_emergency {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_air_pressure_emergency;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_brake_air_pressure_emergency);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_emergency";
            static constexpr const char* const macro = "truck.brake.air.pressure.emergency";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_brake_air_pressure_emergency);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_brake_temperature {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_brake_temperature;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_brake_temperature);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_brake_temperature";
            static constexpr const char* const macro = "truck.brake.temperature";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_brake_temperature);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_fuel {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_fuel);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_fuel";
            static constexpr const char* const macro = "truck.fuel.amount";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_fuel);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_fuel_warning {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel_warning;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_fuel_warning);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_fuel_warning";
            static constexpr const char* const macro = "truck.fuel.warning";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_fuel_warning);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_fuel_average_consumption {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel_average_consumption;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_fuel_average_consumption);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_fuel_average_consumption";
            static constexpr const char* const macro = "truck.fuel.consumption.average";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_fuel_average_consumption);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_fuel_range {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_fuel_range;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_fuel_range);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_fuel_range";
            static constexpr const char* const macro = "truck.fuel.range";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_fuel_range);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_adblue {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_adblue;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_adblue);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_adblue";
            static constexpr const char* const macro = "truck.adblue";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_adblue);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_adblue_warning {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_adblue_warning;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_adblue_warning);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_adblue_warning";
            static constexpr const char* const macro = "truck.adblue.warning";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_adblue_warning);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_oil_pressure {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_oil_pressure;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_oil_pressure);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure";
            static constexpr const char* const macro = "truck.oil.pressure";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_oil_pressure);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_oil_pressure_warning {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_oil_pressure_warning;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_oil_pressure_warning);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure_warning";
            static constexpr const char* const macro = "truck.oil.pressure.warning";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_oil_pressure_warning);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_oil_temperature {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_oil_temperature;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_oil_temperature);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_oil_temperature";
            static constexpr const char* const macro = "truck.oil.temperature";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_oil_temperature);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_water_temperature {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_water_temperature;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_water_temperature);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature";
            static constexpr const char* const macro = "truck.water.temperature";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_water_temperature);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_water_temperature_warning {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_water_temperature_warning;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_water_temperature_warning);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature_warning";
            static constexpr const char* const macro = "truck.water.temperature.warning";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_water_temperature_warning);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_battery_voltage {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_battery_voltage;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_battery_voltage);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage";
            static constexpr const char* const macro = "truck.battery.voltage";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_battery_voltage);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_battery_voltage_warning {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_battery_voltage_warning;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_battery_voltage_warning);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage_warning";
            static constexpr const char* const macro = "truck.battery.voltage.warning";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_battery_voltage_warning);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_electric_enabled {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_electric_enabled;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_electric_enabled);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_electric_enabled";
            static constexpr const char* const macro = "truck.electric.enabled";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_electric_enabled);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_engine_enabled {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_engine_enabled;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_engine_enabled);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_engine_enabled";
            static constexpr const char* const macro = "truck.engine.enabled";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_engine_enabled);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_lblinker {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_lblinker;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_lblinker);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_lblinker";
            static constexpr const char* const macro = "truck.lblinker";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_lblinker);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_rblinker {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_rblinker;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_rblinker);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_rblinker";
            static constexpr const char* const macro = "truck.rblinker";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_rblinker);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_hazard_warning {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_hazard_warning;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_hazard_warning);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_hazard_warning";
            static constexpr const char* const macro = "truck.hazard.warning";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_hazard_warning);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_lblinker {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_lblinker;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_lblinker);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_lblinker";
            static constexpr const char* const macro = "truck.light.lblinker";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_lblinker);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_rblinker {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_rblinker;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_rblinker);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_rblinker";
            static constexpr const char* const macro = "truck.light.rblinker";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_rblinker);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_parking {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_parking;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_parking);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_parking";
            static constexpr const char* const macro = "truck.light.parking";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_parking);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_low_beam {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_low_beam;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_low_beam);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_low_beam";
            static constexpr const char* const macro = "truck.light.beam.low";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_low_beam);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_high_beam {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_high_beam;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_high_beam);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_high_beam";
            static constexpr const char* const macro = "truck.light.beam.high";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_high_beam);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_aux_front {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_aux_front;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_aux_front);
            using storage_type = value_storage<uint32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_front";
            static constexpr const char* const macro = "truck.light.aux.front";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_u32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_u32;
            using primitive_type = uint32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_aux_front);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_aux_roof {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_aux_roof;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_aux_roof);
            using storage_type = value_storage<uint32_t>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_roof";
            static constexpr const char* const macro = "truck.light.aux.roof";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_u32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_u32;
            using primitive_type = uint32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_aux_roof);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_beacon {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_beacon;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_beacon);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_beacon";
            static constexpr const char* const macro = "truck.light.beacon";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_beacon);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_brake {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_brake;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_brake);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_brake";
            static constexpr const char* const macro = "truck.light.brake";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_brake);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_light_reverse {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_light_reverse;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_light_reverse);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_light_reverse";
            static constexpr const char* const macro = "truck.light.reverse";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_light_reverse);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wipers {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wipers;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wipers);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wipers";
            static constexpr const char* const macro = "truck.wipers";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wipers);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_dashboard_backlight {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_dashboard_backlight;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_dashboard_backlight);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_dashboard_backlight";
            static constexpr const char* const macro = "truck.dashboard.backlight";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_dashboard_backlight);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_differential_lock {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_differential_lock;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_differential_lock);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_differential_lock";
            static constexpr const char* const macro = "truck.differential_lock";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_differential_lock);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_lift_axle {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_lift_axle;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_lift_axle);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle";
            static constexpr const char* const macro = "truck.lift_axle";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_lift_axle);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_lift_axle_indicator {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_lift_axle_indicator;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_lift_axle_indicator);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle_indicator";
            static constexpr const char* const macro = "truck.lift_axle.indicator";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_lift_axle_indicator);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_trailer_lift_axle {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_trailer_lift_axle;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_trailer_lift_axle);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle";
            static constexpr const char* const macro = "truck.trailer.lift_axle";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_trailer_lift_axle);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_trailer_lift_axle_indicator {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_trailer_lift_axle_indicator;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_trailer_lift_axle_indicator);
            using storage_type = value_storage<bool>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle_indicator";
            static constexpr const char* const macro = "truck.trailer.lift_axle.indicator";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_trailer_lift_axle_indicator);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wear_engine {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_engine;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wear_engine);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wear_engine";
            static constexpr const char* const macro = "truck.wear.engine";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wear_engine);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wear_transmission {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_transmission;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wear_transmission);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wear_transmission";
            static constexpr const char* const macro = "truck.wear.transmission";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wear_transmission);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wear_cabin {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_cabin;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wear_cabin);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wear_cabin";
            static constexpr const char* const macro = "truck.wear.cabin";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wear_cabin);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wear_chassis {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_chassis;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wear_chassis);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wear_chassis";
            static constexpr const char* const macro = "truck.wear.chassis";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wear_chassis);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wear_wheels {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wear_wheels;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wear_wheels);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wear_wheels";
            static constexpr const char* const macro = "truck.wear.wheels";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wear_wheels);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_odometer {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_odometer;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_odometer);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_odometer";
            static constexpr const char* const macro = "truck.odometer";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_odometer);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_navigation_distance {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_navigation_distance;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_navigation_distance);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_navigation_distance";
            static constexpr const char* const macro = "truck.navigation.distance";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_navigation_distance);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_navigation_time {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_navigation_time;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_navigation_time);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_navigation_time";
            static constexpr const char* const macro = "truck.navigation.time";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_navigation_time);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_navigation_speed_limit {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_navigation_speed_limit;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_navigation_speed_limit);
            using storage_type = value_storage<float>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_navigation_speed_limit";
            static constexpr const char* const macro = "truck.navigation.speed.limit";
            static constexpr const bool indexed = false;
            static constexpr const uint32_t max_count = 1;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_navigation_speed_limit);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_susp_deflection {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_susp_deflection;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_susp_deflection);
            using storage_type = value_array_storage<float, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_susp_deflection";
            static constexpr const char* const macro = "truck.wheel.suspension.deflection";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_susp_deflection);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_on_ground {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_on_ground;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_on_ground);
            using storage_type = value_array_storage<bool, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_on_ground";
            static constexpr const char* const macro = "truck.wheel.on_ground";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_bool_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_bool;
            using primitive_type = bool;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_on_ground);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_substance {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_substance;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_substance);
            using storage_type = value_array_storage<uint32_t, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_substance";
            static constexpr const char* const macro = "truck.wheel.substance";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_u32_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_u32;
            using primitive_type = uint32_t;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_substance);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_velocity {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_velocity;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_velocity);
            using storage_type = value_array_storage<float, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_velocity";
            static constexpr const char* const macro = "truck.wheel.angular_velocity";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_velocity);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_steering {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_steering;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_steering);
            using storage_type = value_array_storage<float, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_steering";
            static constexpr const char* const macro = "truck.wheel.steering";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_steering);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_rotation {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_rotation;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_rotation);
            using storage_type = value_array_storage<float, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_rotation";
            static constexpr const char* const macro = "truck.wheel.rotation";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_rotation);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_lift {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_lift;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_lift);
            using storage_type = value_array_storage<float, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift";
            static constexpr const char* const macro = "truck.wheel.lift";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_lift);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };

        struct truck_channel_wheel_lift_offset {
            static constexpr const telemetry_id id = telemetry_id::truck_channel_wheel_lift_offset;
            static constexpr const telemetry_type telemetry_type = telemetry_type::channel;
            static constexpr const uint32_t master_offset = offsetof(master_storage, channels.truck.truck_channel_wheel_lift_offset);
            using storage_type = value_array_storage<float, 14>;
            static constexpr const char* const macro_identifier = "SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift_offset";
            static constexpr const char* const macro = "truck.wheel.lift.offset";
            static constexpr const bool indexed = true;
            static constexpr const uint32_t max_count = 14;
            static constexpr const bool trailer_channel = false;
            using scs_type = scs_value_float_t;
            static constexpr scs_value_type_t scs_type_id = SCS_VALUE_TYPE_float;
            using primitive_type = float;
            static constexpr const uint32_t structure_offset = offsetof(master_storage::channels_storage::truck_storage, truck_channel_wheel_lift_offset);
            static constexpr const bool custom_channel = false;
            static constexpr const metadata_value metadata_value = metadata_value(id, telemetry_type, master_offset, structure_offset, sizeof(storage_type), macro_identifier, macro, indexed, max_count, trailer_channel, scs_type_id, custom_channel);
        };
    }
}