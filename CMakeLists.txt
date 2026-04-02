cmake_minimum_required(VERSION 4.0)
project(structures C)

set(CMAKE_C_STANDARD 23)

add_executable(structures main.c
        dynamic_array.h)
