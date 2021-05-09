#include <ncurses.h>
#include <cmath>
#include <stdlib.h> 
#include "snake.h"
#include "window.h"
#include "colors.h"
#include "scoreLogger.h"

using namespace std;

Snake::Snake(double verticalVelocity, double horizontalVelocity) : IDrawable(),
m_verticalFractionPosition(0.0),
m_horizontalFractionPosition(0.0),
m_verticalVelocity(0.0),
m_horizontalVelocity(0.01),
m_target_vertical(5),
m_target_horizontal(5),
m_gameOver(false),
m_playWindowHeight(30),
m_playWindowWidth(100), 
m_score(0)
{
    gameOverLabel = string("* * * *   GAME OVER   * * * *");
}


Snake::~Snake()
{
    ScoreLogger log;
    log.logScore(m_score);
}

void Snake::draw()
{
    drawWalls();

    mvprintw(m_playWindowHeight+1,30,("Score: " + to_string(m_score)).c_str());

    Colors::activateColor(COLOR_BLACK,COLOR_YELLOW);
    mvprintw(m_target_vertical,m_target_horizontal,"X");

    Colors::activateColor(COLOR_RED,COLOR_GREEN);

    for(pair<int,int> cell : m_cells)
    {
        mvprintw(cell.first,cell.second, " ");
    }

    mvprintw(m_vertical_position,m_horizontal_position, ":");

    Colors::deactivateColor();

    if(m_gameOver)
    {
        mvprintw((int) (0.5*m_playWindowHeight),(int) (0.5*(m_playWindowWidth-gameOverLabel.size())), gameOverLabel.c_str());
    }
}

void Snake::notify(int ch)
{
    if(ch==KEY_LEFT && m_horizontalVelocity==0.0)
    {
        m_verticalVelocity = 0.0;
        m_horizontalVelocity = -0.010;
    }
    else if(ch==KEY_RIGHT && m_horizontalVelocity==0.0)
    {
        m_verticalVelocity = 0.0;
        m_horizontalVelocity = +0.010;
    }
    else if(ch==KEY_UP && m_verticalVelocity==0.0)
    {
        m_verticalVelocity = -0.005;
        m_horizontalVelocity = 0.0;
    }
    else if(ch==KEY_DOWN && m_verticalVelocity==0.0)
    {
        m_verticalVelocity = 0.005;
        m_horizontalVelocity = 0.0;
    }
}

void Snake::update()
{
    if(!m_gameOver)
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

        for(auto cell : m_cells)
        {
            if(cell.first == m_vertical_position && cell.second == m_horizontal_position)
            {
                m_gameOver = true;
            }
        }

        if(m_vertical_position <= 0 || m_vertical_position >= m_playWindowHeight || m_horizontal_position <= 0 || m_horizontal_position >= m_playWindowWidth)
        {
            m_gameOver = true;
        }
    }
}

void Snake::shiftCells()
{
    m_cells.emplace_back(make_pair(m_vertical_position,m_horizontal_position));
    // if the position of the last cell is different, don't get rid of the last cell
    // if they are the same, get it attached and generate a new random position for the target
    
    if((*(m_cells.begin())).first == m_target_vertical && (*(m_cells.begin())).second == m_target_horizontal)
    {
        m_target_horizontal = (rand() % (m_playWindowWidth-1))+1;
        m_target_vertical = (rand() % (m_playWindowHeight-1))+1;
        m_score++;
    }
    else
    {
        m_cells.pop_front();
    }
}

void Snake::drawWalls()
{
    Colors::activateColor(COLOR_RED,COLOR_WHITE);
    for(int i=0; i<=m_playWindowWidth; i++)
    {
        mvprintw(0,i," ");
        mvprintw(m_playWindowHeight,i," ");
    }

    for(int i=0; i<=m_playWindowHeight; i++)
    {
        mvprintw(i,0," ");
        mvprintw(i,m_playWindowWidth," ");
    }
    Colors::deactivateColor();
}