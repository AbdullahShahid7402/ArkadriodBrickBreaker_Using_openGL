#ifndef POWERUP_H
#define POWERUP_H
#include "util.h"
#include "board.h"
#include "ball.h"

class Powerup
{
protected:
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
    virtual void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall)
    {
        // power of the object
    }

    int get_x()
    {
        return x;
    }

    int get_y()
    {
        return y;
    }
};


#endif