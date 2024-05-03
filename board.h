#ifndef BOARD_H
#define BOARD_H
#include "util.h"
class Board
{
private:
    float x, y;
    int large, small;
    int color;
public:
    Board(bool second = false)
    {
        color = GRAY;
        x = 500;
        y = 20;
        if (second)
            y = 580;
        large = small = 0;
    }

    void draw_board()
    {
        if (large > 0)
            large--;
        if (small > 0)
            small--;

        if (x < 200)
            x = 200;
        if (x > 800)
            x = 800;
        int width = 150;
        if (large)
            width *= 1.5;
        if (small)
            width /= 1.5;
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