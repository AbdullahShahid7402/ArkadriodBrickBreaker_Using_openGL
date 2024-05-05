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

    string power()
    {
        return "Green";
    }
};

#endif