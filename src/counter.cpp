#include <ncurses.h>
#include "counter.h"


Counter::Counter(unsigned int interval) : IDrawable(), m_counter(0), m_pulse_counter(0), m_interval(interval){}

Counter::Counter() : Counter(1000){}


Counter::~Counter() {}

void Counter::setInterval(unsigned int interval)
{
    m_interval = interval;
}

void Counter::draw()
{
    lock_guard<mutex> guard(m_counter_mutex);
    mvprintw(m_vertical_position,m_horizontal_position, to_string(m_counter).c_str());
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