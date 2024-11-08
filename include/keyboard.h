#ifndef KEYBOARD_H
#define KEYBOARD_H

// Função para inicializar o teclado
void keyboardInit();

// Função para restaurar as configurações do terminal
void keyboardDestroy();

// Função para verificar se alguma tecla foi pressionada
int keyhit();

// Função para ler a tecla pressionada
int readch();

// Função para verificar se uma tecla específica foi pressionada
int isKeyPressed(int key);

#endif // KEYBOARD_H
