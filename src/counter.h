#ifndef COUNTER_H
#define COUNTER_H

#include <mutex>
#include "IDrawable.h"
#include "IUpdatable.h"

using namespace std;

class Counter : public IDrawable, public IUpdatable{
public:
    Counter();
    ~Counter();
    
    void setPosition(unsigned int vertical, unsigned int horizontal);
    void setInterval(unsigned int intervalMS);

    void draw() override;
    void update() override;

private:
    unsigned int m_counter;
    unsigned int m_pulse_counter;
    unsigned int m_interval;

    mutex m_counter_mutex;

    unsigned int m_vertical_position;
    unsigned int m_horizontal_position;
};

#endif