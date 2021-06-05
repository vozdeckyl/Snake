#ifndef IGRAPHICSENGINE_H
#define IGRAPHICSENGINE_H

#include <string>
#include <ncurses.h>

enum class Color {
    black = COLOR_BLACK,
    blue = COLOR_BLUE,
    green = COLOR_GREEN,
    cyan = COLOR_CYAN,
    red = COLOR_RED,
    magenta = COLOR_MAGENTA,
    white = COLOR_WHITE,
    yellow = COLOR_YELLOW,
};

class IGraphicsEngine {
    public:
        virtual void init() = 0;
        virtual void prepareScreen() = 0; 
        virtual void draw(std::string text, int y, int x, Color textColor, Color backgroundColor) const = 0;
        virtual void refreshScreen() = 0;
        virtual void clearScreen() const = 0;
        virtual void endScreen() = 0;
        virtual int numberOfRows() = 0;
        virtual int numberOfColumns() = 0;
};

#endif
