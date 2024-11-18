#include "keyboard.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_KEYS 256 // Total de teclas que podemos monitorar

static struct termios old_tio, new_tio; // Configurações do terminal
static int keyState[NUM_KEYS] = {0};    // Array para armazenar o estado das teclas

// Inicializa o teclado
void keyboardInit()
{
    tcgetattr(STDIN_FILENO, &old_tio); // Salva as configurações atuais
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);        // Desativa o buffering e o echo
    new_tio.c_cc[VMIN] = 1;                     // Lê 1 byte por vez
    new_tio.c_cc[VTIME] = 0;                    // Sem timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio); // Aplica as novas configurações
}

// Restaura as configurações do terminal
void keyboardDestroy()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio); // Restaura as configurações anteriores
}

// Função para verificar se alguma tecla foi pressionada
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int keyhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);        // Desabilita buffering e echo
    newt.c_cc[VMIN] = 1;                     // Lê 1 byte por vez
    newt.c_cc[VTIME] = 0;                    // Sem timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Aplica as novas configurações

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar(); // Lê a tecla pressionada

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura configurações do terminal

    if (ch != EOF)
    {
        keyState[ch] = 1; // Marca a tecla como pressionada
        return 1;
    }
    return 0;
}

// Lê a tecla pressionada
int readch()
{
    char ch = getchar(); // Lê a tecla pressionada
    keyState[ch] = 0;    // Marca a tecla como não pressionada
    return ch;
}

// Função para verificar se uma tecla específica foi pressionada
int isKeyPressed(int key)
{
    return keyState[key]; // Retorna 1 se a tecla foi pressionada, 0 caso contrário
}