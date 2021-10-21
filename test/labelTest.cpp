#include <gtest/gtest.h>
#include "label.h"
#include "mockScreen.h"

TEST(labelTest, boolStates)
{
    auto label = new Label("");
    ASSERT_TRUE(label->isVisible());
    ASSERT_FALSE(label->isUpdatable());
    ASSERT_FALSE(label->isNotifiable());
    
    delete label;
}

TEST(labelTest, drawing)
{
    auto engine = new mockScreen(100,100);
    auto label = new Label("All work and no play makes Jack a dull boy");
    label->setPosition(0,0);
    
    label->draw(engine);
    ASSERT_TRUE(engine->testScreen('A',0,0));
    ASSERT_TRUE(engine->testScreen('l',0,1));
    ASSERT_TRUE(engine->testScreen('l',0,2));
    ASSERT_TRUE(engine->testScreen(' ',0,3));
    ASSERT_TRUE(engine->testScreen('w',0,4));
    ASSERT_TRUE(engine->testScreen('o',0,5));
    ASSERT_TRUE(engine->testScreen('r',0,6));

    ASSERT_TRUE(engine->testScreen('y',0,41));
    ASSERT_TRUE(engine->testScreen(' ',0,42));
    
    delete engine;
    delete label;
}

TEST(labelTest, colors)
{
    auto engine = new mockScreen(100,100);
    auto label = new Label("A",Color::red,Color::white);
    label->setPosition(0,0);
    
    label->draw(engine);
    ASSERT_TRUE(engine->testScreen('A',0,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::white,0,0));
    ASSERT_TRUE(engine->testTextColor(Color::red,0,0));
    
    delete engine;
    delete label;
}
 
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
