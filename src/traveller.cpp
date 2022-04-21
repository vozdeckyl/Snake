#include "traveller.h"
#include "colors.h"
#include <cmath>
#include <ncurses.h>

Traveller::Traveller(double verticalVelocity, double horizontalVelocity)
    : IDrawable(), m_verticalFractionPosition(0.0), m_horizontalFractionPosition(0.0), m_verticalVelocity(0.0),
      m_horizontalVelocity(0.0)
{
}

Traveller::~Traveller()
{
}

void Traveller::draw(const IGraphicsEngine* engine)
{
    /*
    Colors::activateColor(COLOR_RED,COLOR_WHITE);
    mvprintw(m_vertical_position,m_horizontal_position, " ");
    Colors::deactivateColor();
    */
    engine->draw("X", m_vertical_position, m_horizontal_position, Color::white, Color::black);
}

void Traveller::notify(int ch)
{
    if (ch == KEY_LEFT)
    {
        m_verticalVelocity = 0.0;
        m_horizontalVelocity = -0.010;
    }
    else if (ch == KEY_RIGHT)
    {
        m_verticalVelocity = 0.0;
        m_horizontalVelocity = +0.010;
    }
    else if (ch == KEY_UP)
    {
        m_verticalVelocity = -0.005;
        m_horizontalVelocity = 0.0;
    }
    else if (ch == KEY_DOWN)
    {
        m_verticalVelocity = 0.005;
        m_horizontalVelocity = 0.0;
    }
}

void Traveller::update()
{
    m_verticalFractionPosition += m_verticalVelocity;
    m_horizontalFractionPosition += m_horizontalVelocity;

    if (m_verticalFractionPosition > 1.0)
    {
        m_verticalFractionPosition = 0.0;
        m_vertical_position++;
    }
    else if (m_verticalFractionPosition < -1.0)
    {
        m_verticalFractionPosition = 0.0;
        m_vertical_position--;
    }

    if (m_horizontalFractionPosition > 1.0)
    {
        m_horizontalFractionPosition = 0.0;
        m_horizontal_position++;
    }
    else if (m_horizontalFractionPosition < -1.0)
    {
        m_horizontalFractionPosition = 0.0;
        m_horizontal_position--;
    }
}