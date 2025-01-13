cmake_minimum_required(VERSION 3.15)
project(rtype_server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Threads REQUIRED) if needed

# Collect your .cpp files that make up the server
set(SERVER_SOURCES
    main.cpp
    src/server.cpp
    src/client_manager.cpp
    src/game_manager.cpp
    # ...
)

add_executable(rtype_server
    ${SERVER_SOURCES}
)

# If your server needs includes from "server/src", do:
target_include_directories(rtype_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link the server to the library from game_source
target_link_libraries(rtype_server
    PRIVATE
        RTypeSource       # from game_source/CMakeLists
        # Threads::Threads    # if needed
        # other libs (asio, etc.) if needed
)
