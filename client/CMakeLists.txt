cmake_minimum_required(VERSION 3.28)
project(RTypeClient)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")

# Include directories for headers
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Include the CMakeLists.txt from the Lib folder
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib)

# Create executable
set(SOURCES 
    src/Client.cpp
    src/main.cpp
    src/NetworkClient.cpp
    src/HandleBackground.cpp
    src/SpriteEntity.cpp
    src/EntityManager.cpp
    src/HUD.cpp
    src/TextureManager.cpp
    src/MusicHandler.cpp
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
    rtype_protocol
    Threads::Threads
    sfml-graphics sfml-window sfml-audio sfml-network sfml-system
)

if(WIN32)
    # Set a variable to point to your SFML DLL directory.
    # Adjust this path to match where your SFML DLLs are built or installed.
    set(SFML_DLL_DIR "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug")
    set(OPEN_AL_DIR "${CMAKE_SOURCE_DIR}/build/_deps/sfml-src/extlibs/bin/x64")

    # Copy SFML graphics DLL.
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-graphics-d-2.dll"
            $<TARGET_FILE_DIR:r-type_client>
        COMMENT "Copying sfml-graphics-d-2.dll to output directory"
    )

    # Copy SFML window DLL.
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-window-d-2.dll"
            $<TARGET_FILE_DIR:r-type_client>
        COMMENT "Copying sfml-window-d-2.dll to output directory"
    )

    # Copy SFML audio DLL.
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-audio-d-2.dll"
            $<TARGET_FILE_DIR:r-type_client>
        COMMENT "Copying sfml-audio-d-2.dll to output directory"
    )

    # Copy SFML network DLL.
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-network-d-2.dll"
            $<TARGET_FILE_DIR:r-type_client>
        COMMENT "Copying sfml-network-d-2.dll to output directory"
    )

    # Copy SFML system DLL.
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-system-d-2.dll"
            $<TARGET_FILE_DIR:r-type_client>
        COMMENT "Copying sfml-system-d-2.dll to output directory"
    )

    # Copy OpenAL32.dll.
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${OPEN_AL_DIR}/openal32.dll"
            $<TARGET_FILE_DIR:r-type_client>
        COMMENT "Copying OpenAL32.dll to output directory"
    )
endif()

target_include_directories(r-type_client PUBLIC ${ASIO_INCLUDE_DIR})