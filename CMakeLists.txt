cmake_minimum_required(VERSION 3.19.2)
project(Betriebssysteme)

set(CMAKE_CXX_STANDARD 23)

add_executable(praktikum04
        praktikum04/src/main.cpp
        praktikum04/src/MiniShell.cpp
        praktikum04/src/MiniShell.h)
