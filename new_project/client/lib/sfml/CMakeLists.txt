cmake_minimum_required(VERSION 3.28)
project(SFML LANGUAGES CXX VERSION 3.0.0)

# FetchContent module is used to download and include SFML and Asio in the project
include(FetchContent)

# Fetch SFML library (from the Git repository, stable 2.6.x version)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
    GIT_SHALLOW ON
)

# Fetch Asio library (from the Git repository)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-32-0
)

# Make SFML and Asio available
FetchContent_MakeAvailable(SFML asio)

# Create an interface target for SFML
add_library(sfml-libs INTERFACE)
target_include_directories(sfml-libs INTERFACE ${SFML_SOURCE_DIR}/include)

# Add the Asio include path to SFML
target_include_directories(sfml-libs INTERFACE ${asio_SOURCE_DIR}/asio/include)

# Link SFML to Asio (Asio is header-only, so no need to link to a compiled library)
target_link_libraries(sfml-libs INTERFACE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Now you also need to link the Asio headers to your target
target_link_libraries(sfml-libs INTERFACE gui_asio)
