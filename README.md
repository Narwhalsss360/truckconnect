# truckconnect

An extension for ATS & ETS2 telemetry over sockets. 

_See the samples folder in the folder for each language_

---

# Game Extension

Currently only supported on Windows. The game extension `.dll` should be placed in the `bin/win_xxx/plugins` directory in the game directory. The developer console will occasionally show some important messages such as when a client connects, disconnects, or an unexpected request comes in. The extension would also log when the dispatcher (client processing) thread is slower than the game thread which is unexpected, but may happen for large operations, this _may_ important because there are no concurrency devices.

---

## Note For Python

The usage of the python API is mixed between the `scssdk_truckconnect` module in the `truckconnect` repository. 
Use `truckconnect` for connections, data definitions, the master structure, telemetry id enumerations, value storage and corresponding functions. Use `scssdk_truckconnect` for all else. 

# Structure and data

All telemetry data is stored in a "master" structure. 
The master structure is made of other structure for categorization of different telemetry types. 
The naming convention will be the same that is used in the language's standard libraries, or standard style guidelines. 

### Structure

- Master
    - Configuration
        - Substances
        - Controls
        - HShifter
        - Truck
        - Trailer
        - Trailer x10
    - Gameplay
	    - Job cancelled
	    - Job delivered
	    - Player fined
	    - Play tollgate paid
	    - Player use ferry
	    - Player use train
    - Channels
        - General
	        - ...Channels
        - Truck
	        - ...Channels
        - Trailer x10
	        - ...Channels

> [!IMPORTANT]
> - All channels are constant size. 
> - All configuration and gameplay event structs have a `latest` member which is a `u32` that increments when there is new data. Currently, you must poll this value to see when a gameplay event occurs.
> - All telemetry data is held within a _storage_ type:
> 	- Value Storage
> 		- `initialized: bool`
> 		- `value: T`
> 	- Value Array Storage
> 		- `initialized: bool`
> 		- `values: array<T>`
> 		- `count: u32`
> 	- Value Vector/List  Storage
> 		- `value: vec<T>`
>
> In python, these are tuples, and lists: `tuple[bool, T]`, `tuple[bool list[T], int]`, `list[T]` 


### Trailer data

Since the SCS telemetry SDK allows for data of up to 10 (`SCS_TELEMETRY_trailers_count`) trailers, when getting data you may ask for a single trailer by indexing, or multiple trailers for trailer channels and ~~trailer structures~~ (Not implemented properly on extension). 

_A custom type is provided for specifying indices and counts in C++._

### Telemetry IDs

Every channel, structure, has it's own telemetry ID, and can be requested.

### Telemetry Types

