#ifndef GAMELOOP_H
#define GAMELOOP_H


#include <iostream>

extern int ROW, COL;

void initVars();
void init_ncurses();
void handleResize(int sig);
void processInput();
void clearScreen();
void printGame();
void loop();

#endif
