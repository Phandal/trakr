cmake_minimum_required(VERSION 3.16..4.0)
project(trackr C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(trakr src/main.c)
install(TARGETS trakr RUNTIME)
