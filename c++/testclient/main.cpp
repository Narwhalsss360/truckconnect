#include <truckconnect>
#include <iostream>

using std::cin;
using truckconnect::platform::debug_assert;
using truckconnect::communication::communication_result;
using truckconnect::communication::connection;
using truckconnect::communication::connect;
using truckconnect::communication::disconnect;

int main() {
    debug_assert(truckconnect::platform::sockets::initialize());
    communication_result result = communication_result::success;
    connection connection = ::connection("127.0.0.1");
    debug_assert((result = connect(connection)) == communication_result::success);
    cin.get();
    debug_assert((result = disconnect(connection)) == communication_result::success);
    debug_assert(truckconnect::platform::sockets::deinitialize());
    return 0;
}
