#include "snake.h"
#include <cassert>

int ROW, COL;
int DB_SN_ROW, DB_SN_COL;
int DB_SN_LENGTH;

int GROWTH_VALUE = 3;

void printBox(uint16_t row, uint16_t col, uint8_t color) {
    std::cout << "\033[" << row << ";" << col << "H";
    if (color == RED) std::cout << "\033[41m";
    else if (color == GREEN) std::cout << "\033[42m";
    else std::cout << "\033[40m";
    std::cout << " ";
    std::cout << "\033[0m";
    std::cout << "\033[?25l";
}

// ********** | NODE METHODS | ********** //
void Node::print() {
    printBox(m_row, m_col);
}

void Node::deleteAllNext(Node* p) {
    while (p != nullptr) {
        Node* next = p->next;
        delete p;
        p = next;
    }
}

// ********** | POSITIONS METHODS | ********** //
Positions::Positions()
: head{new Node{static_cast<uint16_t>(ROW/2), static_cast<uint16_t>(COL/2)}}
, length(5)
, BoolMatrix(ROW, std::vector<bool>(COL, false))
{}


void Positions::printPositions() {
    Node* n = head, *prev;
    for (int i = 0; i < length && n != nullptr; ++i, n=n->next) {
        n->print();
        prev = n;
    }
    std::cout << std::flush;

    if (n != nullptr && n != head) {
        if (n->next == nullptr) {
            BoolMatrix[n->m_row][n->m_col] = false;
            prev->next = nullptr;
            delete n;
        } else {
            assert(false);
            prev->next = nullptr;
            Node::deleteAllNext(n);
        }
    }


    DB_SN_ROW = head->m_row; // NOTE: DEBUG INFO
    DB_SN_COL = head->m_col;
}

bool Positions::pushOnHead(uint16_t row, uint16_t col) {
    if (BoolMatrix[row][col] == true) {
        return true;
    }
    head = new Node{row, col, head};
    BoolMatrix[row][col] = true;
    return false;
}

std::pair<uint16_t,uint16_t> Positions::getHeadRowCol() {
    return {head->m_row, head->m_col};
}

// NOTE: DEBUG
void Positions::debug_getLength() {
    int len = 0;
    for (Node* p = head; p != nullptr; p=p->next) {
        ++len;
    }
    DB_SN_LENGTH = len;
}



// ********** | PELLET METHODS | ********** //
void Pellet::print() {
    printBox(row, col, GREEN);
}

bool Pellet::operator<(const Pellet other) const {
    return (this->row != other.row) ? this->row < other.row : this->col < other.col;
}


// ********** | SNAKE METHODS | ********** //
Snake::Snake()
: positions()
, dir(RIGHT)
, gen(rd())
, row_dist(1, ROW)
, col_dist(1, COL)
{
    randomizePellet();
}

void Snake::render() {
    renderPellets();
    positions.printPositions();
    // NOTE: DEBUG:
    positions.debug_getLength();
}

void Snake::changeDir(uint8_t direction) {
    // Prevents direction change in opposite directions
    // Works since up and down are 0 and 1 and left and right are 2 and 3
    if (!(dir <= 1 && direction <= 1) && !(dir >= 2 && direction >= 2))
        dir = direction;
}


// TODO: Update this function to push a Node onto positions
// and update positions to delete last element not within length
bool Snake::moveHead() {
    auto [row, col] = positions.getHeadRowCol();
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
    detectPelletCollision(row, col);
    return positions.pushOnHead(row, col);
}


void Snake::lengthen() {
    positions.increaseLength(GROWTH_VALUE);
}


// ********** | SNAKE PELLET METHODS | ********** //
void Snake::createPellet(uint16_t row, uint16_t col) {
    pellets.emplace(row, col);
}

void Snake::randomizePellet() {
    uint16_t r_row = row_dist(gen);
    uint16_t r_col = col_dist(gen);
    createPellet(r_row, r_col);
}

void Snake::renderPellets() {
    for (Pellet p : pellets) {
        p.print();
    }
}

void Snake::detectPelletCollision(uint16_t row, uint16_t col) {
    for (auto it=pellets.begin();it!=pellets.end();++it) {
        if (it->row == row && it->col == col) {
            lengthen();
            pellets.erase(it);
            randomizePellet();
            break;
        }
    }
}
