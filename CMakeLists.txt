cmake_minimum_required(VERSION 3.19.2)
project(Betriebssysteme)

set(CMAKE_CXX_STANDARD 11)

add_executable(praktikum04
        praktikum04/src/main.cpp
        praktikum04/src/MiniShell.h
        praktikum04/src/MiniShell.cpp
)

add_executable(praktikum05
        praktikum05/src/main.cpp
        praktikum05/src/MiniShell.h
        praktikum05/src/MiniShell.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")
add_executable(praktikum06
        praktikum06/src/main.cpp
        praktikum06/src/Bot.cpp
        praktikum06/src/Bot.h
        praktikum06/src/Queue.cpp praktikum06/src/Queue.h)
