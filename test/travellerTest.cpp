#include "traveller.h"
#include "mockScreen.h"
#include <gtest/gtest.h>

TEST(travellerTest, boolStates)
{
    auto traveller = new Traveller(1.0, 1.0);

    ASSERT_TRUE(traveller->isVisible());
    ASSERT_TRUE(traveller->isUpdatable());
    ASSERT_TRUE(traveller->isNotifiable());

    delete traveller;
}

TEST(travellerTest, drawing)
{
    auto engine = new mockScreen(100, 100);
    auto traveller = new Traveller(1.0, 1.0);
    traveller->setPosition(0, 0);

    traveller->draw(engine);
    ASSERT_TRUE(engine->testScreen('X', 0, 0));
    ASSERT_TRUE(engine->testScreen(' ', 0, 1));
    ASSERT_TRUE(engine->testScreen(' ', 1, 0));
    ASSERT_TRUE(engine->testScreen(' ', 1, 1));

    engine->clearScreen();

    traveller->setPosition(1, 1);

    traveller->draw(engine);
    ASSERT_TRUE(engine->testScreen(' ', 0, 0));
    ASSERT_TRUE(engine->testScreen(' ', 0, 1));
    ASSERT_TRUE(engine->testScreen(' ', 1, 0));
    ASSERT_TRUE(engine->testScreen('X', 1, 1));

    delete engine;
    delete traveller;
}

TEST(travellerTest, travelling)
{
    auto engine = new mockScreen(100, 100);
    auto traveller = new Traveller(1.0, 1.0);
    traveller->setPosition(0, 0);

    traveller->notify(KEY_RIGHT);

    traveller->draw(engine);
    ASSERT_TRUE(engine->testScreen('X', 0, 0));

    for (int i = 1; i < 102; i++)
    {
        traveller->update();
    }

    engine->clearScreen();
    traveller->draw(engine);
    ASSERT_TRUE(engine->testScreen('X', 0, 1));

    traveller->notify(KEY_LEFT);

    for (int i = 1; i < 102; i++)
    {
        traveller->update();
    }

    engine->clearScreen();
    traveller->draw(engine);
    ASSERT_TRUE(engine->testScreen('X', 0, 0));
    ASSERT_TRUE(engine->testScreen(' ', 0, 1));
    ASSERT_TRUE(engine->testScreen(' ', 1, 0));
    ASSERT_TRUE(engine->testScreen(' ', 1, 1));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
