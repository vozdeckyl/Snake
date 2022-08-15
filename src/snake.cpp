#include "snake.h"
#include <utility>

Snake::Snake(int startPositionY, int startPositionX, Direction startDirection)
    : m_headXposition(startPositionX), m_headYposition(startPositionY), m_direction(startDirection)
{
}

Snake::Snake(int startPositionY, int startPositionX) : Snake(startPositionY, startPositionX, Direction::right)
{
}

Snake::~Snake()
{
}

void Snake::draw(const IGraphicsEngine& engine)
{
    engine.draw(":", m_headYposition, m_headXposition, Color::red, Color::green);

    for (const std::pair<int, int>& cell : m_tail)
    {
        engine.draw(" ", cell.first, cell.second, Color::red, Color::green);
    }
}

int Snake::getLength()
{
    return m_tail.size() + 1;
}

int Snake::getHeadXposition()
{
    return m_headXposition;
}

int Snake::getHeadYposition()
{
    return m_headYposition;
}

Direction Snake::getDirection()
{
    return m_direction;
}

void Snake::setDirection(Direction dir)
{
    m_direction = dir;
}

void Snake::advance()
{
    m_tail.push_front(std::make_pair(m_headYposition, m_headXposition));
    m_tail.pop_back();

    switch (m_direction)
    {
    case Direction::up:
        m_headYposition--;
        break;
    case Direction::down:
        m_headYposition++;
        break;
    case Direction::left:
        m_headXposition--;
        break;
    case Direction::right:
        m_headXposition++;
        break;
    }
}

void Snake::stretch()
{
    m_tail.push_front(std::make_pair(m_headYposition, m_headXposition));

    switch (m_direction)
    {
    case Direction::up:
        m_headYposition--;
        break;
    case Direction::down:
        m_headYposition++;
        break;
    case Direction::left:
        m_headXposition--;
        break;
    case Direction::right:
        m_headXposition++;
        break;
    }
}

void Snake::teleportHeadTo(int y, int x)
{
    m_headYposition = y;
    m_headXposition = x;
}

bool Snake::biteItself()
{
    for (const std::pair<int, int>& cell : m_tail)
    {
        if (cell.first == m_headYposition && cell.second == m_headXposition)
        {
            return true;
        }
    }
    return false;
}
