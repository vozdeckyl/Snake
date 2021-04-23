#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <mutex>
#include "IDrawable.h"

using namespace std;

class Window {
    public:
        Window();
        ~Window();

        void addElement(IDrawable * element);
        void run();
        bool exit();
        void shutDown();

    private:
        void graphicsLoop();
        void updateLoop();
        void notifyLoop();

    private:
        vector<IDrawable*> m_elements;
        int m_numOfRows;
        int m_numOfColumns;
        mutex m_mutex_exit;
        bool m_exit;
};

#endif