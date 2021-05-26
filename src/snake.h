#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <utility>
#include <string>
#include "IDrawable.h"

class Snake : public IDrawable {
    public:
        Snake(double verticalVelocity, double horizontalVelocity);
        ~Snake();

        void draw() override;
        bool isVisible() override {return true;};

        void update() override;
        bool isUpdatable() override {return true;};

        void notify(int ch) override;
        bool isNotifiable() override {return true;};

    private:
        void shiftCells();
        void drawWalls();

    private:
        std::list<std::pair<int,int>> m_cells;
        double m_verticalFractionPosition;
        double m_horizontalFractionPosition;
        double m_verticalVelocity;
        double m_horizontalVelocity;
        double m_speed;
        int m_target_vertical;
        int m_target_horizontal;
        bool m_gameOver;
        int m_playWindowHeight;
        int m_playWindowWidth;
        std::string gameOverLabel;
        int m_score;
};

#endif