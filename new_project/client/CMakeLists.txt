cmake_minimum_required(VERSION 3.15)
project(RTypeClient)

# Find SFML packages
find_package(SFML 2.5 COMPONENTS window graphics system network REQUIRED)

# Include directories
include_directories(include ${SFML_INCLUDE_DIR})

# Create executable
add_executable(rtype_client 
    src/Client.cpp
    src/main.cpp
    src/NetworkClient.cpp
    src/ParallaxBackground.cpp
)

# Link SFML libraries
target_link_libraries(rtype_client 
    sfml-window
    sfml-graphics
    sfml-system
    sfml-network
)