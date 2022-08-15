#include "label.h"
#include <ncurses.h>

using namespace std;

Label::Label(string labelString) : IDrawable(), m_fontColor(Color::white), m_backgroundColor(Color::black)
{
    m_labelString = labelString;
}

Label::Label(string labelString, Color fontColor) : Label(labelString)
{
    m_fontColor = fontColor;
}

Label::Label(string labelString, Color fontColor, Color backgroundColor) : Label(labelString)
{
    m_fontColor = fontColor;
    m_backgroundColor = backgroundColor;
}

Label::~Label()
{
}

void Label::draw(const IGraphicsEngine& engine)
{
    engine.draw(m_labelString, m_vertical_position, m_horizontal_position, m_fontColor, m_backgroundColor);
}
