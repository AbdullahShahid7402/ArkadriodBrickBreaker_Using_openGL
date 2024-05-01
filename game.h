#ifndef GAME_H
#define GAME_H
#include "util.h"
using namespace std;

class Game
{
private:

    int stage;
    int width, height;

    // Function to draw text on the screen
    void drawText(const string& text, float x, float y, bool small = false) {
        if (small)
        {
            glRasterPos2f(x, y); // Set the position for the text
            for (const char& c : text) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c); // Draw each character of the string
            }
        }
        else
        {
            glRasterPos2f(x, y); // Set the position for the text
            for (const char& c : text) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Draw each character of the string
            }
        }
    }
public:

    Game(){ init(); }


    // initialize the game components for the game startup
    void init()
    {
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
        drawText("Brick Breaker", width / 2 - 60, height / 3 * 2 + 100);
        drawText("Press 'P' to play", width / 2 - 70, height / 3 + 50);
        drawText("Press 'E' to Exit", width / 2 - 70, height / 3 + 0);
    }

    void stage_1()
    {
        DrawSquare(0, 0, 100, colors[RED]);
    }

    int get_stage()
    {
        return stage;
    }
    void set_stage(int x)
    {
        stage = x;
    }
};


#endif