cmake_minimum_required(VERSION 3.10)
project(RTypeServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

include_directories(/usr/include/asio)

set(SOURCES
    src/main.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(rtype_server ${SOURCES})

target_link_libraries(rtype_server Threads::Threads)
