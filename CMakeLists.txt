cmake_minimum_required(VERSION 3.9)
project(asm C)

set(CMAKE_C_STANDARD 99)
include_directories(libft/includes asm_f/includes)
FILE(GLOB_RECURSE libft_DIR RELATIVE ${CMAKE_SOURCE_DIR} "libft/*.c")
add_library(libft STATIC ${libft_DIR})
add_executable(hello_world_program asm_f/srcs/main.c asm_f/includes/asm.h asm_f/includes/op.h)
target_link_libraries(hello_world_program libft)