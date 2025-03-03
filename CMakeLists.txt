cmake_minimum_required( VERSION 3.22 )

project( DETOX )

set( CMAKE_C_STANDARD )

add_executable( detox src/main.c )

target_link_libraries( detox m )
