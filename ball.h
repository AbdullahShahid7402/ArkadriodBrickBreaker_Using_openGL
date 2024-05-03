#ifndef BALL_H
#define BALL_H
#include"util.h"

class Ball
{
private:
    float x, y;
    int color;
    float speed;
    float dx, dy;
    int deathTimer;
public:
    Ball(int deathTimer_ = -1)
    {
        x = 1000 / 2;
        y = 40;
        speed = 2.5;
        color = WHITE;
        dx = 0;
        dy = speed;
        deathTimer = deathTimer_;
    }
    void mov_ball()
    {
        x += dx;
        y += dy;
    }
    void draw_ball()
    {
        DrawCircle(x, y, 5, colors[color]);
    }

    // getters and setters
    float get_x()
    {
        return x;
    }
    float get_y()
    {
        return y;
    }
    void set_x(float x)
    {
        this->x = x;
    }
    void set_y(float y)
    {
        this->y = y;
    }
    float get_dx()
    {
        return dx;
    }
    float get_dy()
    {
        return dy;
    }
    void set_dx(float dx)
    {
        this->dx = dx;
    }
    void set_dy(float dy)
    {
        this->dy = dy;
    }
    int get_color()
    {
        return color;
    }
    void set_color(int Color)
    {
        color = Color;
    }
    float get_speed()
    {
        return speed;
    }

};

#endif