#ifndef RED_H
#define RED_H
#include "powerup.h"

class RedPU : public Powerup
{
public:
    void draw()
    {
        y--;
        DrawRectangle(x - 5, y - 5, 10, 5, colors[RED]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall)
    {
        fast = 5 * 60;
    }
};

#endif