#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "board.h"
class GamePlay
{
private:
    Board bottom_board;
    Board top_board;
    int stage;
public:
    GamePlay() :top_board(true)
    {
        stage = 1;
    }

    void draw_game()
    {
        bottom_board.draw_board();
        if (stage == 1)
        {
            top_board.draw_board();
        }
    }


    // Board functions here
    float get_board_b()
    {
        return bottom_board.get_pos();
    }
    float get_board_t()
    {
        return top_board.get_pos();
    }
    void set_board_b(float x)
    {
        bottom_board.set_pos(x);
    }
    void set_board_t(float x)
    {
        top_board.set_pos(x);
    }
};
#endif