#pragma once
#include "truckconnect_platform.h"
#include "vector_collector.h"
#include "telemetry_metadata.h"
#include <string>
#include <functional>

namespace truckconnect {
    namespace communication {
        constexpr const uint16_t PORT = 52878;
        
        using namespace platform;
        
        namespace requests {
            enum request : uint8_t {
                none,
                telemetry_id
            };
        }

        using requests::request;

        struct connection {
            sockets::socket socket;
            sockaddr_in addr;
            socklen_t addr_len;
            vector_collector collector;
            request pending_request;
            union {
                uint8_t byte;
                telemetry_id request_telemetry_id;
            } request_data;
            static_assert(sizeof(request_data) == 1, "Messages must be exactly 2 bytes { request, data-identification }");

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
                no_pending_request
            };
        }

        constexpr const std::array<uint8_t, 2> form_telemetry_request(const telemetry_id& id) {
            return {
                request::telemetry_id,
                id
            };
        }

        using communication_results::communication_result;

        communication_result connect(connection& connection);

        communication_result send_request_for(connection& connection, const telemetry_id& id);

        communication_result receive_one(connection& connection);

        communication_result receive_all(connection& connection, std::function<void(const std::vector<uint8_t>&)> received_callback);

        static inline communication_result receive_all(connection& connection) {
            return receive_all(connection, [](const std::vector<uint8_t>&) {});
        }

        communication_result receive_for_request(connection& connection, const telemetry_id& id);

        communication_result disconnect(connection& connection);
    }
}
