#include <ncurses.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include "snake.h"
#include "window.h"
#include "colors.h"
#include "scoreLogger.h"
#include "fileManager.h"

using namespace std;

Snake::Snake(double verticalVelocity, double horizontalVelocity) :
    IDrawable(),
    m_target_vertical(5),
    m_target_horizontal(5),
    m_gameOver(false),
    m_score(0),
    m_keyLock(false),
    m_penetrableWalls(true),
    m_pace(100),
    m_direction(Direction::right)
{
    gameOverLabel = string("* * * GAME OVER * * *");

    int settings{0};

    int mapSize{1};
    int speedSetting{1};
    int penetrableWalls;

    try
    {
        ifstream settingsFile(FileManager::getFilePath("settings"), ifstream::binary);
        settingsFile.read((char *) &settings, sizeof(int));
        settingsFile.close();

        mapSize = (settings >> 4*0) & 0b1111;
        speedSetting = (settings >> 4*1) & 0b1111;
        penetrableWalls = (settings >> 4*2) & 0b1111;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    

    switch (mapSize)
    {
    case 0:
        // small window
        m_playWindowHeight = 10;
        m_playWindowWidth = 30; 
        break;
    case 1:
        // medium window
        m_playWindowHeight = 20;
        m_playWindowWidth = 50; 
        break;
    case 2:
        // large window
        m_playWindowHeight = 30;
        m_playWindowWidth = 100;
        break;
    default:
        m_playWindowHeight = 20;
        m_playWindowWidth = 50;
        break;
    }

    switch(penetrableWalls)
    {
        case 0:
            m_penetrableWalls = true;
            break;

        case 1:
            m_penetrableWalls = false;
            break;
        
        default:
            m_penetrableWalls = true;
            break;
    }
    m_pace = (3-speedSetting)*100;
}


Snake::~Snake()
{
    ScoreLogger log;
    log.logScore(m_score);
}

void Snake::draw(const IGraphicsEngine * engine)
{
    lock_guard<mutex> guard(m_mutex);
    drawWalls(engine);
    engine->draw(("Score: " + to_string(m_score)),m_playWindowHeight+1,(int)m_playWindowWidth*0.5,Color::white,Color::black);
    engine->draw("X",m_target_vertical,m_target_horizontal,Color::black,Color::yellow);
    
    for(const pair<int,int> & cell : m_cells)
    {
	engine->draw(" ",cell.first,cell.second,Color::red,Color::green);
    }
    
    engine->draw(":",m_vertical_position,m_horizontal_position,Color::red,Color::green);
    
    if(m_gameOver)
    {
        engine->draw(gameOverLabel,(int) (0.5*m_playWindowHeight),(int) (0.5*(m_playWindowWidth-gameOverLabel.size())),Color::white,Color::black);
    }
}

void Snake::notify(int ch)
{
    lock_guard<mutex> guard(m_mutex);

    if(!m_keyLock)
    {	
        if(ch==KEY_LEFT && m_direction != Direction::right)
        {
	    m_direction = Direction::left;
            m_keyLock = true;
        }
        else if(ch==KEY_RIGHT && m_direction != Direction::left)
        {
            m_direction = Direction::right;
            m_keyLock = true;
        }
        else if(ch==KEY_UP && m_direction != Direction::down)
        {
            m_direction = Direction::up;
            m_keyLock = true;
        }
        else if(ch==KEY_DOWN && m_direction != Direction::up)
        {
            m_direction = Direction::down;
            m_keyLock = true;
        }
    }
}

void Snake::update()
{
    lock_guard<mutex> guard(m_mutex);
    if(!m_gameOver)
    {
	
	if(m_direction==Direction::left || m_direction==Direction::right)
	{
	    m_counter+=2;
	}
	else
	{
	    m_counter++;
	}

	if(m_counter>=m_pace)
	{
	    m_counter=0;
	    shiftCells();
	    if(m_direction==Direction::up)
	    {
		m_vertical_position--;
		m_keyLock = false;
	    }
	    else if(m_direction==Direction::down)
	    {
		m_vertical_position++;
		m_keyLock = false;
	    }
	    else if(m_direction==Direction::left)
	    {
		m_horizontal_position--;
		m_keyLock = false;
	    }
	    else if(m_direction==Direction::right)
	    {
		m_horizontal_position++;
		m_keyLock = false;
	    }
	}
	

	for(const auto & cell : m_cells)
	{
	    if(cell.first == m_vertical_position && cell.second == m_horizontal_position)
	    {
		m_gameOver = true;
	    }
	}
	
        if(m_vertical_position <= 0)
        {
            if(!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_vertical_position = m_playWindowHeight-1;
            }
        }
        else if(m_vertical_position >= m_playWindowHeight)
        {
            if(!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_vertical_position=1;
            }
        }

        if(m_horizontal_position <= 0)
        {
            if(!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_horizontal_position = m_playWindowWidth-1;
            }
        }
        else if(m_horizontal_position >= m_playWindowWidth)
        {
            if(!m_penetrableWalls)
            {
                m_gameOver = true;
            }
            else
            {
                m_horizontal_position = 1;
            }
        }
    }
}

void Snake::shiftCells()
{
    lock_guard<mutex> guard(m_mutex);
    m_cells.emplace_back(make_pair(m_vertical_position,m_horizontal_position));
    // if the position of the last cell is different, don't get rid of the last cell
    // if they are the same, get it attached and generate a new random position for the target
    if((*(m_cells.begin())).first == m_target_vertical && (*(m_cells.begin())).second == m_target_horizontal)
    {
        m_target_horizontal = (rand() % (m_playWindowWidth-1))+1;
        m_target_vertical = (rand() % (m_playWindowHeight-1))+1;
	lock_guard<mutex> guardScore(m_scoreMutex);
        m_score++;
    }
    else
    {
        m_cells.pop_front();
    }
}

void Snake::drawWalls(const IGraphicsEngine * engine)
{
    for(int i=0; i<=m_playWindowWidth; i++)
    {
        engine->draw(" ",0,i,Color::red,Color::white);
        engine->draw(" ",m_playWindowHeight,i,Color::red,Color::white);
    }

    for(int i=0; i<=m_playWindowHeight; i++)
    {
        engine->draw(" ",i,0,Color::red,Color::white);
        engine->draw(" ",i,m_playWindowWidth,Color::red,Color::white);
    }
}
