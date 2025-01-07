cmake_minimum_required(VERSION 3.14)
project(my_window)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Fetch SFML 3.0.0
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Add your executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link SFML library
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network)
