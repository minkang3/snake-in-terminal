#ifndef SNAKE_H
#define SNAKE_H

#include "gameloop.h"
#include <cstdint>

void printBox();

struct Snake {
    uint16_t row, col;
    Snake();

    void render();
    void move();
};


#endif
