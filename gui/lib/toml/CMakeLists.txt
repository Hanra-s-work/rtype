cmake_minimum_required(VERSION 3.28)
project(tomlplusplus LANGUAGES CXX)

include(FetchContent)

# Fetch toml++ (Header-only library)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.3.0 # Latest stable version
)

# Make toml++ available
FetchContent_MakeAvailable(tomlplusplus)

# Add interface target for toml++
add_library(tomlplusplus INTERFACE)
target_include_directories(tomlplusplus INTERFACE ${tomlplusplus_SOURCE_DIR})
