#include <thread>
#include <truck_connect_platform_win/truckconnect_platform_win_event_signal.h>
#include "clients.h"
#include "process_client.h"
#include "truckconnectextension.h"

#define LISTENER_BACKLOG (2)

using std::to_string;
using std::thread;
using std::vector;
using namespace truckconnect::platform;
using namespace truckconnect::platform::event_signal;

sockets::socket listener = sockets::INVALID;
thread dispatcher;
volatile bool stop = false;
const timeout_int& dispatcher_timeout = 500;
void dispatcher_start();
vector<client> clients;

void cleanup_listener() {
    if (listener == sockets::INVALID) {
        return;
    }

    if (sockets::close_socket(listener) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(cleanup_listener), "close_socket(listener) error: " + to_string(sockets::last_error()));
    }

    listener = sockets::INVALID;
}

bool clients_init() {
    if (!sockets::initialize()) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "Platform sockets initialization failure.");
        return false;
    }

    listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listener == sockets::INVALID) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "socket(...) creation failure " + to_string(sockets::last_error()));
        return false;
    }

    if (!sockets::set_reuseable_address(listener)) {
        console_log(SCS_LOG_TYPE_warning, IDENTSTR(clients_init), "set_reusable_address(...) failure " + to_string(sockets::last_error()) + ", binding may fail.");
    }

    sockaddr_in all;
    all.sin_family = AF_INET;
    *reinterpret_cast<uint32_t* const>(&all.sin_addr) = 0;
    all.sin_port = htons(truckconnect::communication::PORT);

    if (bind(listener, reinterpret_cast<sockaddr* const>(&all), sizeof(all)) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "bind(...) failure " + to_string(sockets::last_error()));
        cleanup_listener();
        return false;
    }

    if (!sockets::nonblocking(listener)) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "nonblocking(...) failure " + to_string(sockets::last_error()));
        cleanup_listener();
        return false;
    }

    if (listen(listener, LISTENER_BACKLOG) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "listen(...) failure " + to_string(sockets::last_error()));
        cleanup_listener();
        return false;
    }

    stop = false;
    dispatcher = thread(dispatcher_start);
    return true;
}

void dispatcher_start() {
    do {
        client new_client;
        if ((new_client.connection.socket = accept(listener, reinterpret_cast<sockaddr*>(&new_client.connection.addr), &new_client.connection.addr_len)) == sockets::ERROR_RESULT) {
            if (sockets::last_error() != sockets::errors::SE_EWOULDBLOCK) {
                console_log(SCS_LOG_TYPE_error, IDENTSTR(dispatcher_start), "accept(...) error: " + to_string(sockets::last_error()));
            }
        } else {
            clients.push_back(new_client);
            console_log(SCS_LOG_TYPE_message, to_string(new_client.connection.addr) + " connected.");
        }

        for (uint32_t i = 0; i < clients.size(); i++) {
            if (!process_client(clients[i])) {
                console_log(SCS_LOG_TYPE_message, IDENTSTR(dispatcher_start), "Client " + to_string(clients[i].connection.addr) + " disconncted.");
                clients.erase(clients.begin() + i);
            }
        }

        timeout_int timeout;
        if (current_master().channels.general.channel_paused.value || !current_master().channels.general.channel_paused.initialized) {
            timeout = dispatcher_timeout;
        } else {
            timeout = event_signal::NO_TIMEOUT;
        }

        switch (wait(frame_end_signal(), timeout)) {
            case signal_state::signaled:
                break;
            case signal_state::not_signaled:
                // console_log(SCS_LOG_TYPE_warning, IDENTSTR(dispatcher_start), "Unexpected not_signaled result from wait(...) with no timeout.");
                break;
            case signal_state::error:
                console_log(SCS_LOG_TYPE_error, IDENTSTR(dispatcher_start), "Signal wait(...) error: " + to_string(event_signal::last_error()));
                break;
            default:
                break;
        }
    } while (!stop);
}

void clients_deinit() {
    stop = true;
    if (dispatcher.joinable()) {
        if (!set(frame_end_signal())) {
            console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "Signal set(...) error: " + to_string(event_signal::last_error()) + " game thread may block!");
        }
        dispatcher.join();
    }

    cleanup_listener();
    for (client& client : clients) {
        if (!sockets::shut_write(client.connection.socket)) {
            console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "shut_write(" + to_string(client.connection.addr) + ") critical error " + to_string(sockets::last_error()) + ", potentially leaking socket.");
        }

        int recv_read;
        char discard_buffer[64];
        do {
            recv_read = recv(client.connection.socket, discard_buffer, sizeof(discard_buffer), 0);
        } while (recv_read > 0);

        if (!sockets::shut_read(client.connection.socket)) {
            console_log(SCS_LOG_TYPE_warning, IDENTSTR(clients_deinit), "shut_read(" + to_string(client.connection.addr) + ") error " + to_string(sockets::last_error()) + ", socket closed incorrectly.");
        }

        if (sockets::close_socket(client.connection.socket) == sockets::ERROR_RESULT) {
            console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "close_socket(" + to_string(client.connection.addr) + ") error " + to_string(sockets::last_error()) + ", socket closed incorrectly.");
        }

        client.connection.socket = sockets::INVALID;
    }

    clients.clear();

    if (!sockets::deinitialize()) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "Sockets deinitialization error.");
    }
}
