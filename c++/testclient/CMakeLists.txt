cmake_minimum_required(VERSION 3.22)

project(testclient CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(repo "../../")
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

set(testclient_src_path "")
cmake_path(
    SET
    testclient_src_path
    NORMALIZE
    "${testclient_path}/${testclient_src_path}"
)

set(testclient_translation_units "")
file(
    GLOB
    testclient_translation_units
    CONFIGURE_DEPENDS
    "${testclient_src_path}/*.cpp"
)

add_executable(
    testclient
    "${testclient_translation_units}"
)
target_link_libraries(
    testclient
    truckconnect
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(WIN32 AND NOT MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    endif()
endif()
