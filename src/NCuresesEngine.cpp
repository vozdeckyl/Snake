#include <ncurses.h>
#include "NCursesEngine.h"

NCursesEngine::NCursesEngine(int m_numOfRows, int m_numOfColumns)
{
    //initialize
    initscr();
    clear();
    getmaxyx(stdscr, m_numOfRows, m_numOfColumns);
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr,TRUE);
}

NCursesEngine::~NCursesEngine()
{
}

NCursesEngine::draw(std::string text, int y, int x, Color text, Color background)
{
    
}

NCursesEngine::clear()
{
}
