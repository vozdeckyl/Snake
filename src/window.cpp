#include "window.h"
#include "IDrawable.h"
#include "colors.h"
#include "result.h"
#include <thread>

Window::Window(IGraphicsEngine* engine) : m_exit(false), m_nextObjectID(0), m_killByKeyQ(false)
{
    m_engine = unique_ptr<IGraphicsEngine>(engine);
    m_engine->init();

    m_numOfRows = m_engine->numberOfRows();
    m_numOfColumns = m_engine->numberOfColumns();
}

Window::~Window()
{
    m_engine->endScreen();
}

ObjectID Window::addElement(IDrawable* element, int yPosition, int xPosition)
{
    element->setPosition(yPosition, xPosition);
    element->setOwner(this);
    m_elements.insert({m_nextObjectID++, std::unique_ptr<IDrawable>(element)});
    return (m_nextObjectID - 1);
}

Result Window::run()
{
    thread graphicsThread(&Window::graphicsLoop, this);
    thread updateThread(&Window::updateLoop, this);

    graphicsThread.join();
    updateThread.join();

    return Result(m_elements);
}

bool Window::exit()
{
    return m_exit.load();
}

void Window::kill()
{
    m_exit = true;
}

void Window::enableKillByKeyQ()
{
    m_killByKeyQ = true;
}

int Window::getHeight()
{
    return m_numOfRows;
}

int Window::getWidth()
{
    return m_numOfColumns;
}

void Window::graphicsLoop()
{
    /*
     * This function runs on a separate thread. It iterates through
     * all the drawable objects and calls draw() on them.
     */

    int input;

    int msFreeze = 33;
    std::chrono::time_point<std::chrono::steady_clock> tick = std::chrono::steady_clock::now();

    while (!exit())
    {
        input = m_engine->input();

        if (input == 'q' && m_killByKeyQ)
        {
            kill();
        }

        for (const auto& pair : m_elements)
        {
            if (pair.second->isNotifiable())
            {
                pair.second->notify(input);
            }
        }

        m_engine->prepareScreen();

        for (const auto& pair : m_elements)
        {
            if (pair.second->isVisible())
            {
                pair.second->draw(m_engine.get());
            }
        }

        m_engine->refreshScreen();

        std::chrono::duration<double, std::milli> elapsed{std::chrono::steady_clock::now() - tick};
        std::this_thread::sleep_until(tick + std::chrono::milliseconds(msFreeze));
        tick = std::chrono::steady_clock::now();
    }
}

void Window::updateLoop()
{
    int usFreeze = 1000;
    std::chrono::time_point<std::chrono::steady_clock> tick = std::chrono::steady_clock::now();
    while (!exit())
    {
        for (const auto& pair : m_elements)
        {
            if (pair.second->isUpdatable())
            {
                pair.second->update();
            }
        }

        std::chrono::duration<double, std::micro> elapsed{std::chrono::steady_clock::now() - tick};
        std::this_thread::sleep_until(tick + std::chrono::microseconds(usFreeze));
        tick = std::chrono::steady_clock::now();
    }
}
