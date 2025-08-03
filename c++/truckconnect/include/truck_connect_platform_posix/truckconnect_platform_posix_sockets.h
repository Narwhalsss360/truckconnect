#pragma once
#include "truckconnect_platform_posix.h"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cerrno>

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

            static error_int close_socket(socket socket) {
                return close(socket);
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
