#include "connection.h"

using std::string;

namespace truckconnect {
    namespace communication {
        connection::connection(const string& address)
            : socket(sockets::INVALID), addr({}), addr_len(sizeof(addr)), collector({})
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
            if (connection.socket != sockets::INVALID) {
                return communication_result::already_connected;
            }

            if ((connection.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == sockets::INVALID) {
                return communication_result::generic_socket_error;
            }

            if (::connect(connection.socket, reinterpret_cast<sockaddr*>(&connection.addr), connection.addr_len) == sockets::ERROR_RESULT) {
                return communication_result::generic_socket_error;
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
            
            connection.socket = sockets::INVALID;
            return communication_result::success;
        }
    }
}