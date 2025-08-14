from truckconnect.connection import Connection
from scssdk_truckconnect.truckconnect import Version, VERSION
from sys import stderr


def main(connection: Connection) -> None:
    version: Version = connection.get_version()
    print(f"Server: {version}, Client: {VERSION}")
    if version.major != VERSION.major or version.minor != VERSION.minor:
        print("Version mismatch", file=stderr)
        return
    if version.patch < VERSION.patch:
        print("out-patched server", file=stderr)


if __name__ == "__main__":
    with Connection() as connection:
        main(connection)
