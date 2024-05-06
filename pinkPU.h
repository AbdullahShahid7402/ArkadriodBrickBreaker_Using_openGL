#ifndef PINKPU_H
#define PINKPU_H
#include "powerup.h"

class PinkPU : public Powerup
{
public:
    void draw()
    {
        y--;
        DrawSquare(x - 2.5, y - 2.5, 5, colors[PINK]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall)
    {
        bottom->make_small();
        top->make_small();
    }
};

#endif