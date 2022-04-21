#include "colors.h"
#include <ncurses.h>

void Colors::generateColors()
{
    start_color();

    for (int i = 1; i <= 16; i++)
    {
        for (int j = 1; j <= 16; j++)
        {
            init_pair(i * 17 + j, i - 1, j - 1);
        }
    }
}

void Colors::activateColor(int fontColor, int backgroundColor)
{
    attrset(COLOR_PAIR((fontColor + 1) * 17 + backgroundColor + 1));
}

void Colors::deactivateColor()
{
    attrset(0);
}