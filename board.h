#ifndef BOARD_H
#define BOARD_H
#include "util.h"
class Board
{
private:
    float x, y;
    bool large, small;
    int color;
public:
    Board(bool second = false)
    {
        color = GRAY;
        x = 500;
        y = 20;
        if (second)
            y = 580;
        large = small = false;
    }

    void draw_board()
    {
        if (large && small)
        {
            large = small = false;
        }

        if (x < 200)
            x = 200;
        if (x > 800)
            x = 800;
        int width = 150;
        if (large)
            width *= 2;
        if (small)
            width /= 2;
        DrawRectangle(x - width / 2, y - 20 / 2, width, 20, colors[color]);
    }
    void change_color(int Color)
    {
        color = Color;
    }
    float get_x()
    {
        return x;
    }
    void set_x(float x)
    {
        this->x = x;
    }
    float get_y()
    {
        return y;
    }
    void set_y(float y)
    {
        this->y = y;
    }
    void make_large()
    {
        large = true;
    }
    void make_small()
    {
        small = true;
    }

    bool isLarge()
    {
        return large;
    }
    bool isSmall()
    {
        return small;
    }
};
#endif