#include <stdio.h>
#include <unistd.h>
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))

int main()
{
    float position = 0; // Posición inicial
    float velocity = 1; // Velocidad de la partícula

    int totalTime = 10; // Número total de pasos de tiempo
    int delay = 100000; // Retraso en microsegundos entre actualizaciones (para sistemas Unix)
    float i = 0;
    float j = 0;

    for (int time = 0; time < totalTime; time++)
    {
        printf("\x1b[2J");
        gotoxy(0, 0);
        for (int i = 0; i < position; i++)
        {
            gotoxy(i, i);
            printf(".");
        }
        position += velocity;
        usleep(delay);
    }
    return 0;
}