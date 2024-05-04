#ifndef GAME_H
#define GAME_H
#include "util.h"
#include "gameplay.h"
using namespace std;

class Game
{
private:
    GamePlay* gameplay;
    int stage;
    int width, height;

public:

    Game(){ init(); }


    // initialize the game components for the game startup
    void init()
    {
        gameplay = nullptr;
        stage = 0;
        width = 1000;
        height = 600;
    }

    // draw the components that are supposed to be on the display
    void draw_stage()
    {
        switch (stage)
        {
        case 0:
            stage_0();
            break;
        case 1:
            stage_1();
        default:
            return;
        }
    }

    // Draw the main menu
    void stage_0()
    {
        int newGamecol = (gameplay == nullptr) ? (YELLOW) : (GREEN);
        DrawString(width / 2 - 60, height / 3 * 2 + 100, "Brick Breaker", colors[WHITE]);
        DrawString(width / 2 - 110, height / 3 + 50, "Press 'N' to start new Game", colors[newGamecol]);
        DrawString(width / 2 - 72, height / 3 + 0, "Press 'Esc' to Exit", colors[RED]);
        if (gameplay != nullptr)
            DrawString(width / 2 - 80, height / 3 + 100, "Press 'C' to continue", colors[YELLOW]);
    }

    void stage_1()
    {
        if (gameplay == nullptr)
            gameplay = new GamePlay;
        // DrawSquare(0, 0, 100, colors[RED]);
        gameplay[0].draw_game();
    }

    void reset_gameplay()
    {
        if (gameplay != nullptr)
        {
            gameplay->save_current_score();
            delete gameplay;
        }
        gameplay = new GamePlay;
    }
    bool canContinue()
    {
        return (gameplay != nullptr);
    }
    int get_stage()
    {
        return stage;
    }
    void set_stage(int x)
    {
        stage = x;
    }

    // board functions here
    float get_board_b()
    {
        return gameplay[0].get_board_b();
    }
    float get_board_t()
    {
        return gameplay[0].get_board_t();
    }
    void set_board_b(float x)
    {
        gameplay[0].set_board_b(x);
    }
    void set_board_t(float x)
    {
        gameplay[0].set_board_t(x);
    }
};


#endif