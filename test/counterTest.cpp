#include <gtest/gtest.h>

#include "counter.h"
#include "mockScreen.h"

TEST(counterTest, boolStates)
{
    auto c = new Counter();
    ASSERT_TRUE(c->isVisible());
    ASSERT_TRUE(c->isUpdatable());
    ASSERT_FALSE(c->isNotifiable());

    delete c;
}

TEST(couterTest, drawing)
{
    auto engine = new mockScreen(100, 100);
    auto c = new Counter(1);
    c->setPosition(0, 0);

    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('0', 0, 0));
    c->update();
    engine->clearScreen();
    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('1', 0, 0));

    for (int i = 0; i < 9; i++)
        c->update();

    engine->clearScreen();
    c->draw(engine);

    ASSERT_TRUE(engine->testScreen('1', 0, 0));
    ASSERT_TRUE(engine->testScreen('0', 0, 1));
    ASSERT_TRUE(engine->testScreen(' ', 1, 1));

    delete engine;
    delete c;
}

TEST(counterTest, interval)
{
    auto c = new Counter();
    auto engine = new mockScreen(100, 100);
    c->setInterval(5);
    c->setPosition(0, 0);
    c->draw(engine);

    ASSERT_TRUE(engine->testScreen('0', 0, 0));

    for (int i = 0; i < 5; i++)
        c->update();
    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('1', 0, 0));

    for (int i = 0; i < 5; i++)
        c->update();
    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('2', 0, 0));

    c->setInterval(10);

    for (int i = 0; i < 5; i++)
        c->update();
    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('2', 0, 0));

    for (int i = 0; i < 5; i++)
        c->update();
    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('3', 0, 0));

    c->setInterval(1000);

    for (int i = 0; i < 1000; i++)
        c->update();
    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('4', 0, 0));

    delete c;
    delete engine;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
