add_library(rtype_protocol
    NetworkProtocol.cpp
)

target_include_directories(rtype_protocol
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # so #include "NetworkProtocol.hpp" works
)
