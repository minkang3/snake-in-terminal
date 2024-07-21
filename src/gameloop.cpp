#include "gameloop.h"
#include "snake.h"
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>

int ROW, COL;


void initVars() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    ROW = size.ws_row + 1;
    COL = size.ws_col + 1;
}


void init_ncurses() {
    initscr();
    cbreak();
    noecho();
}


void handleResize(int sig) {
    if (sig == SIGWINCH) {
        initVars();
    }
}


void processInput() {
    int ch = getch();

    std::cout << static_cast<char>(ch);
}


void clearScreen() {
    std::cout << "\033c";
}


void printGame() {
    std::cout << "\n\n\n\n        " << ROW << ", " << COL << std::endl;
}


void loop() {
    signal(SIGWINCH, handleResize);

    initVars();
    Snake snake;
    while (1) {
        processInput();
        clearScreen();
        printGame();
        snake.move();
        snake.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
