cmake_minimum_required(VERSION 3.10)
project(r-type_client)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(/usr/include/asio)

# Set the source files
set(SOURCES
    src/Main.cpp
    src/Debug.cpp
    src/RealMain.cpp
    src/MainClass.cpp
    src/HelpFunctions.cpp
    src/ExceptionHandling.cpp

    src/GUI/Network/NetworkManager.cpp
    src/GUI/Network/ProtocolHandler.cpp

    src/GUI/ECS/Component.cpp
    src/GUI/ECS/EntityNode.cpp

    src/GUI/ECS/Components/AnimationComponent.cpp
    src/GUI/ECS/Components/ButtonComponent.cpp
    src/GUI/ECS/Components/CollisionComponent.cpp
    src/GUI/ECS/Components/MusicComponent.cpp
    src/GUI/ECS/Components/PositionComponent.cpp
    src/GUI/ECS/Components/RenderComponent.cpp
    src/GUI/ECS/Components/TextComponent.cpp

    src/GUI/ECS/Systems/AnimationSystem.cpp
    src/GUI/ECS/Systems/ButtonSystem.cpp
    src/GUI/ECS/Systems/InputSystem.cpp
    src/GUI/ECS/Systems/RenderSystem.cpp

    src/GUI/ECS/Utilities/Clock.cpp
    src/GUI/ECS/Utilities/Window.cpp
    src/GUI/ECS/Utilities/EventManager.cpp
)

# Find SFML
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics audio network)

# Check for threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add the executable
add_executable(r-type_client ${SOURCES})

# Link SFML and Threads to the executable
target_link_libraries(r-type_client
    Threads::Threads
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)

# Custom target for cleaning build artifacts
add_custom_target(fclean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Removing all build artifacts and directories"
)
