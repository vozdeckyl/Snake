#include <ncurses.h>
#include "colors.h"
#include "label.h"

using namespace std;

Label::Label(string labelString) : IDrawable(), m_fontColor(COLOR_WHITE), m_backgroundColor(COLOR_BLACK)
{
    m_labelString = labelString;
}

Label::Label(string labelString, int fontColor) : Label(labelString)
{
    m_fontColor = fontColor;
}

Label::Label(string labelString, int fontColor, int backgroundColor) : Label(labelString)
{
    m_fontColor = fontColor;
    m_backgroundColor = backgroundColor;
}

Label::~Label(){}

void Label::draw()
{
    Colors::activateColor(m_fontColor,m_backgroundColor);
    mvprintw(m_vertical_position,m_horizontal_position, m_labelString.c_str());
    Colors::deactivateColor();
}