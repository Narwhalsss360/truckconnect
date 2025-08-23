from time import sleep
from scssdk_telemetry.scssdk_dataclasses import SCS_TELEMETRY_trailers_count
from truckconnect.telemetry_id import TelemetryID
from truckconnect.connection import Connection, TrailerIndexOrCount
from truckconnect.value_storage import is_storage_type, is_value_storage
from truckconnect.data import is_value_storage_array


IP: str = "127.0.0.1"
SLEEP_FOR_SECS: float = 0.500


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
            total_read = bytes_read

            trailers_connected, bytes_read = connection.request_telemetry(TelemetryID.TrailerChannelConnected, TrailerIndexOrCount(True, SCS_TELEMETRY_trailers_count))
            assert isinstance(trailers_connected, list) and is_value_storage_array(trailers_connected, bool), "trailer_connected must be a list[tuple[bool, bool]]"
            total_read += bytes_read

            print(f"Trailers Connected ({total_read} total bytes read):")
            for i, (initialized, connected) in enumerate(trailers_connected):
                print(f"\tTrailer {i + 1}: ", end="")
                if initialized:
                    print("Connected" if connected else "Not Connected")
                else:
                    print("<uninitialized>")
            sleep(SLEEP_FOR_SECS)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("^C")
