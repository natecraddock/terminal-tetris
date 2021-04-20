cmake_minimum_required(VERSION 3.13)

option(COLOR_OUTPUT "Color build output" ON)
if(${COLOR_OUTPUT})
  add_compile_options(-fdiagnostics-color=always)
endif()

project(terminal-tetris)

add_compile_options(-Wall -Werror -D_XOPEN_SOURCE_EXTENDED)

set(EXECUTABLE_OUTPUT_PATH ..)

add_subdirectory(src)
