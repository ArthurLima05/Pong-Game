// keyboard.h
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <ncurses.h>
#include "../include/game.h"

void keyboardInit();
void keyboardDestroy();
int keyhit();
int readch();
void processInput(Paddle *leftPaddle, Paddle *rightPaddle);

#endif // KEYBOARD_H