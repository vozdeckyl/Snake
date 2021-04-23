#ifndef COUNTER_H
#define COUNTER_H

#include <mutex>
#include "IDrawable.h"

using namespace std;

class Counter : public IDrawable {
public:
    Counter();
    ~Counter();

    void setInterval(unsigned int intervalMS);

    void draw() override;
    bool isVisible() override {return true;};

    void update() override;
    bool isUpdatable() override {return true;};

    void notify(int ch) override {};
    bool isNotifiable() override {return false;};

private:
    unsigned int m_counter;
    unsigned int m_pulse_counter;
    unsigned int m_interval;

    mutex m_counter_mutex;
};

#endif