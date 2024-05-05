#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "board.h"
#include "ball.h"
#include "brick.h"
#include <fstream>
#include <cmath>

class GamePlay
{
private:
    int maxBalls;
    int maxBricks;
    fstream file;
    int highscore;
    Ball** balls;
    Brick** bricks;
    int brickcount;
    Board bottom_board;
    Board top_board;
    int stage;
    int score;
    int lives;
    bool highscoreBeaten;
    bool levelChange;

    string Name;
    string RollNumber;

    void DrawString10(float x, float y, const string& score, float* color)
    {
        //  A pointer to a font style..
        //  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13,
        //  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
        //  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
        //  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
        glPushMatrix();
        glLoadIdentity();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        GLvoid* font_style = GLUT_BITMAP_TIMES_ROMAN_10;
        if (color)
            glColor3fv(color);
        glRasterPos3f(x, y, 1);
        //  Draw the characters one by one
        for (int i = 0; i < score.size(); i++)
            glutBitmapCharacter(font_style, score[i]);
        glPopMatrix();
    }
public:
    GamePlay() :top_board(true)
    {
        maxBalls = 10;
        maxBricks = 300;
        Name = "Name";
        RollNumber = "RollNumber";

        levelChange = true;

        file.open("highestscore", ios::in);
        if (file.fail())
        {
            file.open("highestscore", ios::out);
            file << 0;
            file.close();
            file.open("highestscore", ios::in);
        }
        file >> highscore;
        file.close();
        highscoreBeaten = false;
        score = 0;
        lives = 3;
        balls = new Ball * [maxBalls];
        for (int i = 0;i < maxBalls;i++)
        {
            balls[i] = nullptr;
        }
        balls[0] = new Ball;

        bricks = new Brick * [maxBricks];
        for (int i = 0;i < maxBricks;i++)
        {
            bricks[i] = nullptr;
        }
        brickcount = 0;

        stage = 1;
    }

    void save_current_score()
    {
        if (score < highscore)
            return;
        file.open("highestscore", ios::out);
        file << score;
        file.close();
    }

