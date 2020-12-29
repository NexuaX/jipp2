cmake_minimum_required(VERSION 3.0.0)
project(lab6 VERSION 0.1.0)

include_directories( ./include ./src ./libs/sqlite3/include )

add_executable(output ./src/main.cpp ./src/employee.cpp ./src/hrms.cpp)

add_subdirectory( ./libs/sqlite3 )
target_link_libraries( output sqlite3 pthread ${CMAKE_DL_LIBS} )
