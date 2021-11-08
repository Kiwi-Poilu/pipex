cmake_minimum_required(VERSION 3.20)
project(pipex C)

set(CMAKE_C_STANDARD 99)

add_executable(pipex srcs/main.c srcs/ft_split.c srcs/get_next_line.c srcs/get_next_line_utils.c)
