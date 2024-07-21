cmake_minimum_required(VERSION 3.29)

project(terminal_game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FILES
    src/gameloop.h
    src/gameloop.cpp
)

add_executable(main ${FILES} src/main.cpp)
