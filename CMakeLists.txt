cmake_minimum_required(VERSION 3.16..4.0)
project(trackr C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(trakr 
  src/main.c
  src/command.c
  src/session.c
  src/config.c
  src/trakr.c
)
target_include_directories(trakr PUBLIC src)

install(TARGETS trakr RUNTIME)
