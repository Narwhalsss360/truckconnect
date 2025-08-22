from sys import stderr

try:
    import npycli
except ImportError as err:
    print("\n\nThe 'npycli' module is required for truckconnect_util\n", file=stderr)
    raise err

