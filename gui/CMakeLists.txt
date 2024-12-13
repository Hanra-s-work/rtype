cmake_minimum_required(VERSION 3.10)
project(r-type_client)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

include_directories(/usr/include/asio)

set(SOURCES
    src/Main.cpp
    src/RealMain.cpp
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
    src/GUI/ECS/Utilities/EventManager.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(rtype_gui ${SOURCES})

target_link_libraries(rtype_gui Threads::Threads)
