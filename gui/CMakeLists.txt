cmake_minimum_required(VERSION 3.28)
project(RTypeClient VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for headers
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Include the CMakeLists.txt from the Lib folder
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib)

# Set the source files
set(SOURCES

    # Files at the source of the program
    src/Log.cpp
    src/Main.cpp
    src/RealMain.cpp
    src/SoundLib.cpp
    src/MainClass.cpp
    src/TOMLLoader.cpp
    src/HelpFunctions.cpp

    # Custom exceptions
    src/CustomExceptions/No.cpp
    src/CustomExceptions/Found.cpp
    src/CustomExceptions/Failed.cpp
    src/CustomExceptions/Invalid.cpp
    src/CustomExceptions/Unknown.cpp
    src/CustomExceptions/NotFound.cpp
    src/CustomExceptions/NotInitialised.cpp

    # Network files
    src/GUI/Network/ThreadCapsule.cpp
    src/GUI/Network/NetworkManager.cpp
    src/GUI/Network/ProtocolHandler.cpp

    # The files in charge of allowing polymorphic imports
    src/GUI/ECS/Component.cpp
    src/GUI/ECS/EntityNode.cpp

    # ECS Components
    src/GUI/ECS/Components/TextComponent.cpp
    src/GUI/ECS/Components/MusicComponent.cpp
    src/GUI/ECS/Components/ImageComponent.cpp
    src/GUI/ECS/Components/ShapeComponent.cpp
    src/GUI/ECS/Components/SpriteComponent.cpp
    src/GUI/ECS/Components/ButtonComponent.cpp
    src/GUI/ECS/Components/TextureComponent.cpp
    src/GUI/ECS/Components/AnimationComponent.cpp

    # ECS Demo
    src/GUI/ECS/Demo/Bullet.cpp
    src/GUI/ECS/Demo/EnemyBrain.cpp
    src/GUI/ECS/Demo/PlayerBrain.cpp
    src/GUI/ECS/Demo/Orchestrator.cpp

    # ECS Online
    src/GUI/ECS/Online/Bullet.cpp
    src/GUI/ECS/Online/EnemyBrain.cpp
    src/GUI/ECS/Online/PlayerBrain.cpp
    src/GUI/ECS/Online/Orchestrator.cpp

    # ECS Systems
    src/GUI/ECS/Systems/Key.cpp
    src/GUI/ECS/Systems/Font.cpp
    src/GUI/ECS/Systems/Clock.cpp
    src/GUI/ECS/Systems/Colour.cpp
    src/GUI/ECS/Systems/Window.cpp
    src/GUI/ECS/Systems/MouseInfo.cpp
    src/GUI/ECS/Systems/Collision.cpp
    src/GUI/ECS/Systems/EventManager.cpp

    # General Utilities files

    # Custom rebinds
    src/Recoded/Rect.cpp
    src/Recoded/ToString.cpp
)

# Check for threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add executable for the GUI client
add_executable(r-type_client ${SOURCES})

# Link required libraries (SFML + toml++)
target_link_libraries(r-type_client
    PRIVATE
    rtype_client_libraries
    Threads::Threads
)

# Enable debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode detected: Creating unit tests executable")
    target_compile_options(r-type_client PRIVATE -g)
endif()

# Custom target to clean build artifacts
add_custom_target(fclean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Removing all build artifacts and directories"
)
