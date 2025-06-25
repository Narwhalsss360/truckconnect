/*
* Please see other samples for an explanation of uncommented operations.
* This sample show how you would implement a *cooperative* asynchronous operation.
*/

#include <truckconnect>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

constexpr const char* const IP = "127.0.0.1";

bool once(truckconnect::communication::connection& connection) {
    using std::cout;
    using std::endl;
    using std::clock;
    using std::to_string;
    using std::clock_t;
    using master_telemetry = truckconnect::metadata::master;
    using truckconnect::communication::communication_result;
    using truckconnect::from_bytes;
    using truckconnect::platform::sockets::errors::SE_EWOULDBLOCK;
    using truckconnect::platform::sockets::last_error;

    //Using static to not cause a stack overflow.
    static master_telemetry::storage_type master;

    communication_result result = truckconnect::communication::send_request_for(connection, master_telemetry::id);
    if (result != communication_result::success) {
        cout << "send_request_for(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return false;
    }

    clock_t start = clock();
    do {
        result = receive_one(connection);
        if (
            result == communication_result::generic_socket_error &&
            last_error() == SE_EWOULDBLOCK
        ) {
            //yeild to other work...

            //This line is so that the condition in while () expression evaluates to true.
            result = communication_result::incomplete;
            continue;
        }
    } while (result == communication_result::incomplete);

    if (result != truckconnect::communication::communication_result::success) {
        cout << "receive_one(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return false;
    }
    connection.clear_pending_request();

    if (!from_bytes(connection.collector.buffer(), master, connection.TELEMETRY_DATA_START)) {
        cout << "from_bytes(...) failure" << endl;
        return false;
    }

    cout <<
        "Did work for " << clock() - start << "ms|" <<
        (master.channels.truck.truck_channel_speed.initialized ? to_string(master.channels.truck.truck_channel_speed.value) : "---") <<
        "m/s\n";
    return true;
}

int main() {
    using std::cout;
    using std::clock;
    using std::clock_t;
    using std::this_thread::sleep_for;
    using std::endl;
    using namespace std::chrono_literals;

    constexpr const clock_t RUN_FOR = 5 * 60 * 1000;

    if (!truckconnect::platform::sockets::initialize()) {
        cout << "Platform sockets initialization error" << endl;
        return 1;
    }

    truckconnect::communication::connection connection = truckconnect::communication::connection(IP);

    //non-blocking connect not implemented... :(
    truckconnect::communication::communication_result result = truckconnect::communication::connect(connection);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "connect(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    if (!truckconnect::platform::sockets::nonblocking(connection.socket)) {
        cout << "nonblocking(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    clock_t start_time = clock();
    do {
        if (!once(connection)) {
            break;
        }
    } while (clock() - start_time < RUN_FOR);

    result = truckconnect::communication::disconnect(connection);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "disconnect(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    if (!truckconnect::platform::sockets::deinitialize()) {
        cout << "Platform sockets deinitialization error" << endl;
        return 1;
    }
	return 0;
}
