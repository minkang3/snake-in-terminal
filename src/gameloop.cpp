#include "gameloop.h"
#include "snake.h"
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>

bool gameRunning;

void initVars() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    ROW = size.ws_row;
    COL = size.ws_col;
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
        case '=':
            snake.lengthen();
            break;
        case 'q':
            gameRunning = false;
            break;
        case 'p':
            snake.randomizePellet();
            break;
        default:
            break;
    }
}


void clearScreen() {
    std::cout << "\033c";
}


void printDebugInfo() {
    std::cout << "\033[" << 1 << ";" << 1 << "H";
    std::cout << "Height: " << ROW << ", Width: " << COL << " " << std::endl;
    std::cout << "\033[" << 2 << ";" << 1 << "H";
    std::cout << "Snake Pos: " << DB_SN_ROW << ", " << DB_SN_COL << std::endl;
    std::cout << "\033[" << 3 << ";" << 1 << "H";
    std::cout << "Snake Len: " << DB_SN_LENGTH << std::endl;
}


void loop() {
    signal(SIGWINCH, handleResize);

    init_ncurses();
    initVars();
    Snake snake;

    gameRunning = true;
    bool gameOver = false;
    
    while (gameRunning) {
        processInput(snake);
        clearScreen();
        printDebugInfo();
        gameOver = snake.moveHead();
        snake.render();
        
        gameRunning = !gameOver;

        if (snake.dir == UP || snake.dir == DOWN)
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
