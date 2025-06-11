#include "byte_converters.h"
#include "telemetry_metadata.h"
#include "packed_size.h"

namespace truckconnect {
    void append_bytes(const master_storage::gameplay_storage::gameplay_player_use_train_storage& gameplay_player_use_train_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_use_train_info);
        out.reserve(packed_size);
        append_bytes(gameplay_player_use_train_info.latest, out);
        append_bytes(gameplay_player_use_train_info.pay_amount, out);
        append_bytes(gameplay_player_use_train_info.source_name, out);
        append_bytes(gameplay_player_use_train_info.target_name, out);
        append_bytes(gameplay_player_use_train_info.source_id, out);
        append_bytes(gameplay_player_use_train_info.target_id, out);
    }

    void append_bytes(const master_storage::gameplay_storage::gameplay_player_use_ferry_storage& gameplay_player_use_ferry_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_use_ferry_info);
        out.reserve(packed_size);
        append_bytes(gameplay_player_use_ferry_info.latest, out);
        append_bytes(gameplay_player_use_ferry_info.pay_amount, out);
        append_bytes(gameplay_player_use_ferry_info.source_name, out);
        append_bytes(gameplay_player_use_ferry_info.target_name, out);
        append_bytes(gameplay_player_use_ferry_info.source_id, out);
        append_bytes(gameplay_player_use_ferry_info.target_id, out);
    }

    void append_bytes(const master_storage::gameplay_storage::gameplay_player_tollgate_paid_storage& gameplay_player_tollgate_paid_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_tollgate_paid_info);
        out.reserve(packed_size);
        append_bytes(gameplay_player_tollgate_paid_info.latest, out);
        append_bytes(gameplay_player_tollgate_paid_info.pay_amount, out);
    }

    void append_bytes(const master_storage::gameplay_storage::gameplay_player_fined_storage& gameplay_player_fined_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_fined_info);
        out.reserve(packed_size);
        append_bytes(gameplay_player_fined_info.latest, out);
        append_bytes(gameplay_player_fined_info.fine_offence, out);
        append_bytes(gameplay_player_fined_info.fine_amount, out);
    }

    void append_bytes(const master_storage::gameplay_storage::gameplay_job_delivered_storage& gameplay_job_delivered_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_job_delivered_info);
        out.reserve(packed_size);
        append_bytes(gameplay_job_delivered_info.latest, out);
        append_bytes(gameplay_job_delivered_info.revenue, out);
        append_bytes(gameplay_job_delivered_info.earned_xp, out);
        append_bytes(gameplay_job_delivered_info.cargo_damage, out);
        append_bytes(gameplay_job_delivered_info.distance_km, out);
        append_bytes(gameplay_job_delivered_info.delivery_time, out);
        append_bytes(gameplay_job_delivered_info.auto_park_used, out);
        append_bytes(gameplay_job_delivered_info.auto_load_used, out);
    }

    void append_bytes(const master_storage::gameplay_storage::gameplay_job_cancelled_storage& gameplay_job_cancelled_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_job_cancelled_info);
        out.reserve(packed_size);
        append_bytes(gameplay_job_cancelled_info.latest, out);
        append_bytes(gameplay_job_cancelled_info.cancel_penalty, out);
    }

    void append_bytes(const master_storage::configuration_storage::configuration_job_storage& configuration_job_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_job_info);
        out.reserve(packed_size);
        append_bytes(configuration_job_info.latest, out);
        append_bytes(configuration_job_info.cargo_id, out);
        append_bytes(configuration_job_info.cargo, out);
        append_bytes(configuration_job_info.cargo_mass, out);
        append_bytes(configuration_job_info.destination_city_id, out);
        append_bytes(configuration_job_info.cargo_unit_mass, out);
        append_bytes(configuration_job_info.cargo_unit_count, out);
        append_bytes(configuration_job_info.destination_city, out);
        append_bytes(configuration_job_info.source_city_id, out);
        append_bytes(configuration_job_info.source_city, out);
        append_bytes(configuration_job_info.destination_company_id, out);
        append_bytes(configuration_job_info.destination_company, out);
        append_bytes(configuration_job_info.source_company_id, out);
        append_bytes(configuration_job_info.source_company, out);
        append_bytes(configuration_job_info.income, out);
        append_bytes(configuration_job_info.delivery_time, out);
        append_bytes(configuration_job_info.is_cargo_loaded, out);
        append_bytes(configuration_job_info.job_market, out);
        append_bytes(configuration_job_info.special_job, out);
        append_bytes(configuration_job_info.planned_distance_km, out);
    }

    void append_bytes(const master_storage::configuration_storage::configuration_trailer_storage& configuration_trailer_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_trailer_info);
        out.reserve(packed_size);
        append_bytes(configuration_trailer_info.latest, out);
        append_bytes(configuration_trailer_info.id, out);
        append_bytes(configuration_trailer_info.cargo_accessory_id, out);
        append_bytes(configuration_trailer_info.hook_position, out);
        append_bytes(configuration_trailer_info.brand_id, out);
        append_bytes(configuration_trailer_info.brand, out);
        append_bytes(configuration_trailer_info.name, out);
        append_bytes(configuration_trailer_info.chain_type, out);
        append_bytes(configuration_trailer_info.body_type, out);
        append_bytes(configuration_trailer_info.license_plate, out);
        append_bytes(configuration_trailer_info.license_plate_country, out);
        append_bytes(configuration_trailer_info.license_plate_country_id, out);
        append_bytes(configuration_trailer_info.wheel_count, out);
        append_bytes(configuration_trailer_info.wheel_position, out);
        append_bytes(configuration_trailer_info.wheel_steerable, out);
        append_bytes(configuration_trailer_info.wheel_simulated, out);
        append_bytes(configuration_trailer_info.wheel_radius, out);
        append_bytes(configuration_trailer_info.wheel_powered, out);
        append_bytes(configuration_trailer_info.wheel_liftable, out);
    }

    void append_bytes(const master_storage::configuration_storage::configuration_truck_storage& configuration_truck_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_truck_info);
        out.reserve(packed_size);
        append_bytes(configuration_truck_info.latest, out);
        append_bytes(configuration_truck_info.brand_id, out);
        append_bytes(configuration_truck_info.brand, out);
        append_bytes(configuration_truck_info.id, out);
        append_bytes(configuration_truck_info.name, out);
        append_bytes(configuration_truck_info.fuel_capacity, out);
        append_bytes(configuration_truck_info.fuel_warning_factor, out);
        append_bytes(configuration_truck_info.adblue_capacity, out);
        append_bytes(configuration_truck_info.adblue_warning_factor, out);
        append_bytes(configuration_truck_info.air_pressure_warning, out);
        append_bytes(configuration_truck_info.air_pressure_emergency, out);
        append_bytes(configuration_truck_info.oil_pressure_warning, out);
        append_bytes(configuration_truck_info.water_temperature_warning, out);
        append_bytes(configuration_truck_info.battery_voltage_warning, out);
        append_bytes(configuration_truck_info.rpm_limit, out);
        append_bytes(configuration_truck_info.forward_gear_count, out);
        append_bytes(configuration_truck_info.reverse_gear_count, out);
        append_bytes(configuration_truck_info.differential_ratio, out);
        append_bytes(configuration_truck_info.retarder_step_count, out);
        append_bytes(configuration_truck_info.cabin_position, out);
        append_bytes(configuration_truck_info.forward_ratio, out);
        append_bytes(configuration_truck_info.reverse_ratio, out);
        append_bytes(configuration_truck_info.head_position, out);
        append_bytes(configuration_truck_info.hook_position, out);
        append_bytes(configuration_truck_info.license_plate, out);
        append_bytes(configuration_truck_info.license_plate_country, out);
        append_bytes(configuration_truck_info.license_plate_country_id, out);
        append_bytes(configuration_truck_info.wheel_count, out);
        append_bytes(configuration_truck_info.wheel_position, out);
        append_bytes(configuration_truck_info.wheel_steerable, out);
        append_bytes(configuration_truck_info.wheel_simulated, out);
        append_bytes(configuration_truck_info.wheel_radius, out);
        append_bytes(configuration_truck_info.wheel_powered, out);
        append_bytes(configuration_truck_info.wheel_liftable, out);
    }

    void append_bytes(const master_storage::configuration_storage::configuration_hshifter_storage& configuration_hshifter_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_hshifter_info);
        out.reserve(packed_size);
        append_bytes(configuration_hshifter_info.latest, out);
        append_bytes(configuration_hshifter_info.selector_count, out);
        append_bytes(configuration_hshifter_info.slot_gear, out);
        append_bytes(configuration_hshifter_info.slot_handle_position, out);
        append_bytes(configuration_hshifter_info.slot_selectors, out);
    }

    void append_bytes(const master_storage::configuration_storage::configuration_controls_storage& configuration_controls_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_controls_info);
        out.reserve(packed_size);
        append_bytes(configuration_controls_info.latest, out);
        append_bytes(configuration_controls_info.shifter_type, out);
    }

    void append_bytes(const master_storage::configuration_storage::configuration_substances_storage& configuration_substances_info, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_substances_info);
        out.reserve(packed_size);
        append_bytes(configuration_substances_info.latest, out);
        append_bytes(configuration_substances_info.id, out);
    }

    void append_bytes(const master_storage::channels_storage::trailer_storage& trailer, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::trailer);
        out.reserve(packed_size);
        //reserve the packed size of the structure.
        append_bytes(trailer.trailer_channel_connected, out);
        append_bytes(trailer.trailer_channel_cargo_damage, out);
        append_bytes(trailer.trailer_channel_world_placement, out);
        append_bytes(trailer.trailer_channel_local_linear_velocity, out);
        append_bytes(trailer.trailer_channel_local_angular_velocity, out);
        append_bytes(trailer.trailer_channel_local_linear_acceleration, out);
        append_bytes(trailer.trailer_channel_local_angular_acceleration, out);
        append_bytes(trailer.trailer_channel_wear_body, out);
        append_bytes(trailer.trailer_channel_wear_chassis, out);
        append_bytes(trailer.trailer_channel_wear_wheels, out);
        append_bytes(trailer.trailer_channel_wheel_susp_deflection, out);
        append_bytes(trailer.trailer_channel_wheel_on_ground, out);
        append_bytes(trailer.trailer_channel_wheel_substance, out);
        append_bytes(trailer.trailer_channel_wheel_velocity, out);
        append_bytes(trailer.trailer_channel_wheel_steering, out);
        append_bytes(trailer.trailer_channel_wheel_rotation, out);
        append_bytes(trailer.trailer_channel_wheel_lift, out);
        append_bytes(trailer.trailer_channel_wheel_lift_offset, out);
    }

    void append_bytes(const master_storage::channels_storage::truck_storage& truck, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::truck);
        out.reserve(packed_size);
        //reserve the packed size of the structure.
        append_bytes(truck.truck_channel_world_placement, out);
        append_bytes(truck.truck_channel_local_linear_velocity, out);
        append_bytes(truck.truck_channel_local_angular_velocity, out);
        append_bytes(truck.truck_channel_local_linear_acceleration, out);
        append_bytes(truck.truck_channel_local_angular_acceleration, out);
        append_bytes(truck.truck_channel_cabin_offset, out);
        append_bytes(truck.truck_channel_cabin_angular_velocity, out);
        append_bytes(truck.truck_channel_cabin_angular_acceleration, out);
        append_bytes(truck.truck_channel_head_offset, out);
        append_bytes(truck.truck_channel_speed, out);
        append_bytes(truck.truck_channel_engine_rpm, out);
        append_bytes(truck.truck_channel_engine_gear, out);
        append_bytes(truck.truck_channel_displayed_gear, out);
        append_bytes(truck.truck_channel_input_steering, out);
        append_bytes(truck.truck_channel_input_throttle, out);
        append_bytes(truck.truck_channel_input_brake, out);
        append_bytes(truck.truck_channel_input_clutch, out);
        append_bytes(truck.truck_channel_effective_steering, out);
        append_bytes(truck.truck_channel_effective_throttle, out);
        append_bytes(truck.truck_channel_effective_brake, out);
        append_bytes(truck.truck_channel_effective_clutch, out);
        append_bytes(truck.truck_channel_cruise_control, out);
        append_bytes(truck.truck_channel_hshifter_slot, out);
        append_bytes(truck.truck_channel_hshifter_selector, out);
        append_bytes(truck.truck_channel_parking_brake, out);
        append_bytes(truck.truck_channel_motor_brake, out);
        append_bytes(truck.truck_channel_retarder_level, out);
        append_bytes(truck.truck_channel_brake_air_pressure, out);
        append_bytes(truck.truck_channel_brake_air_pressure_warning, out);
        append_bytes(truck.truck_channel_brake_air_pressure_emergency, out);
        append_bytes(truck.truck_channel_brake_temperature, out);
        append_bytes(truck.truck_channel_fuel, out);
        append_bytes(truck.truck_channel_fuel_warning, out);
        append_bytes(truck.truck_channel_fuel_average_consumption, out);
        append_bytes(truck.truck_channel_fuel_range, out);
        append_bytes(truck.truck_channel_adblue, out);
        append_bytes(truck.truck_channel_adblue_warning, out);
        append_bytes(truck.truck_channel_oil_pressure, out);
        append_bytes(truck.truck_channel_oil_pressure_warning, out);
        append_bytes(truck.truck_channel_oil_temperature, out);
        append_bytes(truck.truck_channel_water_temperature, out);
        append_bytes(truck.truck_channel_water_temperature_warning, out);
        append_bytes(truck.truck_channel_battery_voltage, out);
        append_bytes(truck.truck_channel_battery_voltage_warning, out);
        append_bytes(truck.truck_channel_electric_enabled, out);
        append_bytes(truck.truck_channel_engine_enabled, out);
        append_bytes(truck.truck_channel_lblinker, out);
        append_bytes(truck.truck_channel_rblinker, out);
        append_bytes(truck.truck_channel_hazard_warning, out);
        append_bytes(truck.truck_channel_light_lblinker, out);
        append_bytes(truck.truck_channel_light_rblinker, out);
        append_bytes(truck.truck_channel_light_parking, out);
        append_bytes(truck.truck_channel_light_low_beam, out);
        append_bytes(truck.truck_channel_light_high_beam, out);
        append_bytes(truck.truck_channel_light_aux_front, out);
        append_bytes(truck.truck_channel_light_aux_roof, out);
        append_bytes(truck.truck_channel_light_beacon, out);
        append_bytes(truck.truck_channel_light_brake, out);
        append_bytes(truck.truck_channel_light_reverse, out);
        append_bytes(truck.truck_channel_wipers, out);
        append_bytes(truck.truck_channel_dashboard_backlight, out);
        append_bytes(truck.truck_channel_differential_lock, out);
        append_bytes(truck.truck_channel_lift_axle, out);
        append_bytes(truck.truck_channel_lift_axle_indicator, out);
        append_bytes(truck.truck_channel_trailer_lift_axle, out);
        append_bytes(truck.truck_channel_trailer_lift_axle_indicator, out);
        append_bytes(truck.truck_channel_wear_engine, out);
        append_bytes(truck.truck_channel_wear_transmission, out);
        append_bytes(truck.truck_channel_wear_cabin, out);
        append_bytes(truck.truck_channel_wear_chassis, out);
        append_bytes(truck.truck_channel_wear_wheels, out);
        append_bytes(truck.truck_channel_odometer, out);
        append_bytes(truck.truck_channel_navigation_distance, out);
        append_bytes(truck.truck_channel_navigation_time, out);
        append_bytes(truck.truck_channel_navigation_speed_limit, out);
        append_bytes(truck.truck_channel_wheel_susp_deflection, out);
        append_bytes(truck.truck_channel_wheel_on_ground, out);
        append_bytes(truck.truck_channel_wheel_substance, out);
        append_bytes(truck.truck_channel_wheel_velocity, out);
        append_bytes(truck.truck_channel_wheel_steering, out);
        append_bytes(truck.truck_channel_wheel_rotation, out);
        append_bytes(truck.truck_channel_wheel_lift, out);
        append_bytes(truck.truck_channel_wheel_lift_offset, out);
    }

    void append_bytes(const master_storage::channels_storage::general_storage& general, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::general);
        out.reserve(packed_size);
        //reserve the packed size of the structure.
        append_bytes(general.channel_paused, out);
        append_bytes(general.channel_local_scale, out);
        append_bytes(general.channel_game_time, out);
        append_bytes(general.channel_multiplayer_time_offset, out);
        append_bytes(general.channel_next_rest_stop, out);
        append_bytes(general.job_channel_cargo_damage, out);
    }

    void append_bytes(const master_storage::channels_storage& channels, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::channels);
        out.reserve(packed_size);
        //reserve the packed size of the structure.
        append_bytes(channels.general, out);
        append_bytes(channels.truck, out);
        append_bytes(channels.trailer, out);
    }

    void append_bytes(const master_storage::gameplay_storage& gameplay, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay);
        out.reserve(packed_size);
        append_bytes(gameplay.gameplay_job_cancelled_info, out);
        append_bytes(gameplay.gameplay_job_delivered_info, out);
        append_bytes(gameplay.gameplay_player_fined_info, out);
        append_bytes(gameplay.gameplay_player_tollgate_paid_info, out);
        append_bytes(gameplay.gameplay_player_use_ferry_info, out);
        append_bytes(gameplay.gameplay_player_use_train_info, out);
    }

    void append_bytes(const master_storage::configuration_storage& configuration, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration);
        out.reserve(packed_size);
        append_bytes(configuration.configuration_substances_info, out);
        append_bytes(configuration.configuration_controls_info, out);
        append_bytes(configuration.configuration_hshifter_info, out);
        append_bytes(configuration.configuration_truck_info, out);
        append_bytes(configuration.configuration_trailer_info, out);
        append_bytes(configuration.configuration_job_info, out);
    }

    void append_bytes(const master_storage& master, std::vector<uint8_t>& out) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::master);
        out.reserve(packed_size);
        append_bytes(master.configuration, out);
        append_bytes(master.gameplay, out);
        append_bytes(master.channels, out);
    }


    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_use_train_storage& gameplay_player_use_train_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_use_train_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::gameplay_player_use_train_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, gameplay_player_use_train_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_train_info.pay_amount, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_train_info.source_name, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_train_info.target_name, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_train_info.source_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_train_info.target_id, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_use_ferry_storage& gameplay_player_use_ferry_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_use_ferry_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::gameplay_player_use_ferry_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, gameplay_player_use_ferry_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_ferry_info.pay_amount, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_ferry_info.source_name, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_ferry_info.target_name, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_ferry_info.source_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_use_ferry_info.target_id, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_tollgate_paid_storage& gameplay_player_tollgate_paid_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_tollgate_paid_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::gameplay_player_tollgate_paid_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, gameplay_player_tollgate_paid_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_tollgate_paid_info.pay_amount, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_fined_storage& gameplay_player_fined_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_player_fined_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::gameplay_player_fined_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, gameplay_player_fined_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_fined_info.fine_offence, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_player_fined_info.fine_amount, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_job_delivered_storage& gameplay_job_delivered_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_job_delivered_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::gameplay_job_delivered_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.revenue, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.earned_xp, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.cargo_damage, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.distance_km, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.delivery_time, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.auto_park_used, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_delivered_info.auto_load_used, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_job_cancelled_storage& gameplay_job_cancelled_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay_job_cancelled_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::gameplay_job_cancelled_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, gameplay_job_cancelled_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay_job_cancelled_info.cancel_penalty, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_job_storage& configuration_job_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_job_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::configuration_job_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, configuration_job_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.cargo_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.cargo, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.cargo_mass, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.destination_city_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.cargo_unit_mass, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.cargo_unit_count, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.destination_city, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.source_city_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.source_city, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.destination_company_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.destination_company, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.source_company_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.source_company, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.income, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.delivery_time, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.is_cargo_loaded, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.job_market, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.special_job, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_job_info.planned_distance_km, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_trailer_storage& configuration_trailer_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_trailer_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::configuration_trailer_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, configuration_trailer_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.cargo_accessory_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.hook_position, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.brand_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.brand, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.name, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.chain_type, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.body_type, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.license_plate, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.license_plate_country, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.license_plate_country_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.wheel_count, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.wheel_position, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.wheel_steerable, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.wheel_simulated, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.wheel_radius, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.wheel_powered, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_trailer_info.wheel_liftable, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_truck_storage& configuration_truck_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_truck_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::configuration_truck_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, configuration_truck_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.brand_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.brand, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.name, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.fuel_capacity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.fuel_warning_factor, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.adblue_capacity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.adblue_warning_factor, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.air_pressure_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.air_pressure_emergency, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.oil_pressure_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.water_temperature_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.battery_voltage_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.rpm_limit, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.forward_gear_count, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.reverse_gear_count, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.differential_ratio, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.retarder_step_count, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.cabin_position, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.forward_ratio, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.reverse_ratio, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.head_position, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.hook_position, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.license_plate, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.license_plate_country, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.license_plate_country_id, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.wheel_count, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.wheel_position, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.wheel_steerable, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.wheel_simulated, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.wheel_radius, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.wheel_powered, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_truck_info.wheel_liftable, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_hshifter_storage& configuration_hshifter_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_hshifter_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::configuration_hshifter_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, configuration_hshifter_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_hshifter_info.selector_count, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_hshifter_info.slot_gear, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_hshifter_info.slot_handle_position, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_hshifter_info.slot_selectors, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_controls_storage& configuration_controls_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_controls_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::configuration_controls_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, configuration_controls_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_controls_info.shifter_type, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_substances_storage& configuration_substances_info, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration_substances_info);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::configuration_substances_info)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, configuration_substances_info.latest, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration_substances_info.id, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::trailer_storage& trailer, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::trailer);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::trailer)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, trailer.trailer_channel_connected, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_cargo_damage, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_world_placement, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_local_linear_velocity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_local_angular_velocity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_local_linear_acceleration, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_local_angular_acceleration, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wear_body, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wear_chassis, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wear_wheels, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_susp_deflection, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_on_ground, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_substance, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_velocity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_steering, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_rotation, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_lift, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, trailer.trailer_channel_wheel_lift_offset, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::truck_storage& truck, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::truck);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::truck)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, truck.truck_channel_world_placement, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_local_linear_velocity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_local_angular_velocity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_local_linear_acceleration, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_local_angular_acceleration, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_cabin_offset, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_cabin_angular_velocity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_cabin_angular_acceleration, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_head_offset, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_speed, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_engine_rpm, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_engine_gear, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_displayed_gear, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_input_steering, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_input_throttle, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_input_brake, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_input_clutch, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_effective_steering, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_effective_throttle, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_effective_brake, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_effective_clutch, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_cruise_control, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_hshifter_slot, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_hshifter_selector, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_parking_brake, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_motor_brake, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_retarder_level, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_brake_air_pressure, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_brake_air_pressure_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_brake_air_pressure_emergency, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_brake_temperature, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_fuel, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_fuel_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_fuel_average_consumption, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_fuel_range, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_adblue, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_adblue_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_oil_pressure, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_oil_pressure_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_oil_temperature, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_water_temperature, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_water_temperature_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_battery_voltage, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_battery_voltage_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_electric_enabled, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_engine_enabled, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_lblinker, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_rblinker, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_hazard_warning, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_lblinker, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_rblinker, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_parking, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_low_beam, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_high_beam, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_aux_front, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_aux_roof, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_beacon, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_brake, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_light_reverse, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wipers, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_dashboard_backlight, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_differential_lock, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_lift_axle, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_lift_axle_indicator, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_trailer_lift_axle, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_trailer_lift_axle_indicator, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wear_engine, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wear_transmission, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wear_cabin, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wear_chassis, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wear_wheels, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_odometer, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_navigation_distance, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_navigation_time, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_navigation_speed_limit, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_susp_deflection, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_on_ground, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_substance, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_velocity, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_steering, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_rotation, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_lift, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, truck.truck_channel_wheel_lift_offset, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::general_storage& general, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::general);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::general)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, general.channel_paused, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, general.channel_local_scale, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, general.channel_game_time, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, general.channel_multiplayer_time_offset, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, general.channel_next_rest_stop, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, general.job_channel_cargo_damage, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage& channels, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::channels);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::channels)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, channels.general, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, channels.truck, offset + read, single_read)) return false;
        read += single_read;
        for (uint32_t i = 0; i < SCS_TELEMETRY_trailers_count; i++){
            if (!from_bytes(as_bytes, channels.trailer[i], offset + read, single_read)) return false;
            read += single_read;
        }
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage& gameplay, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::gameplay);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::gameplay)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, gameplay.gameplay_job_cancelled_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay.gameplay_job_delivered_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay.gameplay_player_fined_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay.gameplay_player_tollgate_paid_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay.gameplay_player_use_ferry_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, gameplay.gameplay_player_use_train_info, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage& configuration, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::configuration);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::configuration)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, configuration.configuration_substances_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration.configuration_controls_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration.configuration_hshifter_info, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, configuration.configuration_truck_info, offset + read, single_read)) return false;
        read += single_read;
        for (uint32_t i = 0; i < SCS_TELEMETRY_trailers_count; i++){
            if (!from_bytes(as_bytes, configuration.configuration_trailer_info[i], offset + read, single_read)) return false;
            read += single_read;
        }
        if (!from_bytes(as_bytes, configuration.configuration_job_info, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage& master, const uint32_t offset, uint32_t& read) {
        constexpr const uint32_t& packed_size = metadata::packed_size_of(telemetry_id::master);
        if (as_bytes.size() - offset < metadata::packed_size_of(telemetry_id::master)) return false;
        read = 0;
        uint32_t single_read = 0;
        if (!from_bytes(as_bytes, master.configuration, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, master.gameplay, offset + read, single_read)) return false;
        read += single_read;
        if (!from_bytes(as_bytes, master.channels, offset + read, single_read)) return false;
        read += single_read;
        return true;
    }
}
