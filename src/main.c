#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <unistd.h>

#define PADDLE_WIDTH 1
#define PADDLE_HEIGHT 4
#define BALL_SIZE 1
#define WINNING_SCORE 7

int *leftPaddleY, *rightPaddleY;
int *ballX, *ballY, *ballDirectionX, *ballDirectionY;
int *leftScore, *rightScore;
int *gameEnded;

void drawGame()
{
    screenClear();
    screenDrawBorders();

    screenSetColor(BLUE, BLACK);
    int leftPaddleHeight = (*leftScore >= 4) ? 2 : PADDLE_HEIGHT; // Reduz o tamanho do paddle para 2 se a pontuação for >= 4
    for (int i = 0; i < leftPaddleHeight; i++)
    {
        screenGotoxy(2, *leftPaddleY + i);
        printf("|");
    }

    screenSetColor(RED, BLACK);
    int rightPaddleHeight = (*rightScore >= 4) ? 2 : PADDLE_HEIGHT; // Reduz o tamanho do paddle para 2 se a pontuação for >= 4
    for (int i = 0; i < rightPaddleHeight; i++)
    {
        screenGotoxy(MAXX - 2, *rightPaddleY + i);
        printf("|");
    }

    screenSetColor(WHITE, BLACK);
    screenGotoxy(*ballX, *ballY);
    printf("O");

    screenGotoxy(12, MINY);
    printf("Score Left: %d", *leftScore);
    screenGotoxy((3 * MAXX / 4) - 5, MINY);
    printf("Score Right: %d", *rightScore);

    // Exibir mensagem de vitória conforme o jogador
    if (*gameEnded)
    {
        int messagePosX = *leftScore == WINNING_SCORE ? MAXX / 4 : 3 * MAXX / 4;
        screenGotoxy(messagePosX - 5, MAXY / 2); // Ajusta a posição de acordo com o vencedor
        printf("Player %s Wins! Press 'r' to restart", *leftScore == WINNING_SCORE ? "Left" : "Right");
    }

    screenUpdate();
}

void resetGame()
{
    *leftPaddleY = 10;
    *rightPaddleY = 10;
    *ballX = 40;
    *ballY = 12;
    *ballDirectionX = 1;
    *ballDirectionY = 1;
    *leftScore = 0;
    *rightScore = 0;
    *gameEnded = 0;
}

void updateBall()
{
    if (*gameEnded)
        return;

    // Movimento da bola
    *ballX += *ballDirectionX;
    *ballY += *ballDirectionY;

    // Verifica colisões com as bordas superior e inferior
    if (*ballY <= MINY + 1 || *ballY >= MAXY - 1)
    {
        *ballDirectionY *= -1;
    }

    // Colisões com os paddles
    if (*ballX == 3 && *ballY >= *leftPaddleY && *ballY < *leftPaddleY + PADDLE_HEIGHT)
    {
        *ballDirectionX *= -1;
    }

    if (*ballX == MAXX - 3 && *ballY >= *rightPaddleY && *ballY < *rightPaddleY + PADDLE_HEIGHT)
    {
        *ballDirectionX *= -1;
    }

    // Verifica se a bola passou das bordas
    if (*ballX <= MINX)
    {
        (*rightScore)++;
        if (*rightScore >= WINNING_SCORE)
        {
            *gameEnded = 1;
        }
        *ballX = 40;
        *ballY = 12;
        *ballDirectionX = 1;
    }

    if (*ballX >= MAXX)
    {
        (*leftScore)++;
        if (*leftScore >= WINNING_SCORE)
        {
            *gameEnded = 1;
        }
        *ballX = 40;
        *ballY = 12;
        *ballDirectionX = -1;
    }
}

void updatePaddles()
{
    if (keyhit())
    {
        char key = readch();

        if (*gameEnded && key == 'r')
        {
            resetGame();
            return;
        }

        if ((key == 'w' || key == 'W') && *leftPaddleY > MINY + 1)
        {
            (*leftPaddleY)--;
        }
        if ((key == 's' || key == 'S') && *leftPaddleY < MAXY - (*leftScore >= 4 ? 2 : PADDLE_HEIGHT)) // Considera a altura do paddle ao mover
        {
            (*leftPaddleY)++;
        }

        if ((key == 'i' || key == 'I') && *rightPaddleY > MINY + 1)
        {
            (*rightPaddleY)--;
        }
        if ((key == 'k' || key == 'K') && *rightPaddleY < MAXY - (*rightScore >= 4 ? 2 : PADDLE_HEIGHT)) // Considera a altura do paddle ao mover
        {
            (*rightPaddleY)++;
        }
    }
}

int main()
{
    leftPaddleY = malloc(sizeof(int));
    rightPaddleY = malloc(sizeof(int));
    ballX = malloc(sizeof(int));
    ballY = malloc(sizeof(int));
    ballDirectionX = malloc(sizeof(int));
    ballDirectionY = malloc(sizeof(int));
    leftScore = malloc(sizeof(int));
    rightScore = malloc(sizeof(int));
    gameEnded = malloc(sizeof(int));

    // Inicializar variáveis do jogo
    resetGame();

    screenInit(1);
    keyboardInit();
    timerInit(50); // O intervalo de 50ms vai atualizar o jogo

    while (1)
    {
        // Verifica se o tempo passou
        if (timerTimeOver())
        {
            timerUpdate(); // Atualiza o temporizador para o próximo ciclo

            // Atualiza o movimento da bola e os paddles, desenha a tela
            updateBall();
            updatePaddles();
            drawGame(); // Desenha o jogo na tela
        }
        usleep(50000); // Espera por 50ms antes de continuar o loop, garantindo atualização contínua
    }

    // Liberar memória alocada
    free(leftPaddleY);
    free(rightPaddleY);
    free(ballX);
    free(ballY);
    free(ballDirectionX);
    free(ballDirectionY);
    free(leftScore);
    free(rightScore);
    free(gameEnded);

    keyboardDestroy();
    screenDestroy();
    return 0;
}
