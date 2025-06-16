#include <master_structure.h>

namespace truckconnect {
    const uint32_t memory_usage(const master_storage& master) {
        uint32_t usage = 0;
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_vector_storage<std::string>);
        for (uint32_t i = 0; i < master.configuration.configuration_substances_info.id.values.size(); i++) {
            usage += static_cast<uint32_t>(master.configuration.configuration_substances_info.id.values[i].size() + 1);
        }

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_controls_info.shifter_type.value.size() + 1);

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_vector_storage<int32_t>);
        usage += static_cast<uint32_t>(master.configuration.configuration_hshifter_info.slot_gear.values.size() * sizeof(int32_t));
        usage += sizeof(value_vector_storage<uint32_t>);
        usage += static_cast<uint32_t>(master.configuration.configuration_hshifter_info.slot_handle_position.values.size() * sizeof(uint32_t));
        usage += sizeof(value_vector_storage<uint32_t>);
        usage += static_cast<uint32_t>(master.configuration.configuration_hshifter_info.slot_selectors.values.size() * sizeof(uint32_t));

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.brand_id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.brand.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.name.value.size() + 1);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<scs_value_fvector_t>);
        usage += sizeof(value_vector_storage<float>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.forward_ratio.values.size() * sizeof(float));
        usage += sizeof(value_vector_storage<float>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.reverse_ratio.values.size() * sizeof(float));
        usage += sizeof(value_storage<scs_value_fvector_t>);
        usage += sizeof(value_storage<scs_value_fvector_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.license_plate.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.license_plate_country.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.license_plate_country_id.value.size() + 1);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_vector_storage<scs_value_fvector_t>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.wheel_position.values.size() * sizeof(scs_value_fvector_t));
        usage += sizeof(value_vector_storage<bool>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.wheel_steerable.values.size() * sizeof(bool));
        usage += sizeof(value_vector_storage<bool>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.wheel_simulated.values.size() * sizeof(bool));
        usage += sizeof(value_vector_storage<float>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.wheel_radius.values.size() * sizeof(float));
        usage += sizeof(value_vector_storage<bool>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.wheel_powered.values.size() * sizeof(bool));
        usage += sizeof(value_vector_storage<bool>);
        usage += static_cast<uint32_t>(master.configuration.configuration_truck_info.wheel_liftable.values.size() * sizeof(bool));


        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.cargo_id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.cargo.value.size() + 1);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.destination_city_id.value.size() + 1);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.destination_city.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.source_city_id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.source_city.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.destination_company_id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.destination_company.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.source_company_id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.source_company.value.size() + 1);
        usage += sizeof(value_storage<uint64_t>);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<bool>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.configuration.configuration_job_info.job_market.value.size() + 1);
        usage += sizeof(value_storage<bool>);
        usage += sizeof(value_storage<uint32_t>);


        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<int64_t>);

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<int64_t>);
        usage += sizeof(value_storage<int32_t>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<float>);
        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<bool>);
        usage += sizeof(value_storage<bool>);

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_fined_info.fine_offence.value.size() + 1);
        usage += sizeof(value_storage<int64_t>);

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<int64_t>);

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<int64_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_ferry_info.source_name.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_ferry_info.target_name.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_ferry_info.source_id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_ferry_info.target_id.value.size() + 1);

        usage += sizeof(value_storage<uint32_t>);
        usage += sizeof(value_storage<int64_t>);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_train_info.source_name.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_train_info.target_name.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_train_info.source_id.value.size() + 1);
        usage += sizeof(value_storage<std::string>);
        usage += static_cast<uint32_t>(master.gameplay.gameplay_player_use_train_info.target_id.value.size() + 1);


        usage += sizeof(master_storage::channels_storage);
        return usage;
    }
}

