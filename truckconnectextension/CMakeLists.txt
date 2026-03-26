cmake_minimum_required(VERSION 3.22)

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

add_subdirectory("${truckconnect_path}" "truckconnect")

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

set(truckconnectextension_module_file "module.def")
cmake_path(
    SET
    truckconnectextension_module_file
    NORMALIZE
    "${truckconnectextension_path}/${truckconnectextension_module_file}"
)

add_library(
    truckconnectextension
    SHARED
    "${test_client_translation_units}"
    "${truckconnectextension_module_file}"
)
target_link_libraries(
    truckconnectextension
    truckconnect
)

set_target_properties(truckconnectextension PROPERTIES ENABLE_EXPORTS TRUE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(WIN32 AND NOT MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    endif()
endif()
