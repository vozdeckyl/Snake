#ifndef IGRAPHICSENGINE_H
#define IGRAPHICSENGINE_H

#include <ncurses.h>
#include <string>

enum class Color
{
    black = COLOR_BLACK,
    blue = COLOR_BLUE,
    green = COLOR_GREEN,
    cyan = COLOR_CYAN,
    red = COLOR_RED,
    magenta = COLOR_MAGENTA,
    white = COLOR_WHITE,
    yellow = COLOR_YELLOW,
};

/*!
@brief Interface for a graphics library that is used to draw on screen.
*/
class IGraphicsEngine
{
  public:
    /*!
        @brief Initialization of the framwork. The function is called at the beginning.
    */
    virtual void init() = 0;

    /*!
        @brief Prepars screen for the drawing. The function is called before every drawing.
    */
    virtual void prepareScreen() = 0;

    /*!
        @brief Draws text on screen.
        @param text text string to be drawn on screen
        @param y vertical position of the first character
        @param x horizontal position of the first character
        @param textColor color of the text
        @param backgroundColor color of the background
    */
    virtual void draw(std::string text, int y, int x, Color textColor, Color backgroundColor) const = 0;

    /*!
        @brief This function is called after all objects are drawn on the screen.
    */
    virtual void refreshScreen() = 0;

    /*!
        @brief Clears the screen.
    */
    virtual void clearScreen() = 0;

    /*!
        @brief This function is called at the end.
    */
    virtual void endScreen() = 0;

    /*!
        @brief Returns number of rows of the screen.
    */
    virtual int numberOfRows() = 0;

    /*!
        @brief Returns number of columns of the screen.
    */
    virtual int numberOfColumns() = 0;

    /*!
        @brief Briefly pauses the program
        @param timeMS number of miliseconds
    */
    virtual void wait(int timeMS) = 0;

    /*!
        @brief Get input from the keyboard
    */
    virtual int input() = 0;
};

#endif
