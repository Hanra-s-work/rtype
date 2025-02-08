cmake_minimum_required(VERSION 3.28)
project(RTypeServer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")

# Fetch Asio using FetchContent
include(FetchContent)
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-32-0
)
FetchContent_MakeAvailable(asio)

# Gather source files for the server target
file(GLOB_RECURSE SERVER_SOURCES
    "src/*.cpp"
    "include/*.hpp"
)

add_executable(r-type_server ${SERVER_SOURCES})

# Include the server's headers
target_include_directories(r-type_server
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add Asio's include directory (from FetchContent)
target_include_directories(r-type_server PRIVATE ${asio_SOURCE_DIR}/asio/include)

# Link the common protocol library
target_link_libraries(r-type_server
    PRIVATE
        rtype_protocol
)
