file(GLOB_RECURSE SERVER_SOURCES
    "src/*.cpp"
    "include/*.hpp"
)

add_executable(r-type_server
    ${SERVER_SOURCES}
)

target_include_directories(r-type_server
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(r-type_server
    PRIVATE
        rtype_protocol
)