#ifndef COUNTER_H
#define COUNTER_H

#include "IDrawable.h"
#include <mutex>

/*!
    @brief Drawable number whose value increases by one in a given interval.
*/
class Counter : public IDrawable {
public:
    Counter();
    
    /*!
        @brief Contructor
        @param interval the interval in miliseconds after which the counter is increased
    */
    Counter(unsigned int interval);

    ~Counter();

    /*!
        @brief Sets the interval (in miliseconds) after which the counter is updated
        @param intervalMS interval in miliseconds
    */
    void setInterval(unsigned int intervalMS);

    void draw(const IGraphicsEngine * engine) override;
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