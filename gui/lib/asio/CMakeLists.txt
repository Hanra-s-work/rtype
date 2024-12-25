cmake_minimum_required(VERSION 3.28)
project(Asio LANGUAGES CXX)

include(FetchContent)

# Fetch Asio library
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-32-0
)

# Make Asio available
FetchContent_MakeAvailable(asio)

# Create a library target for Asio
add_library(gui_asio INTERFACE)
target_include_directories(gui_asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
