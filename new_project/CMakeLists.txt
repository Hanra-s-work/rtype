cmake_minimum_required(VERSION 3.11)
project(RType VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Server and Client subdirs (each with its own CMakeLists)
add_subdirectory(server)
add_subdirectory(client)
