#include "../include/screen.h"
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#define ESC_SEQ "\033"
#define CURSOR_HIDE "[?25l"
#define CURSOR_SHOW "[?25h"
#define CLEAR_TERMINAL "[2J"
#define CURSOR_HOME "[H"

// Mover o cursor para a posição inicial
static inline void moveToHome()
{
    printf("%s%s", ESC_SEQ, CURSOR_HOME);
}

// Limpar a tela e mover o cursor para o início
static inline void clearTerminalScreen() // Renomeado para evitar conflito
{
    moveToHome();
    printf("%s%s", ESC_SEQ, CLEAR_TERMINAL);
}

// Mostrar o cursor no terminal
static inline void showCursor()
{
    printf("%s%s", ESC_SEQ, CURSOR_SHOW);
}

// Ocultar o cursor no terminal
static inline void hideCursor()
{
    printf("%s%s", ESC_SEQ, CURSOR_HIDE);
}

void initScreen()
{
    hideCursor();          // Oculta o cursor no início
    clearTerminalScreen(); // Limpa a tela no início
}

void endScreen()
{
    showCursor(); // Mostra o cursor antes de sair
}

void updateScreen()
{
}

void setColors(ScreenColor fg, ScreenColor bg)
{
    init_pair(1, fg, bg);  // Inicializa o par de cores
    attron(COLOR_PAIR(1)); // Usa o par de cores
}