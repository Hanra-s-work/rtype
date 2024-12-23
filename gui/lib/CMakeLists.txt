cmake_minimum_required(VERSION 3.28)
project(RTypeLibs LANGUAGES CXX)

# Include SFML, ASIO, and TOML

# Include the sfml library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SFML)

# Include the asio library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/asio)

# Include the toml library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/toml)

# Create a library target for reusable libraries
add_library(rtype_libraries INTERFACE)

# Add the sfml libraries to the rtype_libraries target
target_link_libraries(rtype_libraries INTERFACE sfml-libs)

# Add the asio libraries to the rtype_libraries target
target_link_libraries(rtype_libraries INTERFACE asio)

# Add the toml libraries to the rtype_libraries target
target_link_libraries(rtype_libraries INTERFACE tomlplusplus)
