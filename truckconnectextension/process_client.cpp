#include "process_client.h"

using std::vector;
using std::to_string;
using nstreamcom::collector_states;
using nstreamcom::nsize_int;
using nstreamcom::as_collected_size;
using nstreamcom::encode_with_size;
using namespace truckconnect;
using namespace truckconnect::platform;
using namespace truckconnect::communication;

void cleanup_client(client& client) {
    if (closesocket(client.connection.socket) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(cleanup_client), "closesocket(" + to_string(client.connection.addr) + ") critical error " + to_string(sockets::last_error()) + ", potentially leaking socket.");
    }
    client.connection.socket = sockets::INVALID;
}

bool read_new_pending_request(client& client) {
    if (
        client.connection.collector.state() == collector_states::MISSING_SIZE ||
        client.connection.collector.state() == collector_states::MISSING_DATA
    ) {
        client.connection.pending_request = request_type::none;
    }
    
    if (client.connection.pending_request != request_type::none) {
        return true;
    }

    do {
        uint8_t data;
        int received = recv(client.connection.socket, reinterpret_cast<char* const>(&data), 1, 0);

        if (received == 0) {
            return false;
        }

        if (received < 0) {
            if (sockets::last_error() == sockets::errors::SE_EWOULDBLOCK) {
                return true;
            }

            if (sockets::last_error() != 0) {
                console_log(SCS_LOG_TYPE_error, IDENTSTR(read_new_pending_request), "recv(" + to_string(client.connection.addr) + ") error: " + to_string(sockets::last_error()));
            }
            cleanup_client(client);
            return false;
        }

        client.connection.collector.dynamic_collect(data);
    } while (client.connection.collector.state() == collector_states::WAITING_SIZE || client.connection.collector.state() == collector_states::WAITING_DATA);

    if (client.connection.collector.state() != collector_states::COLLECTED) {
        return true;
    }

    if (client.connection.collector.next_size() == 0) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(read_new_pending_request), "Collected 0 bytes of data. Unknown request.");
        return true;
    }

    client.connection.pending_request = static_cast<communication::request_type>(client.connection.collector.buffer()[0]);
    client.connection.request_data = apply_offset<uint16_t>(client.connection.collector.buffer().data(), 1);
    return true;
}

bool send_catch_fail(client& client, const uint8_t* const data, const uint32_t& size) {
    if (send(client.connection.socket, reinterpret_cast<const char* const>(data), static_cast<int>(size), 0) == sockets::ERROR_RESULT) {
        if (sockets::last_error() != sockets::errors::SE_EWOULDBLOCK) {
            console_log(SCS_LOG_TYPE_error, IDENTSTR(send_catch_fail), "send(" + to_string(client.connection.addr) + ") error: " + to_string(sockets::last_error()));
        }
        cleanup_client(client);
    }
    return true;
}

