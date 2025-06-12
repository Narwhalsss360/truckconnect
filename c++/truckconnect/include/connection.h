#pragma once
#include "truckconnect_platform.h"
#include "vector_collector.h"
#include <string>

namespace truckconnect {
    namespace communication {
        constexpr const uint16_t PORT = 52878;

        using namespace platform;

        struct connection {
            sockets::socket socket;
            sockaddr_in addr;
            socklen_t addr_len;
            vector_collector collector;

            connection(const std::string& address);

            operator const bool() const;
        };

        namespace communication_results {
            enum communication_result {
                success,
                generic_socket_error,
                already_connected,
                not_connected
            };
        }

        using communication_results::communication_result;

        communication_result connect(connection& connection);

        communication_result disconnect(connection& connection);
    }
}
