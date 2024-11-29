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
    screenSetColor(BLUE, BLACK);
    int leftPaddleHeight = (*leftScore >= 4) ? 2 : PADDLE_HEIGHT;
    for (int i = 0; i < leftPaddleHeight; i++)
    {
        screenGotoxy(2, *leftPaddleY + i);
        printf("|");
        printf("|");
    }

    screenSetColor(WHITE, BLACK);
    screenGotoxy(*ballX, *ballY);
    printf("O");

    screenGotoxy(12, MINY);
    printf("Score Left: %d", *leftScore);
    screenGotoxy((3 * MAXX / 4) - 5, MINY);
    printf("Score Right: %d", *rightScore);

    if (*gameEnded)
    {
        int messagePosX = *leftScore == WINNING_SCORE ? MAXX / 4 : 3 * MAXX / 4;
        screenGotoxy(messagePosX - 5, MAXY / 2);
        printf("Player %s Wins! Press 'r' to restart", *leftScore == WINNING_SCORE ? "Left" : "Right");
    }
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

void updateBall() {
    if (*gameEnded)
        return;

    *ballX += *ballDirectionX;
    *ballY += *ballDirectionY;

    if (*ballY <= MINY + 1 || *ballY >= MAXY - 1) {
        *ballDirectionY *= -1;
    }

    if (*ballX == 3 && *ballY >= *leftPaddleY && *ballY < *leftPaddleY + PADDLE_HEIGHT) {
        *ballDirectionX *= -1;

        int paddleMiddle = *leftPaddleY + PADDLE_HEIGHT / 2;
        int ballRelativeY = *ballY - paddleMiddle;

        *ballDirectionY = ballRelativeY / 2;
    }

    if (*ballX == MAXX - 3 && *ballY >= *rightPaddleY && *ballY < *rightPaddleY + PADDLE_HEIGHT) {
        *ballDirectionX *= -1;

        int paddleMiddle = *rightPaddleY + PADDLE_HEIGHT / 2;
        int ballRelativeY = *ballY - paddleMiddle;

        *ballDirectionY = ballRelativeY / 2;
    }

    if (*ballX <= MINX) {
        (*rightScore)++;
        if (*rightScore >= WINNING_SCORE) {
            *gameEnded = 1;
        }
        *ballX = 40;
        *ballY = 12;
        *ballDirectionX = 1;
    }

    if (*ballX >= MAXX) {
        (*leftScore)++;
        if (*leftScore >= WINNING_SCORE) {
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
        if ((key == 's' || key == 'S') && *leftPaddleY < MAXY - (*leftScore >= 4 ? 2 : PADDLE_HEIGHT))
        {
            (*leftPaddleY)++;
        }

        if ((key == 'i' || key == 'I') && *rightPaddleY > MINY + 1)
        {
            (*rightPaddleY)--;
        }
        if ((key == 'k' || key == 'K') && *rightPaddleY < MAXY - (*rightScore >= 4 ? 2 : PADDLE_HEIGHT))
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

    resetGame();
    screenInit(0);
    screenDrawBorders();
    keyboardInit();
    timerInit(1);

    while (1)
    {
        if (timerTimeOver())
        {
            timerUpdate();

            updateBall();
            updatePaddles();
            drawGame();
        }
        usleep(1);
    }

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