    void draw_game()
    {
        stage_change();
        if (score > highscore)
        {
            highscore = score;
            highscoreBeaten = true;
        }

        for (int i = 0;i < maxBalls;i++)
        {
            if (balls[i] != nullptr)
            {
                balls[i] = ball_out_of_bounds(balls[i], (i == 0));
                if (!i && balls[i] == nullptr)
                {
                    balls[0] = new Ball;
                }
                balls[i]->draw_ball();
                balls[i]->mov_ball();
                ball_wall_bounce(balls[i]);
                ball_board_bounce(balls[i], bottom_board);
                if (stage == 3)
                {
                    ball_board_bounce(balls[i], top_board);
                }
            }
        }

        for (int i = 0;i < maxBalls;i++)
        {
            for (int j = 0;j < maxBricks;j++)
            {
                if (balls[i] != nullptr && bricks[j] != nullptr)
                {
                    ball_bounce_brick(bricks[j], balls[i]);
                    if (bricks[j]->get_lives() == 0)
                    {
                        score += bricks[j]->get_score();
                        delete bricks[j];
                        bricks[j] = nullptr;
                        brickcount--;
                    }
                }
            }
        }

        for (int i = 0;i < maxBricks;i++)
        {
            if (bricks[i] != nullptr)
            {
                bricks[i]->draw();
            }
        }

        bottom_board.draw_board();
        if (stage == 3)
        {
            top_board.draw_board();
        }

        // draw borders and HUD

        DrawRectangle(0, 0, 200, 600, colors[BLACK]);
        DrawRectangle(800, 0, 200, 600, colors[BLACK]);
        DrawLine(200, 0, 200, 600, 3, colors[WHITE]);
        DrawLine(800, 0, 800, 600, 3, colors[WHITE]);

        DrawString(10, 500, "Lives = " + to_string(lives), colors[WHITE]);
        DrawString10(10, 450, "Score = " + to_string(score), colors[WHITE]);
        int col = highscoreBeaten ? YELLOW : WHITE;
        DrawString10(10, 400, "Highest score = " + to_string(highscore), colors[col]);
        DrawString10(10, 300, Name, colors[WHITE]);
        DrawString10(10, 250, RollNumber, colors[WHITE]);
        DrawString10(10, 100, "Press 'P' to pause the game", colors[YELLOW]);
    }
    void stage_change()
    {
        if (!levelChange)
            return;
        levelChange = false;
        switch (stage)
        {
        case 1:
            stage01();
            break;
        default:
            return;
        }
    }
    void stage01()
    {
        int COLORS[] = { GREEN,PINK,YELLOW,BLUE,RED };
        int SCORES[] = { 1,2,3,4,5 };
        int type = 0;
        for (int i = 0;i < 10;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                int life = 0;
                if (type % 5 == 0)
                    life = 1;
                else if (type % 5 > 0 && type % 5 <= 2)
                    life = 2;
                else
                    life = 3;

                bricks[brickcount++] = new Brick(i * 40 + 10 + 200 + 100, j * 20 + 400, life, COLORS[type % 5], SCORES[type % 5]);
                type++;
            }
        }
    }

    // brick bounce mechanics
    void ball_bounce_brick(Brick* brick, Ball* ball)
    {
        float bx = brick->get_x(), by = brick->get_y();
        float x = ball->get_x(), y = ball->get_y();
        float dx = ball->get_dx(), dy = ball->get_dy();

        bool hit = false;
        if (abs(y - by) - ball->get_radius() <= 20 / 2 && abs(x - bx) - ball->get_radius() <= 40 / 2)
        {
            if (abs(y - by) - ball->get_radius() <= 20 / 2 && abs(x - bx) - ball->get_radius() > 40 / 2 - ball->get_speed())
            {
                x -= dx;
                dx *= -1;
                if (!hit)
                {
                    hit = true;
                    brick->hit();
                    ball->set_color(brick->get_color());
                }
            }
            if (abs(x - bx) - ball->get_radius() <= 40 / 2 && abs(y - by) - ball->get_radius() > 20 / 2 - ball->get_speed())
            {
                y -= dy;
                dy *= -1;
                if (!hit)
                {
                    hit = true;
                    brick->hit();
                    ball->set_color(brick->get_color());
                }
            }
        }
        ball->set_x(x);
        ball->set_y(y);
        ball->set_dx(dx);
        ball->set_dy(dy);
    }


    // ball out of bounds to reduce life
    Ball* ball_out_of_bounds(Ball* ball, bool Parent = true)
    {
        float y = ball->get_y();
        if (y < -10 || y>610)
        {
            if (Parent)
                lives--;
            delete ball;
            return nullptr;
        }
        return ball;
    }

    // board bounce mechanics in case the ball hits the board
    void ball_board_bounce(Ball* ball, Board& board)
    {
        float bx = board.get_x(), by = board.get_y();
        float x = ball->get_x(), y = ball->get_y();
        float dx = ball->get_dx(), dy = ball->get_dy();
        if (y > by - 10 && y < by + 10)
        {
            y -= dy;
            int width = 150;
            if (bottom_board.isLarge())
                width *= 1.5;
            if (bottom_board.isSmall())
                width /= 1.5;
            if (abs(x - bx) - ball->get_radius() <= width / 2)
            {
                dx = (x - bx) / (15 * 2);
                if (bottom_board.isLarge())
                    dx /= 1.5;
                if (bottom_board.isSmall())
                    dx *= 1.5;
                if (dy < 0)
                    dy = ball->get_speed();
                else
                    dy = -ball->get_speed();

                float new_dx = dx / sqrt(dx * dx + dy * dy) * ball->get_speed();
                float new_dy = dy / sqrt(dx * dx + dy * dy) * ball->get_speed();
                dx = new_dx;
                dy = new_dy;
                board.change_color(ball->get_color());
            }
            else
                return;
        }
        ball->set_x(x);
        ball->set_y(y);
        ball->set_dx(dx);
        ball->set_dy(dy);
    }

    // wall bounce mechanics changing ball direction in case it hits a wall
    void ball_wall_bounce(Ball* ball)
    {
        float x = ball->get_x(), y = ball->get_y();
        float dx = ball->get_dx(), dy = ball->get_dy();
        if (x < 200 || x >= 800)
        {
            x -= dx;
            dx *= -1;
        }
        // in case of level 3 the upper wall is gone
        // so this check ensures wall only works for levels other than 3
        if (stage != 3)
        {
            if (y >= 600)
            {
                y -= dy;
                dy *= -1;
            }
        }
        ball->set_x(x);
        ball->set_y(y);
        ball->set_dx(dx);
        ball->set_dy(dy);
    }


    // Board functions here
    float get_board_b()
    {
        return bottom_board.get_x();
    }
    float get_board_t()
    {
        return top_board.get_x();
    }
    void set_board_b(float x)
    {
        bottom_board.set_x(x);
    }
    void set_board_t(float x)
    {
        top_board.set_x(x);
    }
};
#endif