#ifndef __TIMER_H__
#define __TIMER_H__

// Inicializa o temporizador
void timerInit(int valueMilliSec);

// Atualiza o temporizador
void timerUpdate();

// Verifica se o tempo definido já passou
int timerTimeOver();

// Exibe o tempo atual para fins de debug
void timerPrint();

// Finaliza o temporizador (opcional)
void timerDestroy();

#endif /* __TIMER_H__ */
