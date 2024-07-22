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

int SN_ROW, SN_COL;

void Snake::move() {
    test = dir;
    SN_ROW = row;
    SN_COL = col;
    switch (dir) {
        case UP:
            row = (((row - 1) % ROW) + ROW) % ROW;
            break;
        case DOWN:
            row = (((row + 1) % ROW) + ROW) % ROW;
            break;
        case LEFT:
            col = (((col - 1) % COL) + COL) % COL;
            break;
        case RIGHT:
            col = (((col + 1) % COL) + COL) % COL;
            break;
        default:
            throw "Invalid Direction";
            break;
    }
}
