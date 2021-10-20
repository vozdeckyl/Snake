#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <utility>
#include <string>
#include "IDrawable.h"

enum class Direction {
    up,
    down,
    left,
    right
};

/*!
    @brief Object representing the actual snake and the game map
*/
class Snake : public IDrawable {
public:
    Snake(double verticalVelocity, double horizontalVelocity);
    ~Snake();
    
    void draw(const IGraphicsEngine * engine) override;
    bool isVisible() override {return true;};
    
    void update() override;
    bool isUpdatable() override {return true;};
    
    void notify(int ch) override;
    bool isNotifiable() override {return true;};
    
private:
    /*!
      @brief Shifts the whole snake
      
      If the last cell of the snake is on the target X, it gets extended.
    */
    void shiftCells();
    
    /*!
      @brief Draws the walls around the map
    */
    void drawWalls(const IGraphicsEngine * engine);
    
private:
    std::mutex m_cellsMutex;
    std::list<std::pair<int,int>> m_cells;
    
    std::mutex m_targetPositionMutex;
    int m_target_vertical;
    int m_target_horizontal;
    
    std::mutex m_gameOverMutex;
    bool m_gameOver;
    
    std::mutex m_scoreMutex;
    int m_score;
    
    std::mutex m_keyLockMutex;
    bool m_keyLock;
    
    std::mutex m_directionMutex;
    Direction m_direction; 
    
    // variables that do not need mutex locking
    int m_playWindowHeight;
    int m_playWindowWidth;
    std::string gameOverLabel;
    bool m_penetrableWalls;
    double m_verticalFractionPosition;
    double m_horizontalFractionPosition;
    double m_speed;
    int m_counter;
    int m_pace;
};

#endif
