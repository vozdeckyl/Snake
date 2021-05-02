#include <ncurses.h>
#include <cmath>
#include <stdlib.h> 
#include "snake.h"
#include "window.h"

using namespace std;

Snake::Snake(double verticalVelocity, double horizontalVelocity) : IDrawable(),
m_verticalFractionPosition(0.0),
m_horizontalFractionPosition(0.0),
m_verticalVelocity(0.0),
m_horizontalVelocity(0.0),
m_target_vertical(0),
m_target_horizontal(0)
{
    m_cells.emplace_front(0,-1);
}


Snake::~Snake()
{
}

void Snake::draw()
{
    attrset(COLOR_PAIR(2));
    mvprintw(m_target_vertical,m_target_horizontal,"X");
    mvprintw(m_vertical_position,m_horizontal_position, " ");
    int i{0};
    for(pair<int,int> cell : m_cells)
    {
        mvprintw(cell.first,cell.second, " ");
        //mvprintw(20+i++, 1, (to_string(cell.first) + " " + to_string(cell.second)).c_str());
    }
    attrset(0);

    auto last_pair = ++m_cells.end();

    mvprintw(20,1,to_string((*last_pair).first).c_str());
    mvprintw(21,1,to_string((*last_pair).second).c_str());
    mvprintw(22,1,to_string(m_target_vertical).c_str());
    mvprintw(23,1,to_string(m_target_horizontal).c_str());

}

void Snake::notify(int ch)
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

void Snake::update()
{
    m_verticalFractionPosition += m_verticalVelocity;
    m_horizontalFractionPosition += m_horizontalVelocity;

    if(m_verticalFractionPosition > 1.0)
    {
        m_verticalFractionPosition = 0.0;
        shiftCells();
        m_vertical_position++;
    }
    else if(m_verticalFractionPosition < -1.0)
    {
        m_verticalFractionPosition = 0.0;
        shiftCells();
        m_vertical_position--;
    }

    if(m_horizontalFractionPosition > 1.0)
    {
        m_horizontalFractionPosition = 0.0;
        shiftCells();
        m_horizontal_position++;
    }
    else if(m_horizontalFractionPosition < -1.0)
    {
        m_horizontalFractionPosition = 0.0;
        shiftCells();
        m_horizontal_position--;
    }
}

void Snake::shiftCells()
{
    m_cells.emplace_front(make_pair(m_vertical_position,m_horizontal_position));
    // if the position of the last cell is different, don't get rid of the last cell
    // if they are the same, get it attached and generate a new random position for the target
    
    if((*(++m_cells.end())).first == m_target_vertical && (*(++m_cells.end())).second == m_target_horizontal)
    {
        m_target_horizontal = rand() % m_owner->getWidth();
        m_target_vertical = rand() % m_owner->getHeight();
    }
    else
    {
        m_cells.pop_back();
    }
}