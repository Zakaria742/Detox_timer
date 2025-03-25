cmake_minimum_required( VERSION 3.22 )

project( DETOX )
set(CMAKE_BUILD_TYPE Debug)
set( CMAKE_C_STANDARD )

add_custom_target(runIt COMMAND detox "5" DEPENDS detox ${CMAKE_BINARY_DIR})

add_executable( detox src/main.c )

target_link_libraries( detox m )
