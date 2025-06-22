#pragma once
#include "master_structure.h"
#include "telemetry_metadata.h"

namespace truckconnect {
    template <typename T>
    T& apply_offset(void* const start, const size_t& offset) {
        return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(start) + offset);
    }

    template <typename T>
    const T& apply_offset(const void* const start, const size_t& offset) {
        return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t* const>(start) + offset);
    }

    void append_bytes(const master_storage::gameplay_storage::gameplay_player_use_train_storage& gameplay_player_use_train_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::gameplay_storage::gameplay_player_use_ferry_storage& gameplay_player_use_ferry_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::gameplay_storage::gameplay_player_tollgate_paid_storage& gameplay_player_tollgate_paid_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::gameplay_storage::gameplay_player_fined_storage& gameplay_player_fined_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::gameplay_storage::gameplay_job_delivered_storage& gameplay_job_delivered_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::gameplay_storage::gameplay_job_cancelled_storage& gameplay_job_cancelled_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::configuration_storage::configuration_job_storage& configuration_job_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::configuration_storage::configuration_trailer_storage& configuration_trailer_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::configuration_storage::configuration_truck_storage& configuration_truck_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::configuration_storage::configuration_hshifter_storage& configuration_hshifter_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::configuration_storage::configuration_controls_storage& configuration_controls_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::configuration_storage::configuration_substances_storage& configuration_substances_info, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::channels_storage::trailer_storage& trailer, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::channels_storage::truck_storage& truck, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::channels_storage::general_storage& general, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::channels_storage& channels, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::gameplay_storage& gameplay, std::vector<uint8_t>& out);

    void append_bytes(const master_storage::configuration_storage& configuration, std::vector<uint8_t>& out);

    void append_bytes(const master_storage& master, std::vector<uint8_t>& out);

    bool append_bytes(const telemetry_id& id, const void* const data, std::vector<uint8_t>& out);
    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_use_train_storage& gameplay_player_use_train_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_use_train_storage& gameplay_player_use_train_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, gameplay_player_use_train_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_use_ferry_storage& gameplay_player_use_ferry_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_use_ferry_storage& gameplay_player_use_ferry_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, gameplay_player_use_ferry_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_tollgate_paid_storage& gameplay_player_tollgate_paid_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_tollgate_paid_storage& gameplay_player_tollgate_paid_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, gameplay_player_tollgate_paid_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_fined_storage& gameplay_player_fined_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_player_fined_storage& gameplay_player_fined_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, gameplay_player_fined_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_job_delivered_storage& gameplay_job_delivered_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_job_delivered_storage& gameplay_job_delivered_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, gameplay_job_delivered_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_job_cancelled_storage& gameplay_job_cancelled_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage::gameplay_job_cancelled_storage& gameplay_job_cancelled_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, gameplay_job_cancelled_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_job_storage& configuration_job_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_job_storage& configuration_job_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, configuration_job_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_trailer_storage& configuration_trailer_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_trailer_storage& configuration_trailer_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, configuration_trailer_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_truck_storage& configuration_truck_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_truck_storage& configuration_truck_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, configuration_truck_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_hshifter_storage& configuration_hshifter_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_hshifter_storage& configuration_hshifter_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, configuration_hshifter_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_controls_storage& configuration_controls_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_controls_storage& configuration_controls_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, configuration_controls_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_substances_storage& configuration_substances_info, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage::configuration_substances_storage& configuration_substances_info, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, configuration_substances_info, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::trailer_storage& trailer, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::trailer_storage& trailer, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, trailer, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::truck_storage& truck, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::truck_storage& truck, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, truck, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::general_storage& general, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage::general_storage& general, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, general, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage& channels, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::channels_storage& channels, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, channels, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage& gameplay, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::gameplay_storage& gameplay, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, gameplay, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage& configuration, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage::configuration_storage& configuration, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, configuration, offset, read); }

    bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage& master, const uint32_t offset, uint32_t& read);

    static bool from_bytes(const std::vector<uint8_t>& as_bytes, master_storage& master, const uint32_t offset = 0) { uint32_t read; return from_bytes(as_bytes, master, offset, read); }

    bool from_bytes(const telemetry_id& id, const std::vector<uint8_t>& as_bytes, void* const out, const uint32_t& offset, uint32_t& read);
}
