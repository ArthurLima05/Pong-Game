// src/main.c
#include <ncurses.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/keyboard.h"

int main()
{
    // Inicializa a tela do ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // Habilita a captura das teclas especiais
    curs_set(0);
    timeout(100); // Tempo de espera para a entrada do teclado

    Ball ball;
    Paddle leftPaddle, rightPaddle;

    initializeGame(&ball, &leftPaddle, &rightPaddle);

    while (1)
    {
        processInput(&leftPaddle, &rightPaddle);      // Processa a entrada do usuário
        updateGame(&ball, &leftPaddle, &rightPaddle); // Atualiza a posição da bola e paddles
        renderGame(&ball, &leftPaddle, &rightPaddle); // Renderiza o jogo

        // Condição para sair do jogo (por exemplo, pressionar 'q')
        if (getch() == 'q')
        {
            break;
        }
    }

    endwin(); // Finaliza a tela do ncurses
    return 0;
}