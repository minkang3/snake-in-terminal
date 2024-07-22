#include "snake.h"

int ROW, COL;
int test = 10;

void printBox() {
    std::cout << "\033[41m";
    std::cout << " ";
    std::cout << "\033[0m";
    std::cout << "\033[?25l";
    std::cout << std::flush;
}

Snake::Snake()
: row(ROW/2), col(COL/2), dir(RIGHT) {}

void Snake::render() {
    std::cout << "\033[" << row << ";" << col << "H";
    printBox();
}

void Snake::changeDir(uint8_t direction) {
    dir = direction;
}

void Snake::move() {
    test = dir;
    switch (dir) {
        case UP:
            row = (row - 1) % ROW;
            break;
        case DOWN:
            row = (row + 1) % ROW;
            break;
        case LEFT:
            col = (col - 1) % COL;
            break;
        case RIGHT:
            col = (col + 1) % COL;
            //test = dir;
            break;
        default:
            col = (col + 1) % COL;
            break;
    }
}
