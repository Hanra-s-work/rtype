cmake_minimum_required(VERSION 3.28)
project(SFML LANGUAGES CXX VERSION 3.0.0)

# FetchContent module is used to download and include SFML in the project
include(FetchContent)

# Fetch SFML library (from the Git repository, stable 2.6.x version)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    SYSTEM
)

# Make SFML available
FetchContent_MakeAvailable(SFML)

# Create a library target for SFML
add_library(sfml-libs INTERFACE)
target_include_directories(sfml-libs INTERFACE ${SFML_SOURCE_DIR}/include)

# target_link_libraries(sfml-libs INTERFACE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(sfml-libs INTERFACE SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network)
