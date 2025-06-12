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
        client.connection.pending_request = request::none;
    }
    
    if (client.connection.pending_request != request::none) {
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

    client.connection.pending_request = static_cast<communication::request>(client.connection.collector.buffer()[0]);
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

    if (client.connection.pending_request == request::none) {
        return true;
    }

    static vector<uint8_t> response = vector<uint8_t>(2);
    static vector<uint8_t> encoded_response;

    switch (client.connection.pending_request) {
    case request::telemetry_id: {
        response.resize(3);
        response[0] = client.connection.pending_request;
        apply_offset<telemetry_id>(response.data(), 1) = client.connection.request_data_telemetry_id();
        apply_offset<uint8_t>(response.data(), 2) = client.connection.request_data_trailer_index();

        const metadata::metadata_value& meta = metadata::metadata_value_of(client.connection.request_data_telemetry_id());
        debug_assert(meta.id != telemetry_id::invalid);

        const uint32_t& offset = metadata::master_offset_of(meta.id, client.connection.request_data_trailer_index());
        debug_assert(offset != metadata::INVALID_OFFSET);
        debug_assert(append_bytes(meta.id, &apply_offset<void*>(&current_master(), offset), response));

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
    default:
        console_log(SCS_LOG_TYPE_error, IDENTSTR(process_client), "Received unkown request " + to_string((int)client.connection.pending_request) + " from: " + to_string(client.connection.addr));
        break;
    }

    client.connection.pending_request = request::none;
    return true;
}
