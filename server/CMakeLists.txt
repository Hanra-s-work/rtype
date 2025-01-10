cmake_minimum_required(VERSION 3.15)
project(MultigameServer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If using standalone Asio, find it or link it. Example:
# find_package(Threads REQUIRED)
# find_path(ASIO_INCLUDE_DIR asio.hpp)

add_executable(multigame_server
    main.cpp
    src/server.cpp
    src/game_manager.cpp
    src/client_manager.cpp
    # message.cpp if needed, etc.
)

# E.g. for standalone Asio:
# target_include_directories(multigame_server PRIVATE ${ASIO_INCLUDE_DIR})
# target_link_libraries(multigame_server PRIVATE Threads::Threads)

# If you have "game_logic.cpp", add it or link it. 
# This example assumes "GameLogic" is header-only or compiled elsewhere.
