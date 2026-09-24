#pragma once
#include "truckconnectextension.h"
#include <ctime>

struct client {
    truckconnect::communication::connection connection;
	std::clock_t last_communication_time = std::clock_t();
};

extern std::vector<client> clients;

namespace std {
    static std::string to_string(const sockaddr_in& addr) {
        char buffer[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &(addr.sin_addr), buffer, sizeof(buffer)) != nullptr) {
            return std::string(buffer);
        }

        return "0.0.0.0";
    }
}

bool clients_init();

void clients_deinit();
