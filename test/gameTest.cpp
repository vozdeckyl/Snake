#include <gtest/gtest.h>
#include "game.h"
#include "mockScreen.h"
#include "colors.h"
#include "fileManager.h"

TEST(gameTest, boolStates)
{   
    auto g = new Game(1.0,1.0);
    ASSERT_TRUE(g->isVisible());
    ASSERT_TRUE(g->isUpdatable());
    ASSERT_TRUE(g->isNotifiable());
    
    delete g;
}

TEST(gameTest, drawing)
{    
    auto engine = new mockScreen(100,100);
    auto g = new Game(1.0,1.0);

    g->draw(engine);
    g->update();

    ASSERT_TRUE(engine->testScreen(':',1,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,1,1));
    ASSERT_TRUE(engine->testTextColor(Color::red,1,1));
    
    ASSERT_TRUE(engine->testBackgroundColor(Color::white,0,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::white,0,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::white,1,0));

    ASSERT_TRUE(engine->testScreen(' ',2,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,2,2));

    ASSERT_TRUE(engine->testScreen(' ',1,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,1,2));

    ASSERT_TRUE(engine->testScreen(' ',2,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,2,1));
    
    delete engine;
    delete g;
}

TEST(gameTest,movement)
{
    auto engine = new mockScreen(100,100);
    auto g = new Game(1.0,1.0);
    
    g->draw(engine);

    ASSERT_TRUE(engine->testScreen(':',1,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,1,1));
    ASSERT_TRUE(engine->testTextColor(Color::red,1,1));

    engine->clearScreen();
    
    g->notify(KEY_RIGHT);
    for(int i=0;i<150;i++) g->update();
    g->draw(engine);

    ASSERT_TRUE(engine->testScreen(':',1,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,1,2));
    ASSERT_TRUE(engine->testTextColor(Color::red,1,2));
    ASSERT_TRUE(engine->testScreen(' ',1,1));

    
    engine->clearScreen();

    
    g->notify(KEY_DOWN);
    for(int i=0;i<300;i++) g->update();
    g->draw(engine);

    ASSERT_TRUE(engine->testScreen(':',2,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,2,2));
    ASSERT_TRUE(engine->testTextColor(Color::red,2,2));
    ASSERT_TRUE(engine->testScreen(' ',1,2));
    
    delete engine;
    delete g;
}

TEST(gameTest,target)
{
    auto engine = new mockScreen(100,100);
    auto g = new Game(1.0,1.0);

    g->notify(KEY_RIGHT);
    for(int i=0;i<150*4;i++) g->update();
    g->draw(engine);

    ASSERT_TRUE(engine->testScreen(':',1,5));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,1,5));
    ASSERT_TRUE(engine->testTextColor(Color::red,1,5));

    engine->clearScreen();
    
    g->notify(KEY_DOWN);
    for(int i=0;i<300*3;i++) g->update();
    g->draw(engine);

    ASSERT_TRUE(engine->testScreen(':',4,5));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,4,5));
    ASSERT_TRUE(engine->testTextColor(Color::red,4,5));

    ASSERT_TRUE(engine->testScreen('X',5,5));

    engine->clearScreen();
    
    for(int i=0;i<300;i++) g->update();
    g->draw(engine);

    ASSERT_TRUE(engine->testScreen(':',5,5));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,5,5));
    ASSERT_TRUE(engine->testTextColor(Color::red,5,5));

    engine->clearScreen();
    
    for(int i=0;i<300;i++) g->update();
    g->draw(engine);

    ASSERT_TRUE(engine->testScreen(':',6,5));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,6,5));
    ASSERT_TRUE(engine->testTextColor(Color::red,6,5));

    ASSERT_TRUE(engine->testScreen(' ',5,5));
    ASSERT_TRUE(engine->testBackgroundColor(Color::green,5,5));
    
    delete engine;
    delete g;
}
 
int main(int argc, char **argv) 
{
    FileManager::addFile("settings",std::vector<std::string>({"../data/settings.bin"}));
    FileManager::addFile("logo",std::vector<std::string>({"../data/logo.txt"}));
    FileManager::addFile("scores",std::vector<std::string>({"../data/scores.bin"}));
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
