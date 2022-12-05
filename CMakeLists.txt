cmake_minimum_required(VERSION 3.0)

project(handy LANGUAGES C)

add_executable(handy main.c)

install(TARGETS handy RUNTIME DESTINATION bin)
