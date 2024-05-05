#ifndef POWERUP_H
#define POWERUP_H
#include "util.h"

class Powerup
{
private:
    float x, y;
    int color;
public:
    Powerup(int x_ = 0, int y_ = 0, int color_ = GRAY)
    {
        x = x_;
        y = y_;
        color = color_;
    }
    virtual void draw()
    {
        // draw powerup
    }
    virtual void power()
    {
        // power of the object
    }
};


#endif