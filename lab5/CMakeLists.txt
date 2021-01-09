cmake_minimum_required(VERSION 3.0.0)
project(lab5 VERSION 0.1.0)

include_directories( ./include ./src )

add_executable(output ./src/main.cpp ./src/matrix.cpp)
