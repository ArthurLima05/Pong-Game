#include "../include/keyboard.h"
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>
#include "../include/game.h"
#include <stdlib.h>

static struct termios initialSettings, newSettings;
static int peekCharacter = -1;

void keyboardInit()
{
    tcgetattr(0, &initialSettings);
    newSettings = initialSettings;
    newSettings.c_lflag &= ~ICANON;
    newSettings.c_lflag &= ~ECHO;
    newSettings.c_lflag &= ~ISIG;
    newSettings.c_cc[VMIN] = 1;
    newSettings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &newSettings);
}

void keyboardDestroy()
{
    tcsetattr(0, TCSANOW, &initialSettings);
}

int keyhit()
{
    unsigned char ch;
    int nread;

    if (peekCharacter != -1)
        return 1;

    newSettings.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &newSettings);
    nread = read(0, &ch, 1);
    newSettings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &newSettings);

    if (nread == 1)
    {
        peekCharacter = ch;
        return 1;
    }

    return 0;
}

int readch()
{
    char ch;

    if (peekCharacter != -1)
    {
        ch = peekCharacter;
        peekCharacter = -1;
        return ch;
    }

    read(0, &ch, 1);
    return ch;
}

void processInput(Paddle *leftPaddle, Paddle *rightPaddle)
{
    int ch = getch(); // Captura a entrada do teclado

    // Controla o paddle esquerdo com 'w' e 's'
    switch (ch)
    {
    case 'w':
        if (leftPaddle->y > 0)
        {
            leftPaddle->y--; // Move o paddle para cima
        }
        break;
    case 's':
        if (leftPaddle->y + leftPaddle->height < LINES)
        {
            leftPaddle->y++; // Move o paddle para baixo
        }
        break;

    // Controla o paddle direito com as setas
    case KEY_UP:
        if (rightPaddle->y > 0)
        {
            rightPaddle->y--; // Move o paddle direito para cima
        }
        break;
    case KEY_DOWN:
        if (rightPaddle->y + rightPaddle->height < LINES)
        {
            rightPaddle->y++; // Move o paddle direito para baixo
        }
        break;

    case 'q':
        exit(0); // Sai do jogo se 'q' for pressionado
        break;
    }
}