cmake_minimum_required(VERSION 3.15)
project(R-TypeServer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If your code uses threads (and Asio typically needs it):
find_package(Threads REQUIRED)

# If using standalone Asio or Boost.Asio, you'd locate or find it, for example:
# find_path(ASIO_INCLUDE_DIR asio.hpp)
# target_include_directories(r-type_server PRIVATE ${ASIO_INCLUDE_DIR})

# Create the executable from main.cpp and the sources in src/
add_executable(r-type_server
    main.cpp              # In the server folder
    src/message_codec.cpp
    src/client_manager.cpp
    src/logic_manager.cpp
    src/server.cpp
)

# Tell the compiler where to find header files (the "src" folder).
target_include_directories(r-type_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link with threads (and any other libraries you might need):
target_link_libraries(r-type_server PRIVATE Threads::Threads)

# Optional: Set extra warning flags, etc.
# target_compile_options(r-type_server PRIVATE -Wall -Wextra -pedantic)
