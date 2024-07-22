#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <cstdint>

extern int ROW, COL;
extern int SN_ROW, SN_COL;

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
    uint32_t length;

    Snake();

    void changeDir(uint8_t direction);
    void render();
    void move();
    void lengthen();
};


#endif
