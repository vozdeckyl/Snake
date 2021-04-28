#ifndef COUNTER_H
#define COUNTER_H

#include "IDrawable.h"

class Counter : public IDrawable {
public:
    Counter();
    Counter(unsigned int interval);
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

    std::mutex m_counter_mutex;
};

#endif