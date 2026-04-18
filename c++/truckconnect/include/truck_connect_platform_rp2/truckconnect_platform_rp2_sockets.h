#pragma once
#include <errno.h>
#include <lwip/sockets.h>
#include <lwip/netif.h>
#include <lwip/ip4_addr.h>

namespace truckconnect {
    namespace platform {
        namespace sockets {
            using error_int = int;

            using socket = int;

            constexpr const socket INVALID = -1;

            constexpr const int ERROR_RESULT = -1;

            static bool initialize() {
                return true;
            }

            static error_int last_error() {
                return errno;
            }

            static bool nonblocking(socket socket) {
                int fcntl_flags = fcntl(socket, F_GETFL, 0);
                if (fcntl_flags == -1) {
                    return false;
                }
                fcntl_flags |= O_NONBLOCK;
                return fcntl(socket, F_SETFL, fcntl_flags) != -1;
            }

            static bool set_reuseable_address(socket socket) {
                int true_int = 1;
                return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &true_int, sizeof(true_int)) != -1;
            }

            static bool shut_read(socket socket) {
                return shutdown(socket, SHUT_RD) != -1;
            }

            static bool shut_write(socket socket) {
                return shutdown(socket, SHUT_WR) != -1;
            }

            static error_int close_socket(socket socket, int linger_for = 4) {
                linger so_linger;
                so_linger.l_onoff = 1;
                so_linger.l_linger = linger_for;
                setsockopt(socket, SOL_SOCKET, SO_LINGER, &so_linger, sizeof(so_linger));
                return closesocket(socket);
            }

            static bool deinitialize() {
                return true;
            }

            namespace errors {
                constexpr const error_int SE_EWOULDBLOCK = EWOULDBLOCK;

                constexpr const error_int SE_EAGAIN = EAGAIN;

                constexpr const error_int SE_ECONNRESET = ECONNRESET;

                constexpr const error_int SE_EALREADY = EALREADY;

                constexpr const error_int SE_ECONNABORTED = ECONNABORTED;
            }
        }
    }
}
