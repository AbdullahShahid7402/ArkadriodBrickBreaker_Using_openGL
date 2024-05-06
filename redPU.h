#ifndef RED_H
#define RED_H
#include "powerup.h"

class RedPU : public Powerup
{
public:
    RedPU(int x_ = 0, int y_ = 0, int color_ = GRAY)
    {
        x = x_;
        y = y_;
        color = color_;
    }
    void draw()
    {
        y--;
        DrawRectangle(x - 10, y - 10, 20, 10, colors[RED]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall, int AddBalln)
    {
        fast = 5 * 60;
    }
};

#endif