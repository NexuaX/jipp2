cmake_minimum_required(VERSION 3.0.0)
project(lab8 VERSION 0.1.0)

include_directories( ./include ./src )

find_package( Threads )
add_executable( output ./src/main.cpp ./src/multi_mutex.cpp )
target_link_libraries( output ${CMAKE_THREAD_LIBS_INIT} )
