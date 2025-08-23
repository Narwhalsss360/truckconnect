from time import sleep
from truckconnect.telemetry_id import TelemetryID
from truckconnect.connection import Connection
from truckconnect.value_storage import is_storage_type, is_value_storage


IP: str = "127.0.0.1"
SLEEP_FOR_SECS: float = 0.050


def main() -> None:
    # Or use connection.connect(), connection.disconnect() for manual resource management.
    with Connection(IP) as connection:
        while True:
            paused_tuple, bytes_read = connection.request_telemetry(TelemetryID.ChannelPaused)
            assert is_storage_type(paused_tuple) and is_value_storage(paused_tuple, bool), "Paused must be a tuple[bool, bool] => initialized, value"
            _, paused = paused_tuple # paused is always initialized
            if paused:
                print("<paused>")
                sleep(SLEEP_FOR_SECS)
                continue

            speed_tuple, bytes_read = connection.request_telemetry(TelemetryID.TruckChannelSpeed)
            assert is_storage_type(speed_tuple) and is_value_storage(speed_tuple, float), "Speed must be a tuple[bool, float] => initialized, value"
            speed_initialized, speed = speed_tuple

            if not speed_initialized:
                print("<uninitialized>")
            else:
                print(f"{speed:0.2f} m/s (f{bytes_read} bytes read)")
            sleep(SLEEP_FOR_SECS)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("^C")
