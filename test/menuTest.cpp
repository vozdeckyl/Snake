#include <gtest/gtest.h>

#include "menu.h"
#include "mockScreen.h"
#include <string>
#include <vector>

TEST(menuTest, boolStates)
{
    auto menu = new Menu();
    ASSERT_TRUE(menu->isVisible());
    ASSERT_FALSE(menu->isUpdatable());
    ASSERT_TRUE(menu->isNotifiable());
    
    delete menu;
}

TEST(menuTest, drawing)
{
    auto engine = new mockScreen(100,100);
    auto menu = new Menu({"A","B","C","D"});
    menu->setPosition(1,1);
    
    menu->draw(engine);
    ASSERT_TRUE(engine->testScreen('A',1,1));
    ASSERT_TRUE(engine->testScreen('B',2,1));
    ASSERT_TRUE(engine->testScreen('C',3,1));
    ASSERT_TRUE(engine->testScreen('D',4,1));

    ASSERT_TRUE(engine->testScreen('>',1,0));
    ASSERT_TRUE(engine->testScreen('<',1,2));
    
    
    ASSERT_TRUE(engine->testTextColor(Color::white,1,0));
    ASSERT_TRUE(engine->testTextColor(Color::white,1,2));
    ASSERT_TRUE(engine->testTextColor(Color::white,1,1));
    ASSERT_TRUE(engine->testTextColor(Color::white,2,1));
    ASSERT_TRUE(engine->testTextColor(Color::white,3,1));
    ASSERT_TRUE(engine->testTextColor(Color::white,4,1));

    ASSERT_TRUE(engine->testBackgroundColor(Color::red,1,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,1,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,1,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,2,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,3,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,4,1));
    
    delete engine;
    delete menu;
}

TEST(menuTest, selection)
{
    auto engine = new mockScreen(100,100);
    auto menu = new Menu({"A","B","C","D"});
    menu->setPosition(1,1);
    
    menu->draw(engine);
    ASSERT_TRUE(engine->testScreen('A',1,1));
    ASSERT_TRUE(engine->testScreen('B',2,1));
    ASSERT_TRUE(engine->testScreen('C',3,1));
    ASSERT_TRUE(engine->testScreen('D',4,1));

    ASSERT_TRUE(engine->testScreen('>',1,0));
    ASSERT_TRUE(engine->testScreen('<',1,2));
    ASSERT_TRUE(menu->getResult()==0);

    engine->clearScreen();
    menu->moveSelectorDown();
    menu->draw(engine);

    ASSERT_TRUE(engine->testScreen(' ',1,0));
    ASSERT_TRUE(engine->testScreen(' ',1,2));
    ASSERT_TRUE(engine->testScreen('>',2,0));
    ASSERT_TRUE(engine->testScreen('<',2,2));
    ASSERT_TRUE(menu->getResult()==1);
    
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,1,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,1,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,1,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,2,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,2,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,2,1));
    
    engine->clearScreen();
    menu->moveSelectorDown();
    menu->draw(engine);

    ASSERT_TRUE(engine->testScreen(' ',2,0));
    ASSERT_TRUE(engine->testScreen(' ',2,2));
    ASSERT_TRUE(engine->testScreen('>',3,0));
    ASSERT_TRUE(engine->testScreen('<',3,2));
    ASSERT_TRUE(menu->getResult()==2);

    ASSERT_TRUE(engine->testBackgroundColor(Color::black,2,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,2,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,2,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,3,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,3,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,3,1));
    
    engine->clearScreen();
    menu->moveSelectorDown();
    menu->draw(engine);

    ASSERT_TRUE(engine->testScreen(' ',3,0));
    ASSERT_TRUE(engine->testScreen(' ',3,2));
    ASSERT_TRUE(engine->testScreen('>',4,0));
    ASSERT_TRUE(engine->testScreen('<',4,2));
    ASSERT_TRUE(menu->getResult()==3);

    ASSERT_TRUE(engine->testBackgroundColor(Color::black,3,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,3,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,3,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,4,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,4,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,4,1));
    
    engine->clearScreen();
    menu->moveSelectorDown();
    menu->draw(engine);

    ASSERT_TRUE(engine->testScreen(' ',3,0));
    ASSERT_TRUE(engine->testScreen(' ',3,2));
    ASSERT_TRUE(engine->testScreen('>',4,0));
    ASSERT_TRUE(engine->testScreen('<',4,2));
    ASSERT_TRUE(menu->getResult()==3);

    ASSERT_TRUE(engine->testBackgroundColor(Color::black,3,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,3,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::black,3,1));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,4,0));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,4,2));
    ASSERT_TRUE(engine->testBackgroundColor(Color::red,4,1));

    engine->clearScreen();
    menu->moveSelectorUp();
    menu->draw(engine);
    
    ASSERT_TRUE(engine->testScreen('>',3,0));
    ASSERT_TRUE(engine->testScreen('<',3,2));
    ASSERT_TRUE(menu->getResult()==2);

    engine->clearScreen();
    menu->moveSelectorUp();
    menu->draw(engine);

    ASSERT_TRUE(engine->testScreen('>',2,0));
    ASSERT_TRUE(engine->testScreen('<',2,2));
    ASSERT_TRUE(menu->getResult()==1);

    engine->clearScreen();
    menu->moveSelectorUp();
    menu->draw(engine);

    ASSERT_TRUE(engine->testScreen('>',1,0));
    ASSERT_TRUE(engine->testScreen('<',1,2));
    ASSERT_TRUE(menu->getResult()==0);

    engine->clearScreen();
    menu->moveSelectorUp();
    menu->draw(engine);

    ASSERT_TRUE(engine->testScreen('>',1,0));
    ASSERT_TRUE(engine->testScreen('<',1,2));
    ASSERT_TRUE(menu->getResult()==0);
    
    
    delete engine;
    delete menu;
}

TEST(menuTest, addingEntries)
{
    auto menu = new Menu();
    menu->addEntry("A");
    menu->addEntry("B");
    menu->addEntry("C");
    menu->addEntry("D");

    std::vector<std::string> entries = menu->getEntries();

    ASSERT_TRUE(entries[0]=="A");
    ASSERT_TRUE(entries[1]=="B");
    ASSERT_TRUE(entries[2]=="C");
    ASSERT_TRUE(entries[3]=="D");

    delete menu;
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
