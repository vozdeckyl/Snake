#ifndef WINDOW_H
#define WINDOW_H

#include <map>
#include <mutex>
#include "objectid.h"


class IDrawable;
class Result;
using namespace std;

class Window {
    public:
        Window();
        ~Window();

        ObjectID addElement(IDrawable * element, int yPosition, int xPosition);
        Result * run();

        void kill();

    private:
        void graphicsLoop();
        void updateLoop();
        void notifyLoop();
        bool exit();

    private:
        map<ObjectID,IDrawable*> m_elements;
        ObjectID m_nextObjectID;
        int m_numOfRows;
        int m_numOfColumns;
        mutex m_mutex_exit;
        bool m_exit;
};

#endif