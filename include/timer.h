#ifndef __TIMER_H__
#define __TIMER_H__

void timerInit(int valueMilliSec);

void timerUpdate();

int timerTimeOver();

void timerPrint();

void timerDestroy();

#endif /* __TIMER_H__ */
