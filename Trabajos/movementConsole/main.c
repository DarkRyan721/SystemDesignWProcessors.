#include <stdio.h>
#include <unistd.h> // Para usleep en sistemas Unix

int main()
{
    float position = 0; // Posición inicial
    float velocity = 1; // Velocidad de la partícula

    int totalTime = 5; // Número total de pasos de tiempo
    int delay = 100000; // Retraso en microsegundos entre actualizaciones (para sistemas Unix)
    float i = 0;
    float j = 0;

    for (int time = 0; time < totalTime; time++)
    {
        // system("clear");
        //printf("\x1b[H");
        for (i = 0; i < position; i++)
        {
            printf(" ");
            for (float j = 0; j < i; j++)
                printf("\n");
        }

        printf("o");

        position += velocity;

        usleep(delay);
    }

    return 0;
}