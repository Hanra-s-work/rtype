cmake_minimum_required(VERSION 3.10)
project(RTypeGUI)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

include_directories(/usr/include/asio)

set(SOURCES
    src/Main.cpp
    src/RealMain.cpp
    src/ExceptionHandling.cpp
    src/Network/NetworkManager.cpp
    src/Network/ProtocolHandler.cpp
    src/ECS/Component.cpp
    src/ECS/EntityNode.cpp
    src/ECS/Components/AnimationComponent.cpp
    src/ECS/Components/ButtonComponent.cpp
    src/ECS/Components/CollisionComponent.cpp
    src/ECS/Components/MusicComponent.cpp
    src/ECS/Components/PositionComponent.cpp
    src/ECS/Components/RenderComponent.cpp
    src/ECS/Components/TextComponent.cpp
    src/ECS/Systems/AnimationSystem.cpp
    src/ECS/Systems/ButtonSystem.cpp
    src/ECS/Systems/InputSystem.cpp
    src/ECS/Systems/RenderSystem.cpp
    src/ECS/Systems/Utilities/Clock.cpp
    src/ECS/Systems/Utilities/EventManager.cp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(rtype_gui ${SOURCES})

target_link_libraries(rtype_gui Threads::Threads)
