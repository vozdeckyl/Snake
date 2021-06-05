#ifndef WINDOW_H
#define WINDOW_H

#include <map>
#include <mutex>
#include "objectid.h"
#include "IGraphicsEngine.h"

class IDrawable;
class Result;
using namespace std;

class Window {
    public:
        Window(IGraphicsEngine * engine);
        ~Window();

        ObjectID addElement(IDrawable * element, int yPosition, int xPosition);
        Result run();

        void kill();
        void enableKillByKeyQ();

        int getWidth();
        int getHeight();

    private:
        void graphicsLoop();
        void updateLoop();
        bool exit();

    private:
        map<ObjectID,IDrawable*> m_elements;
        ObjectID m_nextObjectID;
        int m_numOfRows;
        int m_numOfColumns;
        mutex m_mutex_exit;
        bool m_exit;
        bool m_killByKeyQ;
        IGraphicsEngine * m_engine;
};

#endif
