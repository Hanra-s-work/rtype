cmake_minimum_required(VERSION 3.10)
project(RTypeSource)

set(CMAKE_CXX_STANDARD 17)

include_directories(components)
include_directories(ECS/include)
include_directories(manager/include)
include_directories(systems/include)

set(SOURCES
    ECS/Entity.cpp
    ECS/Registry.cpp
    manager/Time.cpp
    manager/Random.cpp
    manager/Game.cpp
    manager/Queue.cpp
    systems/AISystem.cpp
    systems/CollisionSystem.cpp
    systems/EventSystem.cpp
    systems/LifetimeSystem.cpp
    systems/MovementSystem.cpp
    systems/SpawnSystem.cpp
    systems/Systems.cpp
    systems/WeaponSystem.cpp
)

# Unit tests
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode detected: Creating unit tests executable")
    include_directories(tests/include)
    list(APPEND SOURCES tests/main.cpp)
    list(APPEND SOURCES tests/Tests.cpp)

    add_executable(RTypeSource ${SOURCES})
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()