There are:
- Structure
- Event Info (_misnomer, it is actually representative of events which are structures, and all it's event infos._)
- Channel

### Data Definitions

You may specify your own structure of telemetry data, to make efficient request of only the data that you need. Data definitions are must be registered, _then_ may be requested by ID, this is for efficient requests of data. Once a definition is no longer needed, you may unregister.

> [!NOTE]
> Data definitions consist of:
> - `definition_id: u8`
> - `members: data_member[]`
> 	- `data_member`:
> 		- `telemetry_id: telemetry_id`
> 		- `offset: usize`: For using structures.
> 		- `trailer_count: u8`

All data would be buffered, packed. 
You may access your data directly in the connection's buffer, with the `DEFINED_DATA_DATA_START` constant offset. 
Defining data is specific to the language. C# uses a class or base class (automatically defines on current instance), and a `Define<T>` for value-types. C++ uses template specializations. Data definitions be created by value, without coupling to a specific type. 
In python, a data definition can be created using the `data_definition(id: int)` decorator on a class, similar to the `dataclass` decorator as `data_definition` is a wrapper. Otherwise data definitions can be deserialized into a tuple of the telemetries in the data definition. 
Specific languages also include API calls to structure the data into your `struct/class` with a corresponding data definition.

---

# Connection and Communication

Connections are made using stream TCP sockets. All data is encoded/decoded using **NStreamCom**, this is probably unnecessary for TCP, but this does open the possibility of using UDP sockets. To get data, you must send a request, and a response of the data will be sent. 

The listener port used is port 52878. 

On windows C++, the API used is WinSock2, which requires initialization before first use, and deinitialization after use. Use `bool sockets::initialize()` and `bool sockets::deinitialize()` for this, which returns `true` on success.

**Requests**:
- None
	- _internal use._
- Telemetry ID
	- Request a single channel, or structure. For a trailer telemetry, use a index for one trailer or use a count to get an array of data.
- Register data definition
- Defined data
	- Request data for a registered data definition.
- Unregister data definition
- Error response
	- This is when a communication result is returned by the server, not your process.
- Version
    - Used to get the version that the server is running.

**Communication Results**:
- `success`
	- Operation successful.
- `generic_socket_error`
    - Use OS's get last error for sockets for more information.
- `already_connected`
    - Attempted to connect while already connected.
- `not_connected`
    - Attempted to send a request or disconnect, when not connected.
- `disconnected`
    - The connection gracefully disconnected.
- `incomplete`
    - A request response is not fully received yet.
- `collector_error`
    - A `NStreamCom` collector error. See the collector object for more information.
- `no_pending_request`
    - Attempted to receive a response, without a request first.
- `invalid_telemetry`
    - Attempted to use an invalid telemetry id.
- `invalid_trailer_index`
    - Trailer index was out of bounds....
- `other_request_pending`
    - Attempted to do another request while still receiving data for another request.
- `other_telemetry_id_pending`
    - Attempted to do another request of telemetry by id, while another id was pending.
- `other_trailer_index_request_pending`
    - Attempted to do another request of a trailer telemetry while another request for another index was pending.
- `received_other_response`
    - Received data for a different request.
- `received_other_telemetry`
    - Received data for another telemetry.
- `received_other_trailer_index`
    - Received data for another index of the same telemetry.
- `deserialization_failure`
    - Failure to deserialize data in buffer.
- `trailer_index_out_of_bounds`
    - _unused._
- `trailer_count_out_of_bounds`
    - A specified trailer count was larger than `SCS_TELEMETRY_trailers_count`.
- `trailer_index_or_count_was_count`
    - This operations does not support trailer counts, or trailer indices.
- `null_argument`
    - Argument was null.
- `empty`
    - Argument was an empty array.
- `already_registered`
    - Attempted to register a data definition that was already registered. _note: the same **id** was already registered, not necessarily the members._
- `other_defined_data_pending`
    - Attempted to request a data definition while another was pending.
- `not_registered`
    - Attempted to request a data definition which was not registered,
- `arrange_error`
    - Deserialization and structuring a data definition into a `struct/class` failed.
- `badly_formed`
    - The client sent a badly formed data definition registration request.
- `unknown_data`
	- Received data that did not specify was the response is.

_In certain languages, errors are values (C++) and in others, errors are exceptions (C#, Python)._

# Constants/Macros

**C++**:
- `TRUCKCONNECT "x.x.x"`
- `TRUCKCONNECT_MAJOR x`
- `TRUCKCONNECT_MINOR x`
- `TRUCKCONNECT_PATCH x`
- `TRUCKCONNECT_NAMESPACE truckconnect`

# Building

All required include directories are named `include`, and all source directories are named `src`, within `C++/` 

Use VisualStudio for C# projects.

*Minimum C++: c++17*

### Build System: VisualStudio

- C++ Shared Items Project: `C++/NStreamCom/...`
	- Encoding/Decoding library.
- C++ Shared Items Project: `C++/truckconnect`
	- Contains all necessary client API, which is also used by the server.
	- Dependencies:
		- `C++/NStreamCom`
- MSVC Project: `truckconnectextension`
	- Dynamic-Link Library project. Place a `dllcopy.py` script in the `OutputDir` to automagically copy the dll to your installation of the game.
		- Dependencies:
			- `C++/truckconnect`
				- `C++/NStreamCom`
- C# Class Library Project `C#/NStreamCom`
	- Encoding/Decoding library.
- C# Class Library Project `C#/TruckConnectDotNet`
	- Contains all necessary client API.
		- Dependencies
			- `C#/NStreamCom`
- MSVC Project: `c++/testclient`
	- A rudimentary project to "test" certain API calls.
		- Dependencies
			- `C++/truckconnect`
				- `C++/NStreamCom`
- C# Console Project: `C#/TestClientDotNet`
	- A rudimentary project to "test" certain API calls.
	- Dependencies:
		- `C#/TruckConnectDotNet`
			- `C#/NStreamCom`

### Cross-Platform Compatibility

Currently only confirmed on windows, the build system is VisualStudio. API calls are wrapped in a `truckconnect::platform` namespace for cross-platform/compiler implementations. 

---

# Auto-generated Code (Meta Programming)

Most lines of code are automatically generated by a script ([repo](https://github.com/Narwhalsss360/scssdk-telemetry/tree/truckconnect)). 
The repository is a branch off of the `scssdk_telemetry` repository, which is an enumeration of the scssdk telemetry haeder files: 
- main (scssdk_telemetry)
    - truckconnect (scssdk_truckconnect)

The purpose of the auto-generated code is to have the option of compile-time constant-expression evaluation and _metadata_ structs for use as template parameters. 

This also opens the opportunity for implementation in other languages.

The script is a python module, which has several "main functions" (commands) which may be invoked depending on the argument supplied 

### Scripts

- `truckconnect`
    - Will simply build the truckconnect telemetries and write a `truckconnect_master_telemetry.json` file 
- `cpp`
    - Generates C++ code 
- `csharp`
    - Generates C# code 
- `py`
    - Generates Python code 

### Output Directory

The output directory of the generated files are determined by the `OUTPUT_FOLDER: Path` (in each language script) constant which by default is `generated.gitignore/`

---

*v0.1.0*
