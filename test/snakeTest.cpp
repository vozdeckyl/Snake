#include <gtest/gtest.h>

#include "mockScreen.h"
#include "snake.h"

TEST(snakeTest, boolStates)
{
    auto snake = new Snake(1, 1);
    ASSERT_TRUE(snake->isVisible());
    ASSERT_FALSE(snake->isUpdatable());
    ASSERT_FALSE(snake->isNotifiable());

    delete snake;
}

TEST(snakeTest, drawing)
{
    auto engine = new mockScreen(100, 100);
    auto snake = new Snake(1, 1);

    snake->draw(engine);
    ASSERT_TRUE(engine->testScreen(':', 1, 1));
    ASSERT_TRUE(engine->testTextColor(Color::red, 1, 1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 1));

    ASSERT_TRUE(snake->getLength() == 1);

    delete engine;
    delete snake;
}

TEST(snakeTest, moving)
{
    auto engine = new mockScreen(100, 100);
    auto snake = new Snake(1, 1, Direction::right);

    snake->draw(engine);
    ASSERT_TRUE(engine->testScreen(':', 1, 1));
    ASSERT_TRUE(engine->testTextColor(Color::red, 1, 1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 1));

    engine->clearScreen();

    snake->advance();
    snake->draw(engine);

    ASSERT_TRUE(engine->testScreen(':', 1, 2));
    ASSERT_TRUE(engine->testTextColor(Color::red, 1, 2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 2));
    ASSERT_TRUE(engine->testScreen(' ', 1, 1));
    ASSERT_TRUE(engine->testTextColor(Color::white, 1, 1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black, 1, 1));

    delete engine;
    delete snake;
}

TEST(snakeTest, direction)
{
    auto engine = new mockScreen(100, 100);
    auto snake = new Snake(1, 1, Direction::down);

    snake->advance();
    snake->draw(engine);

    ASSERT_TRUE(engine->testScreen(':', 2, 1));
    ASSERT_TRUE(engine->testTextColor(Color::red, 2, 1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 2, 1));
    ASSERT_TRUE(engine->testScreen(' ', 1, 1));
    ASSERT_TRUE(engine->testTextColor(Color::white, 1, 1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black, 1, 1));

    engine->clearScreen();
    snake->setDirection(Direction::right);
    snake->advance();

    snake->draw(engine);
    ASSERT_TRUE(engine->testScreen(':', 2, 2));
    ASSERT_TRUE(engine->testTextColor(Color::red, 2, 2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 2, 2));
    ASSERT_TRUE(engine->testScreen(' ', 2, 1));
    ASSERT_TRUE(engine->testTextColor(Color::white, 2, 1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black, 2, 1));

    engine->clearScreen();
    snake->advance();
    snake->setDirection(Direction::down);
    snake->advance();
    snake->setDirection(Direction::left);
    snake->advance();
    snake->setDirection(Direction::up);
    snake->advance();

    snake->draw(engine);
    ASSERT_TRUE(engine->testScreen(':', 2, 2));
    ASSERT_TRUE(engine->testTextColor(Color::red, 2, 2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 2, 2));

    delete engine;
    delete snake;
}

TEST(snakeTest, stretch)
{
    auto engine = new mockScreen(100, 100);
    auto snake = new Snake(1, 1);

    snake->stretch();
    snake->stretch();

    snake->draw(engine);
    ASSERT_TRUE(engine->testScreen(':', 1, 3));
    ASSERT_TRUE(engine->testTextColor(Color::red, 1, 3));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 3));
    ASSERT_TRUE(engine->testScreen(' ', 1, 1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 1));
    ASSERT_TRUE(engine->testScreen(' ', 1, 2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 2));

    delete engine;
    delete snake;
}

TEST(snakeTest, biting)
{
    auto engine = new mockScreen(100, 100);
    auto snake = new Snake(1, 1, Direction::right);

    ASSERT_FALSE(snake->biteItself());

    snake->stretch();
    snake->stretch();
    snake->stretch();
    snake->stretch();
    snake->stretch();
    snake->stretch();

    ASSERT_FALSE(snake->biteItself());

    snake->setDirection(Direction::down);
    snake->advance();
    snake->setDirection(Direction::left);
    snake->advance();
    snake->setDirection(Direction::up);
    snake->advance();

    ASSERT_TRUE(snake->biteItself());

    delete engine;
    delete snake;
}

TEST(snakeTest, teleport)
{
    auto engine = new mockScreen(100, 100);
    auto snake = new Snake(1, 1, Direction::right);

    snake->stretch();
    snake->stretch();
    snake->stretch();
    snake->stretch();

    snake->teleportHeadTo(20, 20);

    snake->advance();

    snake->draw(engine);

    ASSERT_TRUE(engine->testScreen(':', 20, 21));
    ASSERT_TRUE(engine->testTextColor(Color::red, 20, 21));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 20, 21));
    ASSERT_TRUE(engine->testScreen(' ', 20, 20));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 20, 20));
    ASSERT_TRUE(engine->testScreen(' ', 20, 19));
    ASSERT_TRUE(engine->testTextColor(Color::white, 20, 19));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black, 20, 19));

    ASSERT_TRUE(engine->testScreen(' ', 1, 2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 2));
    ASSERT_TRUE(engine->testScreen(' ', 1, 3));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 3));
    ASSERT_TRUE(engine->testScreen(' ', 1, 4));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green, 1, 4));

    ASSERT_TRUE(engine->testScreen(' ', 1, 6));
    ASSERT_TRUE(engine->testTextColor(Color::white, 1, 6));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black, 1, 6));

    ASSERT_TRUE(engine->testScreen(' ', 1, 7));
    ASSERT_TRUE(engine->testTextColor(Color::white, 1, 7));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black, 1, 7));

    delete engine;
    delete snake;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
