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

    string power()
    {
        return "Pink";
    }
};

#endif