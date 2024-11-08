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

int leftPaddleY = 10, rightPaddleY = 10;
int ballX = 40, ballY = 12;
int ballDirectionX = 1, ballDirectionY = 1;
int leftScore = 0, rightScore = 0;
int gameEnded = 0;

void drawGame()
{
    screenClear();
    screenDrawBorders();

    screenSetColor(BLUE, BLACK);
    for (int i = 0; i < PADDLE_HEIGHT; i++)
    {
        screenGotoxy(2, leftPaddleY + i);
        printf("|");
    }

    screenSetColor(RED, BLACK);
    for (int i = 0; i < PADDLE_HEIGHT; i++)
    {
        screenGotoxy(MAXX - 2, rightPaddleY + i);
        printf("|");
    }

    screenSetColor(WHITE, BLACK);
    screenGotoxy(ballX, ballY);
    printf("O");

    screenGotoxy(12, MINY);
    printf("Score Left: %d", leftScore);
    screenGotoxy((3 * MAXX / 4) - 5, MINY);
    printf("Score Right: %d", rightScore);

    // Exibir mensagem de vitória conforme o jogador
    if (gameEnded)
    {
        int messagePosX = leftScore == WINNING_SCORE ? MAXX / 4 : 3 * MAXX / 4;
        screenGotoxy(messagePosX - 5, MAXY / 2); // Ajusta a posição de acordo com o vencedor
        printf("Player %s Wins! Press 'r' to restart", leftScore == WINNING_SCORE ? "Left" : "Right");
    }

    screenUpdate();
}

void resetGame()
{
    leftPaddleY = 10;
    rightPaddleY = 10;
    ballX = 40;
    ballY = 12;
    ballDirectionX = 1;
    ballDirectionY = 1;
    leftScore = 0;
    rightScore = 0;
    gameEnded = 0;
}

void updateBall()
{
    if (gameEnded)
        return;

    ballX += ballDirectionX;
    ballY += ballDirectionY;

    if (ballY <= MINY + 1 || ballY >= MAXY - 1)
    {
        ballDirectionY *= -1;
    }

    if (ballX == 3 && ballY >= leftPaddleY && ballY < leftPaddleY + PADDLE_HEIGHT)
    {
        ballDirectionX *= -1;
    }

    if (ballX == MAXX - 3 && ballY >= rightPaddleY && ballY < rightPaddleY + PADDLE_HEIGHT)
    {
        ballDirectionX *= -1;
    }

    if (ballX <= MINX)
    {
        rightScore++;
        if (rightScore >= WINNING_SCORE)
        {
            gameEnded = 1;
        }
        ballX = 40;
        ballY = 12;
        ballDirectionX = 1;
    }

    if (ballX >= MAXX)
    {
        leftScore++;
        if (leftScore >= WINNING_SCORE)
        {
            gameEnded = 1;
        }
        ballX = 40;
        ballY = 12;
        ballDirectionX = -1;
    }
}

void updatePaddles()
{
    if (keyhit())
    {
        char key = readch();

        if (gameEnded && key == 'r')
        {
            resetGame();
            return;
        }

        if ((key == 'w' || key == 'W') && leftPaddleY > MINY + 1)
        {
            leftPaddleY--;
        }
        if ((key == 's' || key == 'S') && leftPaddleY < MAXY - PADDLE_HEIGHT)
        {
            leftPaddleY++;
        }

        if ((key == 'i' || key == 'I') && rightPaddleY > MINY + 1)
        {
            rightPaddleY--;
        }
        if ((key == 'k' || key == 'K') && rightPaddleY < MAXY - PADDLE_HEIGHT)
        {
            rightPaddleY++;
        }
    }
}

int main()
{
    screenInit(1);
    keyboardInit();
    timerInit(50);

    while (1)
    {
        if (timerTimeOver() == 1)
        {
            timerUpdate();
            updatePaddles();
            updateBall();
            drawGame();
        }
    }

    keyboardDestroy();
    screenDestroy();
    return 0;
}
