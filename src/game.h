#ifndef GAME_H
#define GAME_H

#include "IDrawable.h"
#include "direction.h"
#include "snake.h"
#include <list>
#include <mutex>
#include <random>
#include <string>
#include <utility>

/*!
    @brief Object representing the actual snake and the game map
*/
class Game : public IDrawable
{
  public:
    Game(double verticalVelocity, double horizontalVelocity);
    ~Game();

    void draw(const IGraphicsEngine& engine) override;
    bool isVisible() override
    {
        return true;
    };

    void update() override;
    bool isUpdatable() override
    {
        return true;
    };

    void notify(int ch) override;
    bool isNotifiable() override
    {
        return true;
    };

  private:
    /*!
      @brief Shifts the whole snake

      If the last cell of the snake is on the target X, it gets extended.
    */
    void shiftCells();

    /*!
      @brief Draws the walls around the map
    */
    void drawWalls(const IGraphicsEngine& engine);

  private:
    std::mutex m_mutex;
    Snake m_snake;

    int m_target_vertical;
    int m_target_horizontal;
    bool m_gameOver;
    int m_score;
    bool m_keyLock;

    // variables that do not need mutex locking
    int m_playWindowHeight;
    int m_playWindowWidth;
    std::string gameOverLabel;
    bool m_penetrableWalls;
    int m_counter;
    int m_pace;
    std::default_random_engine m_generator;
    std::uniform_int_distribution<int> m_horizontalDistribution;
    std::uniform_int_distribution<int> m_verticalDistribution;
};

#endif
