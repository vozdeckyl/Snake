#include <gtest/gtest.h>

#include "fileManager.h"
#include "mockScreen.h"
#include "setting.h"
#include "settingsMenu.h"
#include <string>
#include <vector>

using namespace std;

TEST(settingsMenuTest, drawing)
{
    ASSERT_TRUE(system("touch settings.dat && rm settings.dat") != -1);
    ASSERT_TRUE(system("touch settings.dat") != -1);
    FileManager::addFile("settings", "settings.dat");
    auto engine = new mockScreen(100, 100);
    Setting setting1("1", {"A", "B", "C", "D"});
    Setting setting2("2", {"A", "B", "C", "D"});
    SettingsMenu menu;
    menu.addSetting(setting1);
    menu.addSetting(setting2);
    menu.setPosition(0, 1);

    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('1', 0, 0));
    ASSERT_TRUE(engine->testScreen('2', 1, 0));
    ASSERT_TRUE(engine->testScreen(' ', 0, 1));
    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('A', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    ASSERT_TRUE(engine->testScreen('<', 1, 5));
    ASSERT_TRUE(engine->testScreen('A', 1, 6));
    ASSERT_TRUE(engine->testScreen('>', 1, 7));

    delete engine;
}

TEST(settingsMenuTest, verticalSelection)
{
    ASSERT_TRUE(system("touch settings.dat && rm settings.dat") != -1);
    ASSERT_TRUE(system("touch settings.dat") != -1);
    auto engine = new mockScreen(100, 100);
    Setting setting("1", {"A", "B", "C", "D"});
    SettingsMenu menu;
    menu.addSetting(setting);
    menu.setPosition(0, 1);

    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('1', 0, 0));
    ASSERT_TRUE(engine->testScreen(' ', 1, 0));
    ASSERT_TRUE(engine->testScreen(' ', 0, 1));
    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('A', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    engine->clearScreen();
    menu.notify(KEY_RIGHT);
    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('B', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    engine->clearScreen();
    menu.notify(KEY_RIGHT);
    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('C', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    engine->clearScreen();
    menu.notify(KEY_LEFT);
    menu.notify(KEY_LEFT);
    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('A', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    delete engine;
}

TEST(settingsMenuTest, horizontalSelection)
{
    ASSERT_TRUE(system("touch settings.dat && rm settings.dat") != -1);
    ASSERT_TRUE(system("touch settings.dat") != -1);
    auto engine = new mockScreen(100, 100);
    Setting setting1("1", {"A", "B", "C", "D"});
    Setting setting2("2", {"A", "B", "C", "D"});
    SettingsMenu menu;
    menu.addSetting(setting1);
    menu.addSetting(setting2);
    menu.setPosition(0, 1);

    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('A', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    ASSERT_TRUE(engine->testScreen('<', 1, 5));
    ASSERT_TRUE(engine->testScreen('A', 1, 6));
    ASSERT_TRUE(engine->testScreen('>', 1, 7));

    engine->clearScreen();
    menu.notify(KEY_DOWN);
    menu.notify(KEY_RIGHT);
    menu.notify(KEY_RIGHT);
    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('A', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    ASSERT_TRUE(engine->testScreen('<', 1, 5));
    ASSERT_TRUE(engine->testScreen('C', 1, 6));
    ASSERT_TRUE(engine->testScreen('>', 1, 7));

    engine->clearScreen();
    menu.notify(KEY_LEFT);
    menu.notify(KEY_UP);
    menu.notify(KEY_RIGHT);
    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('B', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    ASSERT_TRUE(engine->testScreen('<', 1, 5));
    ASSERT_TRUE(engine->testScreen('B', 1, 6));
    ASSERT_TRUE(engine->testScreen('>', 1, 7));

    delete engine;
}

TEST(settingsMenuTest, loadingFile)
{
    ASSERT_TRUE(system("touch settings.dat && rm settings.dat") != -1);
    ASSERT_TRUE(system("echo A0 > settings.dat") != -1); // "A" = 0011 0000 0100 0001
    auto engine = new mockScreen(100, 100);
    Setting setting1("1", {"A", "B", "C", "D"});
    Setting setting2("2", {"A", "B", "C", "D", "E", "F", "G"});
    SettingsMenu menu;
    menu.addSetting(setting1);
    menu.addSetting(setting2);
    menu.setPosition(0, 1);
    menu.loadFromFile("settings.dat");

    menu.draw(engine);

    ASSERT_TRUE(engine->testScreen('<', 0, 5));
    ASSERT_TRUE(engine->testScreen('B', 0, 6));
    ASSERT_TRUE(engine->testScreen('>', 0, 7));

    ASSERT_TRUE(engine->testScreen('<', 1, 5));
    ASSERT_TRUE(engine->testScreen('E', 1, 6));
    ASSERT_TRUE(engine->testScreen('>', 1, 7));

    delete engine;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
