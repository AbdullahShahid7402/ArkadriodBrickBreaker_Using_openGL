#ifndef BLUEPU_H
#define BLUEPU_H
#include "powerup.h"

class BluePU : public Powerup
{
public:
    void draw()
    {
        y--;
        DrawCircle(x, y, 2.5, colors[BLUE]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall)
    {
        slow = 5 * 60;
    }
};

#endif