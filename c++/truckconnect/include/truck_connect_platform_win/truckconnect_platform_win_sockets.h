#pragma once
#include "truckconnect_platform_win.h"

namespace truckconnect {
    namespace platform {
        namespace sockets {
            using error_int = int;

            using socket = SOCKET;

            constexpr const socket INVALID = INVALID_SOCKET;

            constexpr const int ERROR_RESULT = SOCKET_ERROR;

            static bool initialize() {
                WSADATA data;
                return WSAStartup(MAKEWORD(2, 2), &data) == 0;
            }
            
            static error_int last_error() {
                return WSAGetLastError();
            }

            static bool nonblocking(socket socket) {
                u_long mode = 1;
                return ioctlsocket(socket, FIONBIO, &mode) != ERROR_RESULT;
            }
            
            static bool deinitialize() {
                return WSACleanup() == 0;
            }

            namespace errors {
                constexpr const error_int SE_EWOULDBLOCK = WSAEWOULDBLOCK;
                
                constexpr const error_int SE_EAGAIN = EAGAIN;

                constexpr const error_int SE_ECONNRESET = WSAECONNRESET;

                constexpr const error_int SE_EALREADY = WSAEALREADY;
            }
        }
    }
}
