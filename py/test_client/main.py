from sys import stderr
from time import time, sleep
from truckconnect.connection import Connection
from scssdk_truckconnect.truckconnect import Version, VERSION
from truckconnect.telemetry_id import TelemetryID
from truckconnect.value_storage import SCSValueType, value_storage_from_bytes, is_value_storage


RUN_FOR_SEC: float = 5 * 60


def update(connection: Connection) -> None:
    connection.send_request_for(TelemetryID.ChannelPaused)
    connection.receive_for_request(TelemetryID.ChannelPaused)
    paused_deserialized, _ = value_storage_from_bytes(
        SCSValueType.SCS_VALUE_TYPE_bool,
        connection.collector.bytearray,
        Connection.TELEMETRY_DATA_START
    )
    assert is_value_storage(paused_deserialized, bool)
    _, paused = paused_deserialized


    if paused:
        print("<paused>")
    else:
        connection.send_request_for(TelemetryID.TruckChannelSpeed)
        connection.receive_for_request(TelemetryID.TruckChannelSpeed)
        speed_deserialized, _ = value_storage_from_bytes(
            SCSValueType.SCS_VALUE_TYPE_float,
            connection.collector.bytearray,
            Connection.TELEMETRY_DATA_START
        )
        assert is_value_storage(speed_deserialized, float)
        speed_initialized, speed = speed_deserialized
        print(f"{f"{speed:0.2f}" if speed_initialized else "---"} m/s")



def main(connection: Connection) -> None:
    version: Version = connection.get_version()
    print(f"Server: {version}, Client: {VERSION}")
    if version.major != VERSION.major or version.minor != VERSION.minor:
        print("Version mismatch", file=stderr)
        return
    if version.patch < VERSION.patch:
        print("out-patched server", file=stderr)

    start = time()
    while time() - start <= RUN_FOR_SEC:
        try:
            update(connection)
        except KeyboardInterrupt:
            print("^C", file=stderr)
            break
        sleep(0.1)


if __name__ == "__main__":
    try:
        with Connection() as connection:
            main(connection)
    except KeyboardInterrupt:
        print("^C", file=stderr)
