#include <gtest/gtest.h>
#include "counter.h"
#include "mockScreen.h"

TEST(counterTest, boolStates)
{
    auto c = new Counter();
    ASSERT_TRUE(c->isVisible());
    ASSERT_TRUE(c->isUpdatable());
    ASSERT_FALSE(c->isNotifiable());
}

TEST(couterTest, drawing)
{
    auto engine = new mockScreen(100,100);
    auto c = new Counter(1);
    c->setPosition(0,0);

    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('0',0,0));
    c->update();
    engine->clearScreen();
    c->draw(engine);
    ASSERT_TRUE(engine->testScreen('1',0,0));

    for(int i=0;i<9;i++) c->update();

    engine->clearScreen();
    c->draw(engine);

    ASSERT_TRUE(engine->testScreen('1',0,0));
    ASSERT_TRUE(engine->testScreen('0',0,1));
    ASSERT_TRUE(engine->testScreen(' ',1,1));
}
 
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}