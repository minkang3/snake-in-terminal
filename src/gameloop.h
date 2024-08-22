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

// TODO:
// 1. Add score display
// 2. Add gameover screen
// 3. Handle game closing more gracefully (set all values back to normal, like hidden cursor)

