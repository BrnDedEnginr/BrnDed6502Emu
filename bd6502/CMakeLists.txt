cmake_minimum_required(VERSION 3.28)
project(bd6502)

set(CMAKE_CXX_STANDARD 26)

add_executable(bd6502 main.cpp
        bd6502cpu.cpp
        bd6502cpu.h
        bd6502bus.cpp
        bd6502bus.h
        bd6502ram.cpp
        bd6502ram.h)
