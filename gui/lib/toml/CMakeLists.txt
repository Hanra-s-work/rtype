cmake_minimum_required(VERSION 3.28)
project(tomlplusplus LANGUAGES CXX)

include(FetchContent)

# Fetch toml++ (Header-only library)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    GIT_SHALLOW ON
)

# Make toml++ available
FetchContent_MakeAvailable(tomlplusplus)

# Add interface target for toml++
add_library(gui_tomlplusplus INTERFACE)
target_include_directories(gui_tomlplusplus INTERFACE ${tomlplusplus_SOURCE_DIR}/include)
