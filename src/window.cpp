#include <ncurses.h>
#include <thread>
#include "window.h"

Window::Window() : m_exit(false)
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
    endwin();
}

void Window::addElement(IDrawable * element)
{
    m_elements.push_back(element);
}

void Window::run()
{
    thread graphicsThread(&Window::graphicsLoop, this);
    thread updateThread(&Window::updateLoop, this);
    thread notifyThread(&Window::notifyLoop, this);

    graphicsThread.join();
    updateThread.join();
    notifyThread.join();
}

bool Window::exit()
{
    lock_guard<mutex> guard(m_mutex_exit);
    return m_exit;
}

void Window::shutDown()
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
        
        for(IDrawable * element : m_elements)
        {
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
        for(IDrawable * element : m_elements)
        {
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
            shutDown();
        }
        
        for(IDrawable * element : m_elements)
        {
            if(element->isNotifiable())
            {
                element->notify(input);
            }
        }
    }
}