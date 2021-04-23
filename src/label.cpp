#include "label.h"
#include <ncurses.h>

Label::Label(string labelString) : IDrawable()
{
    m_labelString = labelString;
}

Label::~Label(){}

void Label::draw()
{
    mvprintw(m_vertical_position,m_horizontal_position, m_labelString.c_str());
}