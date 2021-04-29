#include <ncurses.h>
#include <cmath>
#include "traveller.h"

Traveller::Traveller(double verticalVelocity, double horizontalVelocity) : IDrawable(),
                                                                        m_verticalFractionPosition(0.0),
                                                                        m_horizontalFractionPosition(0.0),
                                                                        m_verticalVelocity(0.0),
                                                                        m_horizontalVelocity(0.0) 
{
}


Traveller::~Traveller()
{
}

void Traveller::draw()
{
    init_pair(2,COLOR_RED,COLOR_WHITE);
    attrset(COLOR_PAIR(2));
    mvprintw(m_vertical_position,m_horizontal_position, " ");
    attrset(0);
}

void Traveller::notify(int ch)
{
    if(ch==KEY_LEFT)
    {
        m_verticalVelocity = 0.0;
        m_horizontalVelocity = -0.010;
    }
    else if(ch==KEY_RIGHT)
    {
        m_verticalVelocity = 0.0;
        m_horizontalVelocity = +0.010;
    }
    else if(ch==KEY_UP)
    {
        m_verticalVelocity = -0.005;
        m_horizontalVelocity = 0.0;
    }
    else if(ch==KEY_DOWN)
    {
        m_verticalVelocity = 0.005;
        m_horizontalVelocity = 0.0;
    }
}

void Traveller::update()
{
    m_verticalFractionPosition += m_verticalVelocity;
    m_horizontalFractionPosition += m_horizontalVelocity;

    if(m_verticalFractionPosition > 1.0)
    {
        m_verticalFractionPosition = 0.0;
        m_vertical_position++;
    }
    else if(m_verticalFractionPosition < -1.0)
    {
        m_verticalFractionPosition = 0.0;
        m_vertical_position--;
    }

    if(m_horizontalFractionPosition > 1.0)
    {
        m_horizontalFractionPosition = 0.0;
        m_horizontal_position++;
    }
    else if(m_horizontalFractionPosition < -1.0)
    {
        m_horizontalFractionPosition = 0.0;
        m_horizontal_position--;
    }
}