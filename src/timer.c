#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

static struct timeval startTime;
static int intervalTime; // Intervalo de tempo em milissegundos
static unsigned long lastUpdateTime;

// Inicializa o temporizador com o intervalo em milissegundos
void timerInit(int valueMilliSec)
{
    gettimeofday(&startTime, NULL); // Captura o tempo inicial
    intervalTime = valueMilliSec;   // Define o intervalo de tempo
    lastUpdateTime = 0;
}

// Atualiza o temporizador, verificando o tempo decorrido
void timerUpdate()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL); // Captura o tempo atual

    unsigned long elapsedTime = (currentTime.tv_sec - startTime.tv_sec) * 1000 +
                                (currentTime.tv_usec - startTime.tv_usec) / 1000;

    if (elapsedTime - lastUpdateTime >= intervalTime)
    {
        lastUpdateTime = elapsedTime; // Atualiza o último tempo de verificação
    }
}

// Verifica se o tempo definido já passou
int timerTimeOver()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    unsigned long elapsedTime = (currentTime.tv_sec - startTime.tv_sec) * 1000 +
                                (currentTime.tv_usec - startTime.tv_usec) / 1000;

    if (elapsedTime - lastUpdateTime >= intervalTime)
    {
        return 1;
    }

    return 0;
}

// Exibe o tempo atual (para depuração)
void timerPrint()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    unsigned long elapsedTime = (currentTime.tv_sec - startTime.tv_sec) * 1000 +
                                (currentTime.tv_usec - startTime.tv_usec) / 1000;

    printf("Time elapsed: %lu ms\n", elapsedTime);
}

// Finaliza o temporizador (opcional)
void timerDestroy()
{
    startTime.tv_sec = 0;
    startTime.tv_usec = 0;
    intervalTime = 0;
    lastUpdateTime = 0;
}
