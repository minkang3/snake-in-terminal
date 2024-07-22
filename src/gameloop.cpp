#include "gameloop.h"
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>

extern int test;


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
    timeout(0);
}


void handleResize(int sig) {
    if (sig == SIGWINCH) {
        initVars();
    }
}


void processInput(Snake &snake) {
    int ch = getch();

    switch (ch) {
        case 'w':
            snake.changeDir(UP);
            //test++;
            break;
        case 'a':
            snake.changeDir(LEFT);
            break;
        case 's':
            snake.changeDir(DOWN);
            break;
        case 'd':
            snake.changeDir(RIGHT);
            break;
        default:
            break;
    }
}


void clearScreen() {
    std::cout << "\033c";
}


void printGame() {
    std::cout << "\n\n   " << ROW << ", " << COL << " " << test << std::endl;
    std::cout << "   " << SN_ROW << ", " << SN_COL << std::endl;
}


void loop() {
    signal(SIGWINCH, handleResize);

    init_ncurses();
    initVars();
    Snake snake;
    while (1) {
        processInput(snake);
        clearScreen();
        printGame();
        snake.move();
        snake.render();
        
        if (snake.dir == UP || snake.dir == DOWN)
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
