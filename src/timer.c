#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

static struct timeval startTime;
static int intervalTime;
static unsigned long lastUpdateTime;

void timerInit(int valueMilliSec)
{
    gettimeofday(&startTime, NULL);
    intervalTime = valueMilliSec;
    lastUpdateTime = 0;
}

void timerUpdate()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    unsigned long elapsedTime = (currentTime.tv_sec - startTime.tv_sec) * 1000 +
                                (currentTime.tv_usec - startTime.tv_usec) / 1000;

        if (elapsedTime - lastUpdateTime >= intervalTime)
    {
        lastUpdateTime = elapsedTime;
    }
}

int timerTimeOver()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    unsigned long elapsedTime = (currentTime.tv_sec - startTime.tv_sec) * 1000 +
                                (currentTime.tv_usec - startTime.tv_usec) / 1000;

    if (elapsedTime - lastUpdateTime >= intervalTime)
    {
        lastUpdateTime = elapsedTime;
        return 1;
    }

    return 0;
}

void timerPrint()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    unsigned long elapsedTime = (currentTime.tv_sec - startTime.tv_sec) * 1000 +
                                (currentTime.tv_usec - startTime.tv_usec) / 1000;

    printf("Time elapsed: %lu ms\n", elapsedTime);
}

void timerDestroy()
{
    startTime.tv_sec = 0;
    startTime.tv_usec = 0;
    intervalTime = 0;
    lastUpdateTime = 0;
}
