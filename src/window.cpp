#include <thread>
#include <ncurses.h>
#include "IDrawable.h"
#include "result.h"
#include "window.h"


Window::Window() : m_exit(false), m_nextObjectID(0)
{
    initscr();
	getmaxyx(stdscr, m_numOfRows, m_numOfRows);
    start_color();
    curs_set(0);
    keypad(stdscr,TRUE);
    cbreak();
    noecho();
}

Window::~Window()
{
    for(pair<ObjectID, IDrawable*> pair : m_elements)
    {
        IDrawable * element = pair.second;
        delete element;
    }
    endwin();
}

ObjectID Window::addElement(IDrawable * element, int yPosition, int xPosition)
{
    element->setPosition(yPosition,xPosition);
    element->setOwner(this);
    m_elements.insert({m_nextObjectID++,element});
    return (m_nextObjectID-1);
}

Result * Window::run()
{
    thread graphicsThread(&Window::graphicsLoop, this);
    thread updateThread(&Window::updateLoop, this);
    thread notifyThread(&Window::notifyLoop, this);

    graphicsThread.join();
    updateThread.join();
    notifyThread.join();

    return new Result(m_elements);
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

void Window::graphicsLoop()
{
    /*
     * This function runs on a separate thread. It iterates through
     * all the drawable objects and calls draw() on them.
     */

    noecho();
    while(!exit())
    {
        erase();
        
        for(pair<ObjectID, IDrawable*> pair : m_elements)
        {
            IDrawable * element = pair.second;
            if(element->isVisible())
            {
                element->draw();
            }
        }

        refresh();
        napms(1);
    }
}

void Window::updateLoop()
{
    while(!exit())
    {
        for(pair<ObjectID, IDrawable*> pair : m_elements)
        {
            IDrawable * element = pair.second;
            if(element->isUpdatable())
            {
                element->update();
            }
        }
        napms(1);
    }
}

void Window::notifyLoop()
{
    int input;

    while(!exit())
    {   
        input = getch();

        if(input=='q')
        {
            kill();
        }
        
        for(pair<ObjectID, IDrawable*> pair : m_elements)
        {
            IDrawable * element = pair.second;
            if(element->isNotifiable())
            {
                element->notify(input);
            }
        }
    }
}