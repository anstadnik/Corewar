cmake_minimum_required(VERSION 3.9)
project(TRUE_COREWAR C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
include_directories(libft/includes asm_f/includes)
FILE(GLOB_RECURSE libft_DIR RELATIVE ${CMAKE_SOURCE_DIR} "libft/*.c")
add_library(libft STATIC ${libft_DIR})
add_executable(asm_dev asm_f/srcs/main.c asm_f/includes/asm.h
        asm_f/includes/op.h asm_f/srcs/parsing_name_and_comment.c
        asm_f/srcs/exit.c asm_f/srcs/parse_code.c asm_f/srcs/parsing_name_and_comment2.c
        asm_f/srcs/other.c asm_f/srcs/bytecode.c asm_f/srcs/things_to_bytecode.c
        asm_f/srcs/del.c asm_f/srcs/label.c asm_f/srcs/parser_error.c
        asm_f/srcs/parser_other.c asm_f/srcs/parse_arg.c asm_f/srcs/parse_args.c
        asm_f/srcs/parser_checks.c
        asm_f/srcs/label2.c)
target_link_libraries(asm_dev libft)