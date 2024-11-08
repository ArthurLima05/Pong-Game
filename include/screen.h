#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

#define ESC "\033"
#define NORMALTEXT "[0m"
#define CLEARSCREEN "[2J"

#define BOX_UPLEFT 0x6C
#define BOX_UPRIGHT 0x6B
#define BOX_ENABLE "(0"
#define BOX_DISABLE "(B"
#define BOX_DWNLEFT 0x6D
#define BOX_DWNRIGHT 0x6A
#define BOX_VLINE 0x78
#define BOX_HLINE 0x71

#define MINX 1
#define MINY 1
#define MAXX 80
#define MAXY 24

typedef enum
{
    BLACK,
    RED,
    GREEN,
    BROWN,
    BLUE,
    MAGENTA,
    CYAN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTRED,
    LIGHTGREEN,
    YELLOW,
    LIGHTBLUE,
    LIGHTMAGENTA,
    LIGHTCYAN,
    WHITE
} screenColor;

void screenGotoxy(int x, int y);

static inline void screenClear()
{
    printf("%s%s", ESC, CLEARSCREEN);
    screenGotoxy(0, 0);
}

static inline void screenUpdate()
{
    fflush(stdout);
}

void screenSetColor(screenColor fg, screenColor bg);

void screenInit(int drawBorders);

static inline void screenBoxEnable()
{
    printf("%s%s", ESC, BOX_ENABLE);
}

static inline void screenBoxDisable()
{
    printf("%s%s", ESC, BOX_DISABLE);
}
void screenDrawBorders();
void screenDestroy();
void screenHomeCursor();
void screenHideCursor();
void screenSetNormal();
void screenShowCursor();

#endif /* __SCREEN_H__ */
