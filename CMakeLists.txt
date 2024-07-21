cmake_minimum_required(VERSION 3.29)

project(terminal_game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(FILES
    src/gameloop.h
    src/gameloop.cpp
    src/snake.h
    src/snake.cpp
)

add_executable(main ${FILES} src/main.cpp)

target_link_libraries(main ${CURSES_LIBRARIES})
