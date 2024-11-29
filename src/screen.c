#include "screen.h"

void screenDrawBorders()
{
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    screenBoxEnable();

    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);

    for (int i = MINX + 1; i < MAXX; i++)
    {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }

    screenGotoxy(MAXX, MINY);
    printf("%c", BOX_UPRIGHT);

    for (int i = MINY + 1; i < MAXY; i++)
    {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    screenGotoxy(MINX, MAXY);
    printf("%c", BOX_DWNLEFT);

    for (int i = MINX + 1; i < MAXX; i++)
    {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }

    screenGotoxy(MAXX, MAXY);
    printf("%c", BOX_DWNRIGHT);

    screenBoxDisable();
}

void screenInit(int drawBorders)
{
    screenClear();
    if (drawBorders)
    {
        screenDrawBorders();
    }
    screenHomeCursor();
    screenHideCursor();
}

void screenDestroy()
{
    printf("%s[0;39;49m", ESC);
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

void screenGotoxy(int x, int y)
{
    if (x < MINX)
        x = MINX;
    if (x > MAXX)
        x = MAXX;
    if (y < MINY)
        y = MINY;
    if (y > MAXY)
        y = MAXY;

    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}

void screenSetColor(screenColor fg, screenColor bg)
{
    char atr[] = "[0;";

    if (fg > LIGHTGRAY)
    {
        atr[1] = '1';
        fg -= 8;
    }

    printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
}
