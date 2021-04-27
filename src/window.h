#ifndef WINDOW_H
#define WINDOW_H

#include <map>
#include <thread>
#include <mutex>
#include <ncurses.h>

#include "IDrawable.h"
#include "result.h"

using namespace std;


class Window {
    public:
        Window();
        ~Window();

        ObjectID addElement(IDrawable * element, unsigned int yPosition, unsigned int xPosition);
        Result * run();

    private:
        void graphicsLoop();
        void updateLoop();
        void notifyLoop();

        bool exit();
        void shutDown();

    private:
        map<ObjectID,IDrawable*> m_elements;
        ObjectID m_nextObjectID;
        int m_numOfRows;
        int m_numOfColumns;
        mutex m_mutex_exit;
        bool m_exit;
};

#endif