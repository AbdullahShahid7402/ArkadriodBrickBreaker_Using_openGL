#ifndef PINKPU_H
#define PINKPU_H
#include "powerup.h"

class PinkPU : public Powerup
{
public:
    PinkPU(int x_ = 0, int y_ = 0, int color_ = GRAY)
    {
        x = x_;
        y = y_;
        color = color_;
    }
    void draw()
    {
        y--;
        DrawSquare(x - 5, y - 5, 10, colors[PINK]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall, int AddBalln)
    {
        bottom->make_small();
        top->make_small();
    }
};

#endif