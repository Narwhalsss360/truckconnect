#include "clients.h"
#include <thread>
#include "process_client.h"

#define LISTENER_BACKLOG (2)

using std::to_string;
using std::thread;
using std::vector;
using namespace truckconnect::platform;
using namespace truckconnect::platform::event_signal;

sockets::socket listener = sockets::INVALID;
thread dispatcher;
volatile bool stop = false;
void dispatcher_start();
vector<client> clients;

void cleanup_listener() {
    if (listener == sockets::INVALID) {
        return;
    }

    if (closesocket(listener) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(cleanup_listener), "closesocket(listener) error: " + to_string(sockets::last_error()));
    }

    listener = sockets::INVALID;
}

bool clients_init() {
    if (!sockets::initialize()) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "Slatform sockets initialization failure.");
        return false;
    }

    listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listener == sockets::INVALID) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "socket(...) creation failure " + to_string(sockets::last_error()));
        return false;
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

    dispatcher = thread(dispatcher_start);
    stop = false;
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

        switch (wait(frame_end_signal())) {
            case signal_state::signaled:
                break;
            case signal_state::not_signaled:
                console_log(SCS_LOG_TYPE_warning, IDENTSTR(dispatcher_start), "Unexpected not_signaled result from wait(...) with no timeout.");
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

    for (client& client : clients) {
        if (closesocket(client.connection.socket) == sockets::ERROR_RESULT) {
            console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "closesocket(" + to_string(client.connection.addr) + ") error: " + to_string(sockets::last_error()));
        }
    }
    clients.clear();

    cleanup_listener();

    if (!sockets::deinitialize()) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "Sockets deinitialization error.");
    }
}
