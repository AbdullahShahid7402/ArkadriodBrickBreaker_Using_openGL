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
    int maxPowerups;
    int currentPowerup;
    fstream file;
    int highscore;
    Ball** balls;
    Brick** bricks;
    Powerup** powerups;
    int brickcount;
    Board bottom_board;
    Board top_board;
    int stage;
    int score;
    int lives;
    bool highscoreBeaten;

    int fastBall, slowBall;

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
        Name = "Name";
        RollNumber = "RollNumber";
        maxBalls = 10;
        maxBricks = 300;
        maxPowerups = 300;
        currentPowerup = 0;

        fastBall = 0;
        slowBall = 0;

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

        powerups = new Powerup * [maxPowerups];
        for (int i = 0;i < maxPowerups;i++)
        {
            powerups[i] = nullptr;
        }

        stage = 0;
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
        if (stage > 3)
        {
            save_current_score();
            return;
        }
        stage_change();
        if (fastBall)
            fastBall--;
        if (slowBall)
            slowBall--;
        if (score > highscore)
        {
            highscore = score;
            highscoreBeaten = true;
        }

        if (balls[0] == nullptr)
            balls[0] = new Ball;

        for (int i = 0;i < maxBalls;i++)
        {
            if (balls[i] != nullptr)
            {
                balls[i]->draw_ball();
                balls[i]->mov_ball(fastBall, slowBall);
                ball_wall_bounce(balls[i]);
                ball_board_bounce(balls[i], bottom_board);
                if (stage == 3)
                {
                    ball_board_bounce(balls[i], top_board);
                }
                balls[i] = ball_out_of_bounds(balls[i], (i == 0));
                if (balls[i] != nullptr)
                    if (balls[i]->isDead())
                    {
                        delete balls[i];
                        balls[i] = nullptr;
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
                        while (powerups[currentPowerup] != nullptr)
                        {
                            currentPowerup++;
                        }

                        powerups[(currentPowerup++) % maxPowerups] = bricks[j]->get_powerup();
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
        for (int i = 0;i < maxPowerups;i++)
        {
            if (powerups[i] != nullptr)
            {
                powerups[i]->draw();
                if (powerup_collect(powerups[i]) || powerups[i]->get_y() < -10)
                {
                    delete powerups[i];
                    powerups[i] = nullptr;
                }
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
        if (lives == 0)
            stage = 5;
        if (brickcount)
            return;
        stage++;
        balls[0] = nullptr;
        switch (stage)
        {
        case 1:
            stage01();
            break;
        case 2:
            stage02();
            break;
        case 3:
            stage03();
            // brickcount = 1;
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
            for (int j = 0;j < 5;j++)
            {
                type = rand();
                int life = 0;
                if (type % 5 == 0)
                    life = 1;
                else if (type % 5 > 0 && type % 5 <= 2)
                    life = 2;
                else
                    life = 3;

                bricks[brickcount] = new Brick(i * 20 + 10 + 200 + 200, j * 10 + 400, life, COLORS[type % 5], SCORES[type % 5]);
                brickcount++;
                // type++;
            }
        }
    }
    void stage02()
    {
        int COLORS[] = { GREEN,PINK,YELLOW,BLUE,RED };
        int SCORES[] = { 1,2,3,4,5 };
        int type = 0;
        for (int k = 0;k < 3;k++)
        {
            for (int i = 0;i < 5;i++)
            {
                for (int j = 0;j < 4;j++)
                {
                    type = rand();
                    int life = 0;
                    if (type % 5 == 0)
                        life = 1;
                    else if (type % 5 > 0 && type % 5 <= 2)
                        life = 2;
                    else
                        life = 3;

                    bricks[brickcount] = new Brick((k * 20 * 5) + i * 20 + 10 + 200, (-k * 10 * 4) + j * 10 + 400, life, COLORS[type % 5], SCORES[type % 5]);
                    brickcount++;
                    // type++;
                }
            }
        }
        for (int k = 0;k < 2;k++)
        {
            for (int i = 0;i < 5;i++)
            {
                for (int j = 0;j < 4;j++)
                {
                    type = rand();
                    int life = 0;
                    if (type % 5 == 0)
                        life = 1;
                    else if (type % 5 > 0 && type % 5 <= 2)
                        life = 2;
                    else
                        life = 3;

                    bricks[brickcount] = new Brick((k * 20 * 5) + i * 20 + 10 + 200, (k * 10 * 4) + j * 10 + 400 - 160, life, COLORS[type % 5], SCORES[type % 5]);
                    brickcount++;
                    // type++;
                }
            }
        }
    }
    void stage03()
    {
        row_wise_br(0, 6, 1, 1, 500, 300);
        row_wise_bl(0, 6, 1, 1, 500, 300);
        row_wise_br(6, 0, -1, -1, 500 - 6 * 20, 300 + 10 * 5);
        row_wise_bl(6, 0, -1, -1, 500 + 6 * 20, 300 + 10 * 5);


    }
    void row_wise_br(int current, int max, int incrementa, int incrementb, int x, int y)
    {
        if (current == max)
            return;
        column_wise_br(current, max, incrementb, current, x, y);
        row_wise_br(current + incrementa, max, incrementa, incrementb, x, y);
    }
    void column_wise_br(int current, int max, int increment, int i, int x, int y)
    {
        if (current == max)
            return;

        int COLORS[] = { GREEN,PINK,YELLOW,BLUE,RED };
        int SCORES[] = { 1,2,3,4,5 };
        int life = 0;
        if (brickcount % 5 == 0)
            life = 1;
        else if (brickcount % 5 > 0 && brickcount % 5 <= 2)
            life = 2;
        else
            life = 3;

        bricks[brickcount] = new Brick(current * 20 + x, i * 10 + y, life, COLORS[brickcount % 5], SCORES[brickcount % 5]);
        brickcount++;
        column_wise_br(current + increment, max, increment, i, x, y);
    }
    void row_wise_bl(int current, int max, int incrementa, int incrementb, int x, int y)
    {
        if (current == max)
            return;
        column_wise_bl(current, max, incrementb, current, x, y);
        row_wise_bl(current + incrementa, max, incrementa, incrementb, x, y);
    }
    void column_wise_bl(int current, int max, int increment, int i, int x, int y)
    {
        if (current == max)
            return;
        if (current == 0)
            current++;
        if (current == 6)
            current--;

        int COLORS[] = { GREEN,PINK,YELLOW,BLUE,RED };
        int SCORES[] = { 1,2,3,4,5 };
        int life = 0;
        if (brickcount % 5 == 0)
            life = 1;
        else if (brickcount % 5 > 0 && brickcount % 5 <= 2)
            life = 2;
        else
            life = 3;

        bricks[brickcount] = new Brick(-current * 20 + x, i * 10 + y, life, COLORS[brickcount % 5], SCORES[brickcount % 5]);
        brickcount++;
        column_wise_bl(current + increment, max, increment, i, x, y);
    }

    // check collision on board and powerups
    bool powerup_collect(Powerup* PU)
    {
        int x = PU->get_x();
        int y = PU->get_y();
        int width = 150;
        if (bottom_board.isLarge())
            width *= 2;
        if (bottom_board.isSmall())
            width /= 2;
        if (abs(y - bottom_board.get_y()) <= 10 && abs(x - bottom_board.get_x()) <= width)
        {
            PU->power(&bottom_board, &top_board, fastBall, slowBall, balls, maxBalls);
            return true;
        }
        return false;
    }

    // brick bounce mechanics
    void ball_bounce_brick(Brick* brick, Ball* ball)
    {
        float bx = brick->get_x(), by = brick->get_y();
        float x = ball->get_x(), y = ball->get_y();
        float dx = ball->get_dx(), dy = ball->get_dy();

        bool hit = false;
        if (abs(y - by) - ball->get_radius() <= brick->get_height() / 2 && abs(x - bx) - ball->get_radius() <= brick->get_width() / 2)
        {
            if (abs(y - by) - ball->get_radius() <= brick->get_height() / 2 && abs(x - bx) - ball->get_radius() > brick->get_width() / 2 - ball->get_speed(fastBall, slowBall))
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
            if (abs(x - bx) - ball->get_radius() <= brick->get_width() / 2 && abs(y - by) - ball->get_radius() > brick->get_height() / 2 - ball->get_speed(fastBall, slowBall))
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
                width *= 2;
            if (bottom_board.isSmall())
                width /= 2;
            if (abs(x - bx) - ball->get_radius() <= width / 2)
            {
                dx = (x - bx) / (15 * 2);
                if (bottom_board.isLarge())
                    dx /= 2;
                if (bottom_board.isSmall())
                    dx *= 2;
                if (dy < 0)
                    dy = ball->get_speed(fastBall, slowBall);
                else
                    dy = -ball->get_speed(fastBall, slowBall);

                float new_dx = dx / sqrt(dx * dx + dy * dy) * ball->get_speed(fastBall, slowBall);
                float new_dy = dy / sqrt(dx * dx + dy * dy) * ball->get_speed(fastBall, slowBall);
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
    int get_stage()
    {
        return stage;
    }
};
#endif