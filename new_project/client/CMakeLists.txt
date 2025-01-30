cmake_minimum_required(VERSION 3.28)
project(RTypeClient)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

target_include_directories(r-type_client PUBLIC ${ASIO_INCLUDE_DIR})
