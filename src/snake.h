#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <cstdint>

extern int ROW, COL;

enum directions {
    UP    = 0,
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3
};

void printBox();

struct Snake {
    uint16_t row, col;
    uint8_t dir;

    Snake();

    void changeDir(uint8_t direction);
    void render();
    void move();
};


#endif
