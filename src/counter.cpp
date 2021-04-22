#include <ncurses.h>
#include "counter.h"


Counter::Counter() : m_counter(0), m_pulse_counter(0), m_interval(1000),
                    m_vertical_position(0), m_horizontal_position(0) {}

Counter::~Counter() {}

void Counter::setPosition(unsigned int vertical, unsigned int horizontal)
{
    m_vertical_position = vertical;
    m_horizontal_position = horizontal;
}

void Counter::setInterval(unsigned int interval)
{
    m_interval = interval;
}

void Counter::draw()
{
    move(m_vertical_position,m_horizontal_position);
    lock_guard<mutex> guard(m_counter_mutex);
    addstr(to_string(m_counter).c_str());
}

void Counter::update()
{
    m_pulse_counter++;

    if(m_pulse_counter==m_interval)
    {
        m_pulse_counter=0;
        lock_guard<mutex> guard(m_counter_mutex);
        m_counter++;
    }   
}