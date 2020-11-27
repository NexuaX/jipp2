cmake_minimum_required(VERSION 3.0)

project(sqlite3)

add_library(sqlite3 STATIC ./src/sqlite3.c)
