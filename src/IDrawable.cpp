
#include "IDrawable.h"

IDrawable::IDrawable() : m_vertical_position(0), m_horizontal_position(0) {};

IDrawable::~IDrawable() {};

void IDrawable::setPosition(int vertical, int horizontal)
{
    m_vertical_position=vertical;
    m_horizontal_position=horizontal;
}

int IDrawable::getResult()
{
    return -1;
}


void IDrawable::setOwner(Window * owner)
{
    m_owner = owner;
}

