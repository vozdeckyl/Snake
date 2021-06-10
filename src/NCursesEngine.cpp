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

void NCursesEngine::prepareScreen()
{
    erase();
	
    move(0,0);
    for(int i = 0; i<=m_rows*m_columns; i++)
    {
        printw(" ");
    }

    Colors::activateColor(COLOR_BLACK,COLOR_BLACK);
    box(stdscr, 0, 0);
    Colors::deactivateColor();
}


void NCursesEngine::draw(std::string text, int y, int x, Color textColor, Color backgroundColor) const
{
    Colors::activateColor((int) textColor, (int) backgroundColor);
    mvprintw(y,x,text.c_str());
    Colors::deactivateColor();    
}

void NCursesEngine::refreshScreen()
{
    refresh();
}

void NCursesEngine::clearScreen() const
{
    clear();
}

void NCursesEngine::endScreen()
{
    endwin();
}

int NCursesEngine::numberOfRows()
{
    return m_rows;
}

int NCursesEngine::numberOfColumns()
{
    return m_columns;
}

void NCursesEngine::wait(int timeMS)
{
    napms(timeMS);
}

int NCursesEngine::input()
{
    return getch();
}