#include "snake.h"

int ROW, COL;
int SN_ROW, SN_COL;

void printBox(uint16_t row, uint16_t col) {
    std::cout << "\033[" << row << ";" << col << "H";
    std::cout << "\033[41m";
    std::cout << " ";
    std::cout << "\033[0m";
    std::cout << "\033[?25l";
    std::cout << std::flush;
}

// ********** | NODE METHODS | ********** //
void Node::print() {
    printBox(m_row, m_col);
}

// ********** | POSITIONS METHODS | ********** //
Positions::Positions()
: head{new Node{static_cast<uint16_t>(ROW/2), static_cast<uint16_t>(COL/2)}}
, length(1)
{}


void Positions::printPositions() {
    for (Node* n = head; n != nullptr; n=n->next) {
        n->print();
    }
    SN_ROW = head->m_row; // NOTE: TEST LINE
    SN_COL = head->m_col;
}


void Positions::pushOnHead(uint16_t row, uint16_t col) {
    head = new Node{row, col, head};
}


std::pair<uint16_t,uint16_t> Positions::getHeadRowCol() {
    return {head->m_row, head->m_col};
}



// ********** | SNAKE METHODS | ********** //
Snake::Snake()
: positions()
, dir(RIGHT)
{}

void Snake::render() {
    positions.printPositions();
}

void Snake::changeDir(uint8_t direction) {
    dir = direction;
}


// TODO: Update this function to push a Node onto positions
// and update positions to delete last element not within length
void Snake::moveHead() {
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
    positions.pushOnHead(row, col);
}
