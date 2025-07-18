#ifndef SNAKE_H
#define SNAKE_H

#include "IDrawable.h"
#include "direction.h"
#include <list>
#include <utility>

/*!
    @brief Class representing the actual snake
*/
class Snake : public IDrawable
{
  public:
    /*!
      @brief Constructor
      @param startPositionY Starting vertical position
      @param startPositionX Starting horizontal position
      @param startDirection Direction in which the snake starts moving at the beginning
    */
    Snake(int startPositionY, int startPositionX, Direction startDirection);

    /*!
      @brief Constructor
      @param startPositionY Starting vertical position
      @param startPositionX Starting horizontal position
    */
    Snake(int startPositionY, int startPositionX);

    ~Snake();

    void draw(const IGraphicsEngine* engine) override;
    bool isVisible() override
    {
        return true;
    };

    void update() override {};
    bool isUpdatable() override
    {
        return false;
    };

    void notify(int ch) override {};
    bool isNotifiable() override
    {
        return false;
    };

    /*!
      @brief Returns the snake length - i.e. the number of cells
    */
    int getLength();

    /*!
      @brief Returns the horizontal position of the snake's first cell (head)
    */
    int getHeadXposition();

    /*!
      @brief Returns the vertical position of the snake's first cell (head)
    */
    int getHeadYposition();

    /*!
      @brief Returns the direction the snake is moving
    */
    Direction getDirection();

    /*!
      @brief Sets the snake's direction
      @param dir Snake's direction
    */
    void setDirection(Direction dir);

    /*!
      @brief Moves the whole snake in the direction it's facing
    */
    void advance();

    /*!
      @brief Moves the head in the snake's direction and adds one cell behind the head while leaving the rest of the
      body still
    */
    void stretch();

    /*!
      @brief Move the head to a completely random location
      @param y new vertical position of snake's head
      @param x new horizontal position of snake's head
    */
    void teleportHeadTo(int y, int x);

    /*!
      @brief Check if the snake is not biting itself - i.e. the head is at the same coordinate as one of its cells
    */
    bool biteItself();

  private:
    Direction m_direction;
    int m_headXposition;
    int m_headYposition;
    std::list<std::pair<int, int>> m_tail;
};

#endif
