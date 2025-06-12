#include "connection.h"

using nstreamcom::collector_states;
using nstreamcom::as_collected_size;
using nstreamcom::encode_with_size;
using nstreamcom::nsize_int;
using std::string;

namespace truckconnect {
    namespace communication {
        constexpr const uint8_t require_connect = static_cast<uint8_t>(-1);

        connection::connection(const string& address)
            : socket(sockets::INVALID), addr({}), addr_len(sizeof(addr)), collector({}), pending_request(request::none), request_data({ require_connect })
        {
            addr.sin_family = AF_INET;
            if (address != "") {
                inet_pton(AF_INET, address.c_str(), &addr.sin_addr);
            }
            addr.sin_port = htons(PORT);
        }

        connection::operator const bool() const {
            return socket != sockets::INVALID;
        }

        communication_result connect(connection& connection) {
            if (connection.socket != sockets::INVALID && connection.request_data.byte != require_connect) {
                return communication_result::already_connected;
            }

            if (connection.socket == sockets::INVALID) {
                if ((connection.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == sockets::INVALID) {
                    return communication_result::generic_socket_error;
                }
            }

            if (::connect(connection.socket, reinterpret_cast<sockaddr*>(&connection.addr), connection.addr_len) == sockets::ERROR_RESULT) {
                return communication_result::generic_socket_error;
            }

            connection.pending_request = request::none;
            connection.request_data.request_telemetry_id = telemetry_id::invalid;
            return communication_result::success;
        }

        communication_result send_request_for(connection& connection, const telemetry_id& id) {
            if (connection.socket == sockets::INVALID) {
                return communication_result::not_connected;
            }

            const std::array<uint8_t, 2> request_data = form_telemetry_request(id);
            std::array<uint8_t, as_collected_size(static_cast<nsize_int>(request_data.size()))> encoded_request_data;
            encode_with_size(
                request_data.begin(),
                request_data.end(),
                static_cast<nsize_int>(request_data.size()),
                encoded_request_data.begin(),
                encoded_request_data.end()
            );

            if (send(connection.socket, reinterpret_cast<const char* const>(encoded_request_data.data()), static_cast<int>(encoded_request_data.size()), 0) == sockets::ERROR_RESULT) {
                return communication_result::generic_socket_error;
            }

            connection.pending_request = request::telemetry_id;
            connection.request_data.request_telemetry_id = id;
            return communication_result::success;
        }

        communication_result receive_one(connection& connection) {
            if (connection.socket == sockets::INVALID) {
                return communication_result::not_connected;
            }

            if (connection.pending_request == request::none) {
                return communication_result::no_pending_request;
            }

            uint8_t data;
            int received = recv(connection.socket, reinterpret_cast<char* const>(&data), 1, 0);

            if (received == 0) {
                return communication_result::disconnected;
            }

            if (received < 0) {
                return communication_result::generic_socket_error;
            }

            switch (connection.collector.dynamic_collect(data)) {
            case collector_states::COLLECTED:
                connection.pending_request = request::none;
                return communication_result::success;
            case collector_states::MISSING_SIZE:
            case collector_states::MISSING_DATA:
                connection.pending_request = request::none;
                return communication_result::collector_error;
            case collector_states::WAITING_SIZE:
            case collector_states::WAITING_DATA:
                return communication_result::incomplete;
            case collector_states::BUFFER_FULL:
            default:
                return communication_result::collector_error;
            }
        }

        communication_result receive_all(connection& connection, std::function<void(const std::vector<uint8_t>&)> received_callback) {
            communication_result result;
            do {
                result = receive_one(connection);
            } while (result == communication_result::incomplete);

            if (result == communication_result::success) {
                received_callback(connection.collector.buffer());
            }

            return result;
        }

        communication_result receive_for_request(connection& connection, const telemetry_id& id) {
            if (connection.socket == sockets::INVALID) {
                return communication_result::not_connected;
            }
            
            return communication_result::success;
        }

        communication_result disconnect(connection& connection) {
            if (connection.socket == sockets::INVALID) {
                return communication_result::not_connected;
            }

            if (closesocket(connection.socket) == sockets::ERROR_RESULT) {
                return communication_result::generic_socket_error;
            }
            
            connection.collector.reset_and_resize(connection.collector.minimum_size);
            connection.pending_request = request::none;
            connection.socket = sockets::INVALID;
            return communication_result::success;
        }
    }
}