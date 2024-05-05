#ifndef RED_H
#define RED_H
#include "powerup.h"

class RedPU : public Powerup
{
public:
    void draw()
    {
        y--;
        DrawRectangle(x - 5, y - 5, 10, 5, colors[RED]);
    }

    string power()
    {
        return "Red";
    }
};

#endif