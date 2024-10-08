#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <set>

extern int ROW, COL;
extern int DB_SN_ROW, DB_SN_COL;
extern int DB_SN_LENGTH;

extern int GROWTH_VALUE;

enum directions {
    UP    = 0,
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3
};

enum colors {
    RED = 0,
    GREEN = 1
};

void printBox(uint16_t row, uint16_t col, uint8_t color=RED);

struct Node {
    uint16_t m_row, m_col;
    Node* next = nullptr;

    void print();
    static void deleteAllNext(Node* p);
};

struct Positions {
    Node* head;
    uint32_t length;
    // TODO: Implement a matrix of bools to detect collision with itself
    std::vector<std::vector<bool>> BoolMatrix;

    Positions();

    void printPositions();
    bool pushOnHead(uint16_t row, uint16_t col);
    void increaseLength(uint32_t len) { length += len; }


    std::pair<uint16_t,uint16_t> getHeadRowCol();
    
    // NOTE: DEBUG
    void debug_getLength();
};

struct Pellet {
    uint16_t row, col;

    Pellet(uint16_t row, uint16_t col) 
    : row(row), col(col) {}

    void print();

    bool operator<(const Pellet other) const;
};

struct Snake {
    Positions positions;
    uint8_t dir;
    //std::vector<Pellet> pellets;
    std::set<Pellet> pellets;

    // Used for randomly generating pellet locations
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> row_dist;
    std::uniform_real_distribution<> col_dist;

    Snake();

    void changeDir(uint8_t direction);
    void render();
    bool moveHead();
    void lengthen();

    // Pellets
    void createPellet(uint16_t row, uint16_t col);
    void randomizePellet();
    void renderPellets();

    // TODO: DETECT COLLISION WITH PELLETS
    void detectPelletCollision(uint16_t row, uint16_t col);
};


#endif
