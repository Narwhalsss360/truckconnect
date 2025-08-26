#include <cinttypes>
#include <iostream>
#include <thread>
#include <chrono>
#include <truckconnect>
#include <ctime>

constexpr const char* const IP = "127.0.0.1";

bool once(truckconnect::communication::connection& connection) {
    using std::cout;
    using std::endl;

    //The `truckconnect::metadata` namespace contains a bunch of types that have metadata information, they are static, and constexpr.
    //These may be used along with the API to avoid "foot-gun".
    using telemetry = truckconnect::metadata::truck_channel_speed;
    static_assert(telemetry::type == truckconnect::metadata::telemetry_type::channel, "Please use a channel telemetry for this sample.");

    //The `storage_type` type alias in all metadata structs is the type that is used to store the data for that telemetry.
    telemetry::storage_type storage;

    //Use the metadata type to avoid any foot-guns.
    truckconnect::communication::communication_result result = truckconnect::communication::request<telemetry>(connection, storage);

    if (result != truckconnect::communication::communication_result::success) {
        cout << "telemetry request<...>(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return false;
    }

    //Checking if the game is paused.
    truckconnect::value_storage<bool> paused; //or tuckconnect::metadata::channel_paused::storage_type
    result = truckconnect::communication::request(connection, truckconnect::telemetry_id::channel_paused);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "paused request<...>(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return false;
    }

    //Deserialize the buffer ourselves
    uint32_t read;
    if (!paused.from_bytes(connection.collector.buffer(), connection.TELEMETRY_DATA_START, read)) {
        //Deserialization error.
        return false;
    }

    //channel_paused is _always_ initialized as long it is properly deserialized.
    //When paused, data may be frozen since there are no telemetry updates.
    if (paused.value) {
        cout << "<paused>\n";
        return true;
    }

    if (!storage.initialized) {
        cout << "<uninitialized>\n";
    } else {
        //Please use a telemetry that is a primitve, or overload your own << operator.
        cout << storage.value << '\n';
    }

    return true;
}

int main() {
    using std::cout;
    using std::endl;
    using std::clock_t;
    using std::clock;
    using namespace std::chrono_literals;

    constexpr const clock_t RUN_FOR = 5 * 60 * 1000;

    //Setup & initialize sockets for this platform.
    if (!truckconnect::platform::sockets::initialize()) {
        cout << "Platform sockets initialization error" << endl;
        return 1;
    }

    truckconnect::communication::connection connection = truckconnect::communication::connection(IP);

    truckconnect::communication::communication_result result = truckconnect::communication::connect(connection);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "connect(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    truckconnect::version_t version;
    result = truckconnect::communication::get_version(connection, version);

    if (result != truckconnect::communication::communication_result::success) {
        cout << "get_version(...) failure code : " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    if (version.major != truckconnect::version.major || version.minor != truckconnect::version.minor) {
        cout << "Version mismatch, client:" << std::to_string(truckconnect::version) << ", server:" << std::to_string(version) << endl;
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
