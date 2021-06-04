#include <ncurses.h>
#include "colors.h"
#include "NCursesEngine.h"

NCursesEngine::NCursesEngine() : m_columns(0), m_rows(0)
{
}

NCursesEngine::~NCursesEngine()
{
}

void NCursesEngine::init()
{
    initscr();
    clear();
    getmaxyx(stdscr, m_rows, m_columns);
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr,TRUE);

    Colors::generateColors();
}


void NCursesEngine::draw(std::string text, int y, int x, Color textColor, Color backgroundColor)
{
    Colors::activateColor((int) textColor, (int) backgroundColor);
    mvprintw(y,x,text.c_str());
    Colors::deactivateColor();    
}

void NCursesEngine::clear()
{
    clear();
}

int NCursesEngine::numberOfRows()
{
    return m_rows;
}

int NCursesEngine::numberOfColumns()
{
    return m_columns;
}