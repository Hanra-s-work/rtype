cmake_minimum_required(VERSION 3.28)
project(RType VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding cpm.cmake to the project
set(CPM_URL "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake")
set(CPM_PATH "${CMAKE_BINARY_DIR}/CPM.cmake")

file(DOWNLOAD
    ${CPM_URL}
    ${CPM_PATH}
    SHOW_PROGRESS
)

include(${CPM_PATH})

# Adding sfml and asio libraries
CPMAddPackage(NAME asio
    GITHUB_REPOSITORY chriskohlhoff/asio
    GIT_TAG asio-1-32-0)
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

# Installing sfml 3.0.0
CPMAddPackage(NAME SFML
    GITHUB_REPOSITORY SFML/SFML
    VERSION 3.0.0
    GIT_TAG 3.0.0
    OPTIONS
    "SFML_GENERATE_PACKAGE=FALSE"
    "SFML_STATIC_LIBRARIES=TRUE")

# Create the Build and Bin directories if they do not exist
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Output directory for binaries (primary: bin folder)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include first-level subdirectories (project binaries)
add_subdirectory(gui)
add_subdirectory(server)
add_subdirectory(game_source)

if(WIN32)
    file(GLOB SFML_DLLS
        "${SFML_BINARY_DIR}/lib/*.dll"
        "${SFML_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/*.dll"
    )

    add_custom_command(TARGET rtype-client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SFML_BINARY_DIR}/lib $<TARGET_FILE_DIR:rtype-client>)

    if(EXISTS "${SFML_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")
        add_custom_command(TARGET rtype-client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
            $<TARGET_FILE_DIR:rtype-client>)
    endif()

    add_custom_command(TARGET rtype-client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64"
        $<TARGET_FILE_DIR:rtype-client>)
endif()

# Secondary output directory: source folder
set(SECONDARY_OUTPUT_DIR ${CMAKE_SOURCE_DIR})

# Add a post-build step to copy binaries to the secondary location
add_custom_target(copy_binaries ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${SECONDARY_OUTPUT_DIR}
    DEPENDS gui server
)

# Ensure the custom target depends on all subdirectories
# This is now safe to do after defining the targets.
add_dependencies(copy_binaries r-type_client r-type_server)
