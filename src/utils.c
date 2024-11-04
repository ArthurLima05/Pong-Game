#include "../include/utils.h"
#include <ncurses.h>
#include <unistd.h>

void clearScreen()
{
    clear(); // Limpa a tela
}

void delay(int milliseconds)
{
    usleep(milliseconds * 10); // Pausa a execução por um número de milissegundos
}