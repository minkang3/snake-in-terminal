#include "gameloop.h"

void clearScreen() {
    std::cout << "\033c";
}


void initLoop() {
    while (1) {
        clearScreen();
    }
}
