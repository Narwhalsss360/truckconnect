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

            static bool set_reuseable_address(socket socket) {
                int true_int = 1;
                return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&true_int, sizeof(true_int)) != -1;
            }

            static bool shut_read(socket socket) {
                return shutdown(socket, SD_RECEIVE) != -1;
            }

            static bool shut_write(socket socket) {
                return shutdown(socket, SD_SEND) != -1;
            }

            static error_int close_socket(socket socket, int linger_for = 4) {
                linger so_linger;
                so_linger.l_onoff = 1;
                so_linger.l_linger = linger_for;
                setsockopt(socket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));
                return closesocket(socket);
            }

            static bool deinitialize() {
                return WSACleanup() == 0;
            }

            namespace errors {
                constexpr const error_int SE_EWOULDBLOCK = WSAEWOULDBLOCK;

                constexpr const error_int SE_EAGAIN = EAGAIN;

                constexpr const error_int SE_ECONNRESET = WSAECONNRESET;

                constexpr const error_int SE_EALREADY = WSAEALREADY;

                constexpr const error_int SE_ECONNABORTED = WSAECONNABORTED;
            }
        }
    }
}
