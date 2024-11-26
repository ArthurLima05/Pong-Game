#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboardInit();

void keyboardDestroy();

int keyhit();

int readch();

int isKeyPressed(int key);

#endif // KEYBOARD_H
