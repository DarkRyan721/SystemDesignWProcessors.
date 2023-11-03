#include <stdlib.h>
#include "maze.h"
#include <stdio.h>
typedef enum
{
    CHECK_SIDE1,
    CHECK_SIDE2,
    CHECK_FRONT,
    CHECK_BACK,
    CHECK_ALL
} STATE;

int main()
{
    STATE state = CHECK_FRONT;

    Testing_Maze();

    while (Running())
    {
        switch (state)
        {
        case CHECK_FRONT:
            if (Is_There_Wall())
            {
                Robot(CLOCK_WISE);
                state = CHECK_SIDE1;
            }
            else
            {
                Forward();
                state = CHECK_FRONT;
            }
            break;
        case CHECK_SIDE1:
            if (Is_There_Wall())
            {
                Robot(COUNTER_CW);
                Robot(COUNTER_CW);
                state = CHECK_SIDE2;
            }
            else
            {
                Forward();
                state = CHECK_FRONT;
            }
            break;
        case CHECK_SIDE2:
            if (Is_There_Wall())
            {
                Robot(CLOCK_WISE);
                Robot(CLOCK_WISE);
                Robot(CLOCK_WISE);
                state = CHECK_BACK;
            }
            else
            {
                Forward();
                state = CHECK_FRONT;
            }
            break;
        case CHECK_BACK:
            if (Is_There_Wall())
            {
                state = CHECK_ALL;
            }
            else
            {
                Forward();
                state = CHECK_FRONT;
            }
            break;
        }
    }
    Challenge_Was_Finished();
    return 0;
}