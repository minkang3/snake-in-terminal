#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "snake.h"
#include <iostream>

extern int ROW, COL;
extern bool gameRunning;

void initVars();
void init_ncurses();
void handleResize(int sig);
void processInput(Snake&);
void clearScreen();
void printDebugInfo();
void loop();

#endif
