#ifndef BRICK_H
#define BRICK_H
#include "util.h"
#include "powerup.h"

class Brick
{
private:
    float x, y;
    int color, lives;
    int score;

public:
    Brick(int x_ = 0, int y_ = 0, int lives_ = 1, int color_ = GRAY, int score_ = 0)
    {
        x = x_;
        y = y_;
        lives = lives_;
        color = color_;
        score = score_;
    }

    void draw()
    {
        int width = 40;
        DrawRectangle(x - width / 2, y - 20 / 2, width, 20, colors[color]);
    }

    Powerup* get_powerup()
    {
        return (new Powerup);
    }

    // getters setters
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
    void hit()
    {
        lives--;
    }
    int get_lives()
    {
        return lives;
    }
    int get_color()
    {
        return color;
    }
    int get_score()
    {
        return score;
    }
};

#endif