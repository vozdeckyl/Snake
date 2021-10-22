#include "snake.h"

Snake::Snake(int startPositionY, int startPositionX, Direction startDirection)
{
}

Snake::Snake(int startPositionY, int startPositionX)
{
}

Snake::~Snake()
{
}

void Snake::draw(const IGraphicsEngine * engine)
{
}

int Snake::getLength()
{
    return -1;
}

int Snake::getHeadXposition()
{
    return -1;
}

int Snake::getHeadYposition()
{
    return -1;
}

Direction Snake::getDirection()
{
    return Direction::up;
}

void Snake::setDirection(Direction dir)
{
}

void Snake::advance()
{
}

void Snake::stretch()
{
}

void Snake::teleportHeadTo(int y, int x)
{
}

bool Snake::biteItself()
{
    return true;
}
