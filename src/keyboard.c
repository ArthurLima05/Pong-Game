#include "keyboard.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define NUM_KEYS 256

static struct termios old_tio, new_tio;
static int keyState[NUM_KEYS] = {0};

void keyboardInit()
{
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    new_tio.c_cc[VMIN] = 1;
    new_tio.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void keyboardDestroy()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

int keyhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (ch != EOF)
    {
        keyState[ch] = 1;
        return 1;
    }
    return 0;
}

int readch()
{
    char ch = getchar();
    keyState[ch] = 0;
    return ch;
}

int isKeyPressed(int key)
{
    return keyState[key];
}