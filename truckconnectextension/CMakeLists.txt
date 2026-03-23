cmake_minimum_required(VERSION 4.3)

project(truckconnectextension CXX)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(repo "../")
cmake_path(ABSOLUTE_PATH repo NORMALIZE)

set(truckconnect_path "c++/truckconnect")
cmake_path(
    SET
    truckconnect_path
    NORMALIZE
    "${repo}/${truckconnect_path}"
)

add_subdirectory("${truckconnect_path}" "build")

set(truckconnectextension_path "truckconnectextension")
cmake_path(
    SET
    truckconnectextension_path
    NORMALIZE
    "${repo}/${truckconnectextension_path}"
)

set(truckconnectextension_src_path "")
cmake_path(
    SET
    truckconnectextension_src_path
    NORMALIZE
    "${truckconnectextension_path}/${truckconnectextension_src_path}"
)

set(truckconnectextension_translation_units "")
file(
    GLOB
    test_client_translation_units
    CONFIGURE_DEPENDS
    "${truckconnectextension_src_path}/*.cpp"
)

add_library(
    truckconnectextension
    "${test_client_translation_units}"
)
target_link_libraries(
    truckconnectextension
    truckconnect
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(
        truckconnectextension
        PUBLIC
        TRUCKCONNECT_DEBUG
    )
endif()
