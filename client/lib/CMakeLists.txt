cmake_minimum_required(VERSION 3.28)
project(RTypeClientLibs LANGUAGES CXX)

# Add SFML and TOML libraries
add_subdirectory(asio)
add_subdirectory(sfml)

# Create an interface library for reusable libraries
add_library(rtype_client_libraries INTERFACE)

# Link Asio libraries
target_link_libraries(rtype_client_libraries INTERFACE gui_asio)

# Link SFML libraries
target_link_libraries(rtype_client_libraries INTERFACE sfml-libs)