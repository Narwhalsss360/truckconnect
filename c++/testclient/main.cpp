#include <truckconnect>
#include <iostream>

using std::cout;
using std::cin;
using truckconnect::platform::debug_assert;
using truckconnect::communication::communication_result;
using truckconnect::communication::connection;
using truckconnect::telemetry_id;
using truckconnect::communication::connect;
using truckconnect::communication::send_request_for;
using truckconnect::communication::receive_all;
using truckconnect::communication::disconnect;

truckconnect::platform::sockets::error_int dbg_sockets_last_error() {
    return truckconnect::platform::sockets::last_error();
}

int main() {
    debug_assert(truckconnect::platform::sockets::initialize());
    communication_result result = communication_result::success;
    connection connection = ::connection("127.0.0.1");
    debug_assert(communication_result::success == (result = connect(connection)));
    debug_assert(communication_result::success == (result = send_request_for(connection, telemetry_id::channel_game_time)));
    debug_assert(communication_result::success == (result = receive_all(connection)));
    cout << "Enter any character to disconnect.";
    cin.get();
    debug_assert(communication_result::success == (result = disconnect(connection)));
    debug_assert(truckconnect::platform::sockets::deinitialize());
    return 0;
}
