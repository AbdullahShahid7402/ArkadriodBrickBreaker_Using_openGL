#ifndef GREENPU_H
#define GREENPU_H
#include "powerup.h"

class GreenPU : public Powerup
{
public:
    void draw()
    {
        y--;
        DrawTriangle(x, y + 2.5, x - 2.5, y - 2.5, x + 2.5, y - 2.5, colors[GREEN]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall)
    {
        bottom->make_large();
        top->make_large();
    }
};

#endif