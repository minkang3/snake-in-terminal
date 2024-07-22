#include "snake.h"

int ROW, COL;
int test = 10;
int SN_ROW, SN_COL;

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
    SN_ROW = row;
    SN_COL = col;
}

void Snake::changeDir(uint8_t direction) {
    dir = direction;
}


void Snake::move() {
    test = dir; // NOTE: Test line
    //SN_ROW = row;
    //SN_COL = col;
    switch (dir) {
        case UP:
            row = (((row - 1 - 1) % ROW) + ROW) % ROW + 1;
            break;
        case DOWN:
            row = (((row + 1 - 1) % ROW) + ROW) % ROW + 1;
            break;
        case LEFT:
            col = (((col - 1 - 1) % COL) + COL) % COL + 1;
            break;
        case RIGHT:
            col = (((col + 1 - 1) % COL) + COL) % COL + 1;
            break;
        default:
            throw "Invalid Direction";
            break;
    }
}
