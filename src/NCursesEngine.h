#ifndef NCURSESENGINE_H
#define NCURSESENGINE_H

#include "IGraphicsEngine.h"

class NCursesEngine : public IGraphicsEngine {
    public:
        NCursesEngine();
        ~NCursesEngine();
        void init() override;
        void draw(std::string text, int y, int x, Color textColor, Color backgroundColor) override;
        void clear() override;
        int numberOfRows() override;
        int numberOfColumns() override;
    
    private:
        int m_rows;
        int m_columns;
};

#endif
