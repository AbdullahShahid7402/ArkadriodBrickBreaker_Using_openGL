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

    void power(Board* bottom, Board* top, int& fast, int& slow, Ball** AddBall)
    {
        int count = 2;
        for (int i = 0;i < AddBalln;i++)
        {
            if (!count)
                break;
            if (AddBall[i] == nullptr)
            {
                AddBall[i] = new Ball(5 * 60, 2.5);
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