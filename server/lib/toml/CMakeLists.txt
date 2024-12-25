cmake_minimum_required(VERSION 3.28)
project(server_tomlplusplus LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(tomlplusplus)

add_library(server_tomlplusplus INTERFACE)
target_include_directories(server_tomlplusplus INTERFACE ${tomlplusplus_SOURCE_DIR}/include)
