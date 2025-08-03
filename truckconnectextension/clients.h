#pragma once
#include "truckconnectextension.h"

struct client {
    truckconnect::communication::connection connection;
};

extern std::vector<client> clients;

namespace std {
	static string to_string(sockaddr_in& addr)
	{
        const uint8_t (&bytes)[4] = *reinterpret_cast<uint8_t(*)[4]>(&addr);
		return
			to_string(bytes[0]) + "." +
			to_string(bytes[1]) + "." +
			to_string(bytes[2]) + "." +
			to_string(bytes[3]);
	}
}

bool clients_init();

void clients_deinit();
