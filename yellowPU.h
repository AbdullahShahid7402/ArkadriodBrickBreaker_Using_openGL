#ifndef YELLOW_H
#define YELLOW_H
#include "powerup.h"

class YellowPU : public Powerup
{
public:
    YellowPU(int x_ = 0, int y_ = 0, int color_ = GRAY)
    {
        x = x_;
        y = y_;
        color = color_;
    }
    void draw()
    {
        y--;
        DrawSquare(x - 5, y - 5, 10, colors[YELLOW]);
    }

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall, int AddBalln)
    {
        int count = 2;
        for (int i = 0;i < AddBalln;i++)
        {
            if (!count)
                break;
            if (AddBall[i] == nullptr)
            {
                AddBall[i] = new Ball(5 * 60, 10);
                count--;
                if (count)
                {
                    AddBall[i]->set_dx(0.5);
                }
                else
                {
                    AddBall[i]->set_dx(-0.5);
                }
            }
        }
    }
};

#endif