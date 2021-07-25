cmake_minimum_required(VERSION 3.19)
project(pgbooster C)

set(CMAKE_C_STANDARD 11)

add_executable(pgbooster src/pgbooster.c src/log.c src/log.h src/config.c src/config.h)