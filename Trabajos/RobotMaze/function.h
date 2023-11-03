#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

// Variables creadas con static
void cera - mangel_robot()
{
    typedef enum
    {
        CHECK_SIDE1,
        CHECK_SIDE2,
        CHECK_FRONT,
        CHECK_BACK,
        CHECK_ALL
    } STATE;
    static STATE state = CHECK_FRONT; // Definir el estado en una sola linea.
    // Testing_Maze();
    if (TRUE)
    {
        switch (state)
        {
        case CHECK_FRONT:
            if (Is_There_Wall(CERA - MANGEL))
            {
                Robot(CERA - MANGEL, CLOCK_WISE);
                state = CHECK_SIDE1;
            }
            else
            {
                Forward(CERA - MANGEL);
                state = CHECK_FRONT;
            }
            break;
        case CHECK_SIDE1:
            if (Is_There_Wall(CERA - MANGEL))
            {
                Robot(CERA - MANGEL, COUNTER_CW);
                Robot(CERA - MANGEL, COUNTER_CW);
                state = CHECK_SIDE2;
            }
            else
            {
                Forward(CERA - MANGEL);
                state = CHECK_FRONT;
            }
            break;
        case CHECK_SIDE2:
            if (Is_There_Wall(CERA - MANGEL))
            {
                Robot(CERA - MANGEL, CLOCK_WISE);
                Robot(CERA - MANGEL, CLOCK_WISE);
                Robot(CERA - MANGEL, CLOCK_WISE);
                state = CHECK_BACK;
            }
            else
            {
                Forward(CERA - MANGEL);
                state = CHECK_FRONT;
            }
            break;
        case CHECK_BACK:
            if (Is_There_Wall(CERA - MANGEL))
            {
                state = CHECK_ALL;
            }
            else
            {
                Forward(CERA - MANGEL);
                state = CHECK_FRONT;
            }
            break;
        }
    }
    // Challenge_Was_Finished();
}