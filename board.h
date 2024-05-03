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
        y = 10;
        if (second)
            y = 570;
        large = small = false;
    }

    void draw_board()
    {
        if (x < 0)
            x = 0;
        if (x > 1000)
            x = 1000;
        int width = 150;
        if (large)
            width *= 2;
        if (small)
            width /= 2;
        DrawRectangle(x - width / 2, y, width, 20, colors[color]);
    }
    void change_color(int Color)
    {
        color = Color;
    }
    float get_pos()
    {
        return x;
    }
    void set_pos(float x)
    {
        this->x = x;
    }
};
#endif