cmake_minimum_required(VERSION 3.28)
project(SFML LANGUAGES CXX VERSION 2.6)

include(FetchContent)

# Fetch SFML library
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x # Use the latest stable release branch
)

# Make SFML available
FetchContent_MakeAvailable(SFML)

# Create a library target for SFML
add_library(sfml-libs INTERFACE)
target_include_directories(sfml-libs INTERFACE ${SFML_SOURCE_DIR}/include)
target_link_libraries(sfml-libs INTERFACE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
