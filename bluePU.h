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

    string power()
    {
        return "Blue";
    }
};

#endif