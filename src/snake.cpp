#include "snake.h"
#include <cassert>

int ROW, COL;
int DB_SN_ROW, DB_SN_COL;
int DB_SN_LENGTH;

void printBox(uint16_t row, uint16_t col) {
    std::cout << "\033[" << row << ";" << col << "H";
    std::cout << "\033[41m";
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

void testDeleteAllNext() {
    Node* head = new Node{1, 1};
    for (int i = 0; i < 20; ++i) {
        head = new Node{1, 1, head};
    }
    Node::deleteAllNext(head);
    assert(head == nullptr);
}

// ********** | POSITIONS METHODS | ********** //
Positions::Positions()
: head{new Node{static_cast<uint16_t>(ROW/2), static_cast<uint16_t>(COL/2)}}
, length(5)
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
            prev->next = nullptr;
            delete n;
        } else {
            prev->next = nullptr;
            Node::deleteAllNext(n);
        }
    }


    DB_SN_ROW = head->m_row; // NOTE: DEBUG INFO
    DB_SN_COL = head->m_col;
}

void Positions::pushOnHead(uint16_t row, uint16_t col) {
    head = new Node{row, col, head};
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



// ********** | SNAKE METHODS | ********** //
Snake::Snake()
: positions()
, dir(RIGHT)
{}

void Snake::render() {
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


void Snake::lengthen() {
    positions.increaseLength(1);
}
