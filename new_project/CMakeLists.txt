cmake_minimum_required(VERSION 3.11)
project(RType VERSION 1.0 LANGUAGES CXX)

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

# Installing sfml 2.6.0
CPMAddPackage(NAME SFML
    GITHUB_REPOSITORY SFML/SFML
    VERSION 2.6.0
    GIT_TAG 2.6.0
    OPTIONS
    "SFML_GENERATE_PACKAGE=FALSE"
    "SFML_STATIC_LIBRARIES=TRUE")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Add Server and Client subdirs (each with its own CMakeLists)
add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)