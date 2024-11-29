cmake_minimum_required(VERSION 3.10)
project(RTypeServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(server/includes)

set(SOURCES
    server/GameManager.cpp
    server/main.cpp
    server/NetworkManager.cpp
    server/ProtocolHandler.cpp
    server/Server.cpp
    server/ThreadPool.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(rtype_server ${SOURCES})

target_link_libraries(rtype_server Threads::Threads)
