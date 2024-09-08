#include "Bricks.hpp"

void IBrick::HardRotate(bool clockwise) 
{
    (void)clockwise;
    if(rotationState)
    {
        mask = {0, 1, 0, 0,
                0, 1, 0, 0,
                0, 1, 0, 0,
                0, 1, 0, 0};
        rotationState = false;
    }
    else 
    {
        mask = {0, 0, 0, 0,
                0, 0, 0, 0,
                1, 1, 1, 1,
                0, 0, 0, 0};
        rotationState = true;
    }
   
}

void CBrick::HardRotate(bool clockwise) 
{
    (void)clockwise; //optimisation
}
