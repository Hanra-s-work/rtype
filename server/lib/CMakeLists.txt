cmake_minimum_required(VERSION 3.28)
project(RTypeServerLibs LANGUAGES CXX)

# Add the asio library
add_subdirectory(asio)

# Add the toml library
add_subdirectory(toml)

# Aggregate libraries into rtype_libraries
add_library(rtype_server_libraries INTERFACE)

# Add the asio library
target_link_libraries(rtype_server_libraries INTERFACE asio)

# Add the toml library
target_link_libraries(rtype_server_libraries INTERFACE server_tomlplusplus)
