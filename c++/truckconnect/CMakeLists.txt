cmake_minimum_required(VERSION 4.3)

project(truckconnect CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(repo "../../")
cmake_path(ABSOLUTE_PATH repo NORMALIZE)

set(nstreamcom_path "c++/NStreamCom/")
cmake_path(
    SET
    nstreamcom_path
    NORMALIZE
    "${repo}/${nstreamcom_path}"
)

set(nstreamcom_include_path "include")
cmake_path(
    SET
    nstreamcom_include_path
    NORMALIZE
    "${nstreamcom_path}/${nstreamcom_include_path}"
)

set(nstreamcom_src_path "src")
cmake_path(
    SET
    nstreamcom_src_path
    NORMALIZE
    "${nstreamcom_path}/${nstreamcom_src_path}"
)

set(nstreamcom_sources "")
file(
    GLOB_RECURSE
    nstreamcom_sources
    CONFIGURE_DEPENDS
    "${nstreamcom_src_path}/*.cpp"
)

add_library(nstreamcom STATIC ${nstreamcom_sources})
target_include_directories(nstreamcom PUBLIC "${nstreamcom_include_path}")

set(truckconnect_path "c++/truckconnect")
cmake_path(
    SET
    truckconnect_path
    NORMALIZE
    "${repo}/${truckconnect_path}"
)

set(truckconnect_include_path "include")
cmake_path(
    SET
    truckconnect_include_path
    NORMALIZE
    "${truckconnect_path}/${truckconnect_include_path}"
)

set(truckconnect_src_path "src")
cmake_path(
    SET
    truckconnect_src_path
    NORMALIZE
    "${truckconnect_path}/${truckconnect_src_path}"
)

set(truckconnect_sources "")
file(
    GLOB_RECURSE
    truckconnect_sources
    CONFIGURE_DEPENDS
    "${truckconnect_src_path}/*.cpp"
)

add_library(truckconnect STATIC ${truckconnect_sources})
target_include_directories(truckconnect PUBLIC "${truckconnect_include_path}")
target_link_libraries(truckconnect nstreamcom)
