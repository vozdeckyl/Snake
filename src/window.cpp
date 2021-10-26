#include <thread>
#include "IDrawable.h"
#include "result.h"
#include "window.h"
#include "colors.h"


Window::Window(IGraphicsEngine * engine) : m_exit(false), m_nextObjectID(0), m_killByKeyQ(false)
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

ObjectID Window::addElement(IDrawable * element, int yPosition, int xPosition)
{
    element->setPosition(yPosition,xPosition);
    element->setOwner(this);
    m_elements.insert({m_nextObjectID++,std::unique_ptr<IDrawable>(element)});
    return (m_nextObjectID-1);
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
    lock_guard<mutex> guard(m_mutex_exit);
    return m_exit;
}

void Window::kill()
{
    lock_guard<mutex> guard(m_mutex_exit);
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
  
    while(!exit())
    {
        input = m_engine->input();
       
        if(input=='q' && m_killByKeyQ)
        {
            kill();
        }
        
        for(const auto & pair : m_elements)
        {
            if(pair.second->isNotifiable())
            {
                pair.second->notify(input);
            }
        }
      
	m_engine->prepareScreen();
       
        for(const auto & pair : m_elements)
        {
            if(pair.second->isVisible())
            {
                pair.second->draw(m_engine.get());
            }
        }
	
        m_engine->refreshScreen();
    }
}

void Window::updateLoop()
{
    while(!exit())
    {
        for(const auto & pair : m_elements)
        {
            if(pair.second->isUpdatable())
            {
                pair.second->update();
            }
        }
        m_engine->wait(1);
    }
}
