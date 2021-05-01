#include <thread>
#include <ncurses.h>
#include "IDrawable.h"
#include "result.h"
#include "window.h"


Window::Window() : m_exit(false), m_nextObjectID(0), m_killByKeyQ(false)
{
    initscr();
    clear();
    getmaxyx(stdscr, m_numOfRows, m_numOfColumns);
    start_color();
    curs_set(0);
    keypad(stdscr,TRUE);
    cbreak();
    noecho();

    //initialize all color settings
    init_pair(1,COLOR_WHITE,COLOR_RED);
    init_pair(2,COLOR_RED,COLOR_WHITE);
    init_pair(3,COLOR_BLACK,COLOR_BLACK);
}

Window::~Window()
{
    for(pair<ObjectID, IDrawable*> pair : m_elements)
    {
        IDrawable * element = pair.second;
        delete element;
    }
    clear();
    endwin();
}

ObjectID Window::addElement(IDrawable * element, int yPosition, int xPosition)
{
    element->setPosition(yPosition,xPosition);
    element->setOwner(this);
    m_elements.insert({m_nextObjectID++,element});
    return (m_nextObjectID-1);
}

Result Window::run()
{
    thread graphicsThread(&Window::graphicsLoop, this);
    thread updateThread(&Window::updateLoop, this);
    thread notifyThread(&Window::notifyLoop, this);

    graphicsThread.join();
    updateThread.join();
    notifyThread.join();

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
    while(!exit())
    {
        erase();

        
        attrset(COLOR_PAIR(3));
        box(stdscr, 0, 0);
        attrset(0);
        
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

        if(input=='q' && m_killByKeyQ)
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
