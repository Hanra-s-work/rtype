cmake_minimum_required(VERSION 3.10)
project(RTypeServer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/includes)

include_directories(/usr/include/asio)

set(SOURCES
    src/GameManager.cpp
    src/main.cpp
    src/NetworkManager.cpp
    src/ProtocolHandler.cpp
    src/Server.cpp
    src/ThreadPool.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(r-type_server ${SOURCES})

target_link_libraries(r-type_server Threads::Threads)