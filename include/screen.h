#ifndef SCREEN_H
#define SCREEN_H

typedef enum
{
    BLACK = 0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
} ScreenColor;

void clearScreen();
void setColors(ScreenColor fg, ScreenColor bg);
void initScreen();
void endScreen();
void updateScreen();

#endif // SCREEN_H