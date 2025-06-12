#include "truckconnectextension.h"

struct client {
    truckconnect::communication::connection connection;
};

extern std::vector<client> clients;

namespace std {
	static string to_string(sockaddr_in& addr)
	{
		return
			to_string(addr.sin_addr.S_un.S_un_b.s_b1) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b2) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b3) + "." +
			to_string(addr.sin_addr.S_un.S_un_b.s_b4);
	}
}

bool clients_init();

void clients_deinit();
