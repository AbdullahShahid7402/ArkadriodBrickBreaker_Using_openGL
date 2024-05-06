#ifndef GREENPU_H
#define GREENPU_H
#include "powerup.h"

class GreenPU : public Powerup
{
public:
    GreenPU(int x_ = 0, int y_ = 0, int color_ = GRAY)
    {
        x = x_;
        y = y_;
        color = color_;
    }
    void draw()
    {
        y--;
        DrawTriangle(x, y + 5, x - 5, y - 5, x + 5, y - 5, colors[GREEN]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall, int AddBalln)
    {
        bottom->make_large();
        top->make_large();
    }
};

#endif