cmake_minimum_required(VERSION 3.28)
project(RTypeClient VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the include directories
include_directories(include)

# Include the CMakeLists.txt from the Lib folder to inherit the desired libraries
include(${CMAKE_CURRENT_LIST_DIR}/lib/CMakeLists.txt)

# Set the source files
set(SOURCES

    # The files at the source of the program
    src/Main.cpp
    src/Debug.cpp
    src/RealMain.cpp
    src/MainClass.cpp
    src/TOMLLoader.cpp
    src/HelpFunctions.cpp
    src/ExceptionHandling.cpp

    # The files in charge of managing the networking side
    src/GUI/Network/NetworkManager.cpp
    src/GUI/Network/ProtocolHandler.cpp

    # The files in charge of allowing polymorphic imports
    src/GUI/ECS/Component.cpp
    src/GUI/ECS/EntityNode.cpp

    # The files in charge of containing the components of the program
    src/GUI/ECS/Components/AnimationComponent.cpp
    src/GUI/ECS/Components/CollisionComponent.cpp
    src/GUI/ECS/Components/MusicComponent.cpp
    src/GUI/ECS/Components/ShapeComponent.cpp
    src/GUI/ECS/Components/TextComponent.cpp
    src/GUI/ECS/Components/TextureComponent.cpp
    src/GUI/ECS/Components/SpriteComponent.cpp
    src/GUI/ECS/Components/ButtonComponent.cpp

    # The files in charge of containing the system files
    src/GUI/ECS/Systems/AnimationSystem.cpp
    src/GUI/ECS/Systems/ButtonSystem.cpp
    src/GUI/ECS/Systems/InputSystem.cpp
    src/GUI/ECS/Systems/RenderSystem.cpp

    # The files in charge of containing the utility classes
    src/GUI/ECS/Utilities/Font.cpp
    src/GUI/ECS/Utilities/Clock.cpp
    src/GUI/ECS/Utilities/Window.cpp
    src/GUI/ECS/Utilities/MouseInfo.cpp
    src/GUI/ECS/Utilities/EventManager.cpp
)

# Check for threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add the executable
add_executable(r-type_client ${SOURCES})

# Link SFML and Threads to the executable
target_link_libraries(r-type_client
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
