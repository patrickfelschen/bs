cmake_minimum_required (VERSION 3.8)
project ("Betriebssysteme")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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

add_executable(praktikum06
        praktikum06/src/main.cpp
        praktikum06/src/Bot.cpp
        praktikum06/src/Bot.h
        praktikum06/src/Queue.cpp
        praktikum06/src/Queue.h
)

add_executable(praktikum07
        praktikum07/src/main.cpp
        praktikum07/src/ListDir.cpp
        praktikum07/src/ListDir.h
)

add_executable(praktikum08
        praktikum08/src/main.cpp
)

