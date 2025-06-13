#pragma once
#include "truckconnect_platform.h"
#include "vector_collector.h"
#include "telemetry_metadata.h"
#include "byte_converters.h"
#include <string>
#include <functional>

namespace truckconnect {
    namespace communication {
        constexpr const uint16_t PORT = 52878;
        
        using namespace platform;
        
        namespace request_types {
            enum request_type : uint8_t {
                none,
                telemetry_id
            };
        }

        using request_types::request_type;

        struct connection {
            sockets::socket socket;
            sockaddr_in addr;
            socklen_t addr_len;
            vector_collector collector;
            request_type pending_request;
            uint16_t request_data;

            static constexpr const uint32_t DATA_START = sizeof(pending_request) + sizeof(request_data);

            inline telemetry_id& request_data_telemetry_id() {
                return apply_offset<telemetry_id>(&request_data, 0);
            }

            inline uint8_t& request_data_trailer_index() {
                return apply_offset<uint8_t>(&request_data, 1);
            }

            inline void clear_pending_request() {
                pending_request = request_type::none;
            }

            connection(const std::string& address = "");

            operator const bool() const;
        };

        constexpr const uint32_t DATA_START = 2;

        namespace communication_results {
            enum communication_result {
                success,
                generic_socket_error,
                already_connected,
                not_connected,
                disconnected,
                incomplete,
                collector_error,
                no_pending_request,
                invalid_trailer_index,
                other_request_pending,
                other_telemetry_id_pending,
                other_trailer_index_request_pending,
                received_other_response,
                received_other_telemetry,
                received_other_trailer_index,
                unknown_data
            };
        }

        constexpr const std::array<uint8_t, 3> form_telemetry_request(const telemetry_id& id, const uint8_t trailer_index = 1) {
            return {
                request_type::telemetry_id,
                id,
                trailer_index
            };
        }

        using communication_results::communication_result;

        communication_result connect(connection& connection);

        communication_result send_request_for(connection& connection, const telemetry_id& id, const uint8_t& trailer_index = 0);

        communication_result receive_one(connection& connection);

        communication_result receive_all(connection& connection, std::function<void(const std::vector<uint8_t>&)> received_callback);

        static inline communication_result receive_all(connection& connection) {
            return receive_all(connection, [](const std::vector<uint8_t>&) {});
        }

        communication_result receive_for_request(connection& connection, const telemetry_id& id, std::function<void(const std::vector<uint8_t>&)> received_callback, const uint8_t& trailer_index = 0);

        static inline communication_result receive_for_request(connection& connection, const telemetry_id& id, const uint8_t& trailer_index = 0) {
            return receive_for_request(connection, id, [](const std::vector<uint8_t>&) {}, trailer_index);
        }

        communication_result disconnect(connection& connection);
    }
}
