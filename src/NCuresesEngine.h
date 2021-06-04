#ifndef NCURSESENGINE_H
#define NCURSESENGINE_H

#include "IGraphicsEngine.h"

class NCursesEngine : public IGraphicsEngine {
public:
    NCursesEngine();
    ~NCursesEngine();
    void init() override;
    void draw(std::string text, int y, int x, Color text, Color background) override;
    void clear() override;
    int numberOfRows() override;
    int numberOfColumns() override;
};

#endif
