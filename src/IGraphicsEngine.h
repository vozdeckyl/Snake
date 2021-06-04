#ifndef IGRAPHICSENGINE_H
#define IGRAPHICSENGINE_H

#include <string>

enum class Color {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    white,
    gray,
    brightBlue,
    brightGreen,
    brightCyan,
    brightRed,
    brightMagenta,
    yellow,
    brightWhite,
};

class IGraphicsEngine {
    public:
        virtual void init() = 0;
        virtual void draw(std::string text, int y, int x, Color textColor, Color backgroundColor) = 0;
        virtual void clear() = 0;
        virtual int numberOfRows() = 0;
        virtual int numberOfColumns() = 0;
};

#endif
