cmake_minimum_required(VERSION 3.22)

project(TopLevelTruckConnect)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(repo ".")
cmake_path(ABSOLUTE_PATH repo NORMALIZE)

set(truckconnect_path "c++/truckconnect")
cmake_path(
    SET
    truckconnect_path
    NORMALIZE
    "${repo}/${truckconnect_path}"
)

add_subdirectory("${truckconnect_path}" "truckconnect")

set(testclient_path "c++/testclient")
cmake_path(
    SET
    testclient_path
    NORMALIZE
    "${repo}/${testclient_path}"
)

add_subdirectory("${testclient_path}" "testclient")

set(truckconnectextension_path "truckconnectextension")
cmake_path(
    SET
    truckconnectextension_path
    NORMALIZE
    "${repo}/${truckconnectextension_path}"
)

add_subdirectory("${truckconnectextension_path}" "truckconnectextension")
