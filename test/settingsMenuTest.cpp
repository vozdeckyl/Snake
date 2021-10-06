#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "settingsMenuTest.h"
#include "setting.h"
#include "mockScreen.h"

using namespace std;

TEST(settingsMenuTest, drawing)
{
    auto engine = new mockScreen(100,100);
    Setting setting1("1",{"A","B","C","D"});
    Setting setting2("2",{"A","B","C","D"});
    SettingsMenu m();
    m.addSetting(setting1);
    m.addSetting(setting2);
    m.setPosition(0,0);
    
    m.draw(engine);

    ASSERT_TRUE(engine.testScreen('1',0,0));
    ASSERT_TRUE(engine.testScreen('2',1,0));
    ASSERT_TRUE(engine.testScreen(' ',0,1));
    ASSERT_TRUE(engine.testScreen('<',0,5));
    ASSERT_TRUE(engine.testScreen('A',0,6));
    ASSERT_TRUE(engine.testScreen('>',0,7));

    ASSERT_TRUE(engine.testScreen('<',1,5));
    ASSERT_TRUE(engine.testScreen('A',1,6));
    ASSERT_TRUE(engine.testScreen('>',1,7));


    delete engine;
}



int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
