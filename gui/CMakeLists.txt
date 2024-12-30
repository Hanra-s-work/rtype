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
    src/Main.cpp
    src/Debug.cpp
    src/RealMain.cpp
    src/MainClass.cpp
    src/TOMLLoader.cpp
    src/HelpFunctions.cpp
    src/ExceptionHandling.cpp

    # Network files
    src/GUI/Network/NetworkManager.cpp
    src/GUI/Network/ProtocolHandler.cpp

    # The files in charge of allowing polymorphic imports
    src/GUI/ECS/Component.cpp
    src/GUI/ECS/EntityNode.cpp

    # ECS Components
    src/GUI/ECS/Components/TextComponent.cpp
    src/GUI/ECS/Components/MusicComponent.cpp
    src/GUI/ECS/Components/ShapeComponent.cpp
    src/GUI/ECS/Components/SpriteComponent.cpp
    src/GUI/ECS/Components/ButtonComponent.cpp
    src/GUI/ECS/Components/TextureComponent.cpp
    src/GUI/ECS/Components/CollisionComponent.cpp
    src/GUI/ECS/Components/AnimationComponent.cpp

    # ECS system components
    src/GUI/ECS/Systems/InputSystem.cpp
    src/GUI/ECS/Systems/ButtonSystem.cpp
    src/GUI/ECS/Systems/RenderSystem.cpp
    src/GUI/ECS/Systems/AnimationSystem.cpp

    # ECS Utilities
    src/GUI/ECS/Utilities/key.cpp
    src/GUI/ECS/Utilities/Font.cpp
    src/GUI/ECS/Utilities/Clock.cpp
    src/GUI/ECS/Utilities/Colour.cpp
    src/GUI/ECS/Utilities/Window.cpp
    src/GUI/ECS/Utilities/MouseInfo.cpp
    src/GUI/ECS/Utilities/EventManager.cpp

    # Custom rebinds
    src/MyRecodes/Rect.cpp
    src/MyRecodes/ToString.cpp
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

# Custom target to clean build artifacts
add_custom_target(fclean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Removing all build artifacts and directories"
)
