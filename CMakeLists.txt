cmake_minimum_required(VERSION 3.28)
project(RType VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create the Build and Bin directories if they do not exist
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Output directory for binaries (primary: bin folder)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include first-level subdirectories (project binaries)
add_subdirectory(gui)
add_subdirectory(server)

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
