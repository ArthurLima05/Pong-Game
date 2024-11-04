#ifndef GAME_H
#define GAME_H

typedef struct
{
    int x;      // Posição horizontal do paddle
    int y;      // Posição vertical do paddle
    int width;  // Largura do paddle
    int height; // Altura do paddle
} Paddle;

typedef struct
{
    int x, y;   // Posição da bola
    int dx, dy; // Direção da bola
} Ball;

void initializeGame(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle);
void updateGame(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle);
void renderGame(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle);
void processInput(Paddle *leftPaddle, Paddle *rightPaddle);

#endif // GAME_H