#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

typedef enum
{
    CHECK_ALL_WALLS,
    CHECK_AT_LEAST_ONE_WALL,
    CHECK_NO_WALLS
} STATE_INITIAL;

static STATE_INITIAL state_initial = CHECK_ALL_WALLS;

int There_Wall_Front()
{
    if (Is_There_Wall(CERA_DASH_MANGEL))
        return 1;
    return 0;
}
int There_Wall_Right()
{
    Sonar(CERA_DASH_MANGEL, CLOCK_WISE);
    if (Is_There_Wall(CERA_DASH_MANGEL))
        return 1;
    return 0;
}
int There_Wall_Left()
{
    Sonar(CERA_DASH_MANGEL, COUNTER_CW);
    if (Is_There_Wall(CERA_DASH_MANGEL))
        return 1;
    return 0;
}

void cera_dash_mangel_robot()
{
    if (TRUE)
    {
        switch (state_initial)
        {
        case CHECK_ALL_WALLS:
            if (There_Wall_Front() && There_Wall_Right() && There_Wall_Left()) // 1 1 1
            {
                // Rotamos 180 y vamos hacia adelante
                Robot(CERA_DASH_MANGEL, COUNTER_CW);
                Robot(CERA_DASH_MANGEL, COUNTER_CW);
                Forward(CERA_DASH_MANGEL);
            }
            else
            {
                state_initial = CHECK_AT_LEAST_ONE_WALL;
            }
            break;
        case CHECK_AT_LEAST_ONE_WALL:
            if (There_Wall_Front() || There_Wall_Right() || There_Wall_Left())
            {
                if (!There_Wall_Front() && There_Wall_Right() && There_Wall_Left()) // 0 1 1
                {
                    // Hacia adelante
                    Forward(CERA_DASH_MANGEL);
                }
                else if (There_Wall_Front() && !There_Wall_Right() && There_Wall_Left()) // 1 0 1
                {
                    // Rotamos hacia la derecha y avanzamos
                    Robot(CERA_DASH_MANGEL, CLOCK_WISE);
                    Forward(CERA_DASH_MANGEL);
                }
                else if (There_Wall_Front() && There_Wall_Right() && !There_Wall_Left()) // 1 1 0
                {
                    // Rotamos hacia la izquierda y avanzamos
                    Robot(CERA_DASH_MANGEL, COUNTER_CW);
                    Forward(CERA_DASH_MANGEL);
                }
                else if (There_Wall_Front() && !There_Wall_Right() && !There_Wall_Left()) // 1 0 0
                {
                    // RANDOM
                    srand(time(NULL));
                    int two_sides(rand() % 10) + 1;
                    // Rotamos hacia un lado de forma aleatoria y avanzamos
                    //Par: Izquierda, Impar: Derecha
                    if (two_sides % 2)
                    {
                        Robot(CERA_DASH_MANGEL, COUNTER_CW);
                        Forward(CERA_DASH_MANGEL);
                    }
                    else
                    {
                        Robot(CERA_DASH_MANGEL, CLOCK_WISE);
                        Forward(CERA_DASH_MANGEL);
                    }
                }
                else if (!There_Wall_Front() && (There_Wall_Right || There_Wall_Left))
                {
                    // RANDOM
                    srand(time(NULL));
                    int random_value = rand() % 2;
                    // De manera aleatorio se selecciona si seguir con el camino o girar por el hueco

                    if (There_Wall_Right() && random_value) // 0 1 0
                    {
                        // Rotamos hacia la izquierda y avanzamos
                        Robot(CERA_DASH_MANGEL, COUNTER_CW);
                        Forward(CERA_DASH_MANGEL);
                    }
                    else if (There_Wall_Left() && !random_value) // 0 0 1
                    {
                        // Rotamos hacia la derecha  y avanzamos
                        Robot(CERA_DASH_MANGEL, CLOCK_WISE);
                        Forward(CERA_DASH_MANGEL);
                    }
                    else
                    {
                        Forward(CERA_DASH_MANGEL);
                    }
                }
            }
            else
            {
                state_initial = CHECK_NO_WALLS;
            }
            break;
        case CHECK_NO_WALLS:
            if (!There_Wall_Front() && !There_Wall_Right() && !There_Wall_Left()) // 0 0 0
            {
                // RANDOM
                srand(time(NULL));
                int random_integer = (rand() % 3) + 1;
                // Rotamos de manera aleatoria hacia un lado y avanzamos
                // 3: Hacia adelante, 2: Hacia la derecha, 1: Hacia la izquierda

                if (random_integer % 3)
                {
                    if (random_integer % 2)
                    {
                        Robot(CERA_DASH_MANGEL, CLOCK_WISE);
                        Forward(CERA_DASH_MANGEL);
                    }
                    else
                    {
                        Robot(CERA_DASH_MANGEL, COUNTER_CW);
                        Forward(CERA_DASH_MANGEL);
                    }
                }
                else
                {
                    Forward(CERA_DASH_MANGEL);
                }
            }
            break;
        default:
            break;
        }
    }
}