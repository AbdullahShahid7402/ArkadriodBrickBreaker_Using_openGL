#ifndef BLUEPU_H
#define BLUEPU_H
#include "powerup.h"

class BluePU : public Powerup
{
public:
    BluePU(int x_ = 0, int y_ = 0, int color_ = GRAY)
    {
        x = x_;
        y = y_;
        color = color_;
    }
    void draw()
    {
        y--;
        DrawCircle(x, y, 4, colors[BLUE]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall, int AddBalln)
    {
        slow = 5 * 60;
    }
};

#endif