bool process_client(client& client) {
    if (!read_new_pending_request(client)) {
        return false;
    }

    if (client.connection.pending_request == request_type::none) {
        return true;
    }

    static vector<uint8_t> response = vector<uint8_t>(3);
    static vector<uint8_t> encoded_response;

    switch (client.connection.pending_request) {
    case request_type::telemetry_id: {
        response.resize(3);
        response[0] = client.connection.pending_request;
        apply_offset<telemetry_id>(response.data(), 1) = client.connection.request_data_telemetry_id();
        apply_offset<trailer_index_or_count>(response.data(), 2) = client.connection.request_data_trailer_index_or_count();
        const trailer_index_or_count& trailer_index_or_count = client.connection.request_data_trailer_index_or_count();

        const metadata::metadata_value& meta = metadata::metadata_value_of(client.connection.request_data_telemetry_id());
        debug_assert(meta.id != telemetry_id::invalid);

        if (meta.trailer_channel && trailer_index_or_count.is_count) {
            for (uint8_t i = 0; i < trailer_index_or_count.index_or_count; i++) {
                const uint32_t& offset = metadata::master_offset_of(meta.id, i);
                debug_assert(offset != metadata::INVALID_OFFSET);
                debug_assert(append_bytes(meta.id, &apply_offset<void*>(&current_master(), offset), response));
            }
        } else {
            const uint32_t& offset = metadata::master_offset_of(meta.id, trailer_index_or_count.index_or_count);
            debug_assert(offset != metadata::INVALID_OFFSET);
            debug_assert(append_bytes(meta.id, &apply_offset<void*>(&current_master(), offset), response));
        }

        encoded_response.resize(as_collected_size(static_cast<uint32_t>(response.size())));
        encode_with_size(
            response.begin(),
            response.end(),
            static_cast<nsize_int>(response.size()),
            encoded_response.begin(),
            encoded_response.end()
        );

        if (!send_catch_fail(client, encoded_response.data(), static_cast<uint32_t>(encoded_response.size()))) {
            return false;
        }
        break;
    }
    case request_type::register_data_definition: {
        const data::data_definition_id& id = client.connection.requst_data_data_definition_id();
        debug_assert(std::find_if(
                client.connection.data_definitions.begin(),
                client.connection.data_definitions.end(),
                [&id](const data::data_definition_value& definition) { return definition.id == id; }
            ) == client.connection.data_definitions.end()
        );
        debug_assert((client.connection.collector.next_size() - connection::DATA_DEFINITION_DATA_START) % data::data_member_serialization_info::packed_size == 0);

        const uint32_t count = (client.connection.collector.next_size() - connection::DATA_DEFINITION_DATA_START) / data::data_member_serialization_info::packed_size;
        client.connection.data_definitions.emplace_back(client.connection.requst_data_data_definition_id());
        data::data_definition_value& definition = client.connection.data_definitions.back();
        
        definition.members.resize(count);
        for (uint32_t i = 0; i < count; i++) {
            const uint32_t offset = connection::DATA_DEFINITION_DATA_START + i * data::data_member_serialization_info::packed_size;
            data::from_bytes(client.connection.collector.buffer(), definition.members[i], offset);
        }

        response.resize(2);
        response[0] = request_type::register_data_definition;
        response[1] = definition.id;
        encoded_response.resize(as_collected_size(static_cast<uint32_t>(response.size())));
        encode_with_size(
            response.begin(),
            response.end(),
            static_cast<nsize_int>(response.size()),
            encoded_response.begin(),
            encoded_response.end()
        );

        if (!send_catch_fail(client, encoded_response.data(), static_cast<uint32_t>(encoded_response.size()))) {
            return false;
        }
        break;
    }
    case request_type::defined_data: {
        const data::data_definition_id& id = client.connection.requst_data_data_definition_id();
        const auto find_it = std::find_if(
            client.connection.data_definitions.begin(),
            client.connection.data_definitions.end(),
            [&id](const data::data_definition_value& definition) { return definition.id == id; }
        );
        debug_assert(find_it != client.connection.data_definitions.end());

        response.resize(2);
        response[0] = request_type::defined_data;
        response[1] = id;

        for (const data::data_member& member : find_it->members) {
            const trailer_index_or_count& trailer_count = member.trailer_count;

            const metadata::metadata_value& meta = metadata::metadata_value_of(member.telemetry_id);
            debug_assert(meta.id != telemetry_id::invalid);

            if (meta.trailer_channel) {
                debug_assert(member.trailer_count <= SCS_TELEMETRY_trailers_count);
                for (uint8_t i = 0; i < member.trailer_count; i++) {
                    const uint32_t& offset = metadata::master_offset_of(meta.id, i);
                    debug_assert(offset != metadata::INVALID_OFFSET);
                    debug_assert(append_bytes(meta.id, &apply_offset<void*>(&current_master(), offset), response));
                }
            } else {
                const uint32_t& offset = metadata::master_offset_of(meta.id);
                debug_assert(offset != metadata::INVALID_OFFSET);
                debug_assert(append_bytes(meta.id, &apply_offset<void*>(&current_master(), offset), response));
            }
        }

        encoded_response.resize(as_collected_size(static_cast<uint32_t>(response.size())));
        encode_with_size(
            response.begin(),
            response.end(),
            static_cast<nsize_int>(response.size()),
            encoded_response.begin(),
            encoded_response.end()
        );

        if (!send_catch_fail(client, encoded_response.data(), static_cast<uint32_t>(encoded_response.size()))) {
            return false;
        }
        break;
    }
    case request_type::unregister_data_definition: {
        const data::data_definition_id& id = client.connection.requst_data_data_definition_id();
        const auto find_it = std::find_if(
            client.connection.data_definitions.begin(),
            client.connection.data_definitions.end(),
            [&id](const data::data_definition_value& definition) { return definition.id == id; }
        );
        debug_assert(find_it != client.connection.data_definitions.end());

        client.connection.data_definitions.erase(find_it);
        response.resize(2);
        response[0] = request_type::unregister_data_definition;
        response[1] = id;
        encoded_response.resize(as_collected_size(static_cast<uint32_t>(response.size())));
        encode_with_size(
            response.begin(),
            response.end(),
            static_cast<nsize_int>(response.size()),
            encoded_response.begin(),
            encoded_response.end()
        );

        if (!send_catch_fail(client, encoded_response.data(), static_cast<uint32_t>(encoded_response.size()))) {
            return false;
        }
    }
    default:
        console_log(SCS_LOG_TYPE_error, IDENTSTR(process_client), "Received unkown request " + to_string((int)client.connection.pending_request) + " from: " + to_string(client.connection.addr));
        break;
    }

    client.connection.pending_request = request_type::none;
    return true;
}
