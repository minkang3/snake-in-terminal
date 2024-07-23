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

void printBox(uint16_t row, uint16_t col);

struct Node {
    uint16_t m_row, m_col;
    Node* next = nullptr;

    void print();
};

struct Positions {
    Node* head;
    uint32_t length;

    Positions();

    void printPositions();
    void pushOnHead(uint16_t row, uint16_t col);
    std::pair<uint16_t,uint16_t> getHeadRowCol();
};

struct Snake {
    Positions positions;
    uint8_t dir;

    Snake();

    void changeDir(uint8_t direction);
    void render();
    void moveHead();
    void lengthen();
};


#endif
