#ifndef YELLOW_H
#define YELLOW_H
#include "powerup.h"

class YellowPU : public Powerup
{
public:
    void draw()
    {
        y--;
        DrawSquare(x - 2.5, y - 2.5, 5, colors[YELLOW]);
    }

    string power()
    {
        return "Yellow";
    }
};

#endif