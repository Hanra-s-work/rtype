file(GLOB_RECURSE SERVER_SOURCES
    "src/*.cpp"
    "include/*.hpp"
)

add_executable(rtype_server
    ${SERVER_SOURCES}
)

target_include_directories(rtype_server
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# If using Boost or standalone Asio:
# find_package(Boost REQUIRED COMPONENTS system)
# target_include_directories(rtype_server PUBLIC ${Boost_INCLUDE_DIRS})
# target_link_libraries(rtype_server PRIVATE Boost::system)
