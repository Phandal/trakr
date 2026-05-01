cmake_minimum_required(VERSION 3.16..4.0)
project(trackr LANGUAGES C VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(include/version.h.in include/version.h)

add_executable(trakr 
  src/main.c
  src/command.c
  src/config.c
  src/trakr.c
)
target_include_directories(trakr PUBLIC include)
target_include_directories(trakr PUBLIC build/include)

install(TARGETS trakr RUNTIME)
