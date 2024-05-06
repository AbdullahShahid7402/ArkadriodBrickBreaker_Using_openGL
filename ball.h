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
    int radius;
    int deathTimer;
public:
    Ball(int deathTimer_ = -1, int radius_ = 5)
    {
        radius = radius_;
        x = 1000 / 2;
        y = 40;
        speed = 2.5;
        color = WHITE;
        dx = 0;
        dy = speed;
        deathTimer = deathTimer_;
    }
    void mov_ball(int fast, int slow)
    {
        float dx_ = dx;
        float dy_ = dy;
        if (fast > 0)
        {
            dx_ *= 2;
            dy_ *= 2;
        }
        if (slow > 0)
        {
            dx_ /= 2;
            dy_ /= 2;
        }

        x += dx_;
        y += dy_;
        if (deathTimer > 0)
            deathTimer--;
    }
    void draw_ball()
    {
        DrawCircle(x, y, radius, colors[color]);
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
    void set_dx(float dx_)
    {
        dx = dx_;
    }
    void set_dy(float dy_)
    {
        dy = dy_;
    }
    int get_color()
    {
        return color;
    }
    void set_color(int Color)
    {
        color = Color;
    }
    float get_speed(int fast, int slow)
    {
        int s = speed;
        if (fast > 0)
            s *= 2;
        if (slow > 0)
            s /= 2;
        return s;
    }
    int get_radius()
    {
        return radius;
    }
    bool isDead()
    {
        return (deathTimer == 0);
    }

};

#endif