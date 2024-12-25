cmake_minimum_required(VERSION 3.28)
project(RTypeServer VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/includes)

# Include the CMakeLists.txt from the Lib folder to inherit the desired libraries
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib)

set(SOURCES
    src/GameManager.cpp
    src/main.cpp
    src/NetworkManager.cpp
    src/ProtocolHandler.cpp
    src/Server.cpp
    src/ThreadPool.cpp
)

# Check for threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Create the server executable
add_executable(r-type_server ${SOURCES})

# Link libraries needed by the server (asio and toml++)
target_link_libraries(r-type_server
    PRIVATE
    rtype_server_libraries
    Threads::Threads
)
