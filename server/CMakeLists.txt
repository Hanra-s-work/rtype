cmake_minimum_required(VERSION 3.10)
project(RTypeServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/includes)
include_directories(../game_source/components)
include_directories(../game_source/ECS)
include_directories(../game_source/systems)

include_directories(/usr/include/asio)

set(SOURCES
    src/GameManager.cpp
    src/main.cpp
    src/NetworkManager.cpp
    src/ProtocolHandler.cpp
    src/Server.cpp
    src/ThreadPool.cpp
    ../game_source/ECS/Registry.cpp
    ../game_source/ECS/Entity.cpp
    ../game_source/systems/AISystem.cpp
    ../game_source/systems/CollisionSystem.cpp
    ../game_source/systems/LifetimeSystem.cpp
    ../game_source/systems/MovementSystem.cpp
    ../game_source/systems/WeaponSystem.cpp
    ../game_source/systems/Systems.cpp
    ../game_source/systems/SpawnSystem.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(rtype_server ${SOURCES})

target_link_libraries(rtype_server Threads::Threads)
