#include <gtest/gtest.h>
#include "game.h"
#include "mockScreen.h"

TEST(gameTest, boolStates)
{
    auto g = new Game(1.0,1.0);
    ASSERT_TRUE(g->isVisible());
    ASSERT_TRUE(g->isUpdatable());
    ASSERT_TRUE(g->isNotifiable());
    
    delete g;
}

TEST(couterTest, drawing)
{
    auto engine = new mockScreen(100,100);
    auto g = new Game(1.0,1.0);

    g->draw(engine);
    //ASSERT_TRUE(engine->testScreen('0',0,0));
    g->update();

    /*
    ASSERT_TRUE(engine->testScreen('1',0,0));
    ASSERT_TRUE(engine->testScreen('0',0,1));
    ASSERT_TRUE(engine->testScreen(' ',1,1));
    */
    
    delete engine;
    delete g;
}
 
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
