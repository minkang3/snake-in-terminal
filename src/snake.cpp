#include "snake.h"

void printBox() {
    std::cout << "\033[41m";
    std::cout << " ";
    std::cout << "\033[0m";
    std::cout << "\033[?25l";
    std::cout << std::flush;
}

Snake::Snake()
: row(ROW/2), col(COL/2) {}

void Snake::render() {
    std::cout << "\033[" << row << ";" << col << "H";
    printBox();
}

void Snake::move() {
    col = (col + 1) % COL;
}
