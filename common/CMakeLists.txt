cmake_minimum_required(VERSION 3.28)
project(rtype_protocol)

add_library(rtype_protocol STATIC
    NetworkProtocol.cpp
)

target_include_directories(rtype_protocol
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}  # so #include "NetworkProtocol.hpp" works
)

# Optionally, force the output directory:
set_target_properties(rtype_protocol PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/common/Debug"
)
