#include "settingsMenu.h"
#include "colors.h"
#include "window.h"
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include "fileManager.h"

using namespace std;

SettingsMenu::SettingsMenu() : IDrawable(), m_selector(0)
{
}


void SettingsMenu::loadFromFile(string fileName)
{
    int settings{0};
    int counter{0};
    try
    {
        ifstream settingsFile(fileName, ifstream::binary);
        settingsFile.read((char *) &settings, sizeof(int));
        settingsFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for(Setting & s : m_settings)
    {
        s.selectOption((settings >> 4*counter) & 0b1111);
        counter++;
    }
}

SettingsMenu::~SettingsMenu()
{
    this->saveSettings();
}

void SettingsMenu::draw(const IGraphicsEngine * engine)
{
    int counter{0};

    lock_guard<mutex> guard(m_selector_mutex);

    for(const Setting & setting : m_settings)
    {   
        Color textColor, backgroundColor;
        if(counter==m_selector)
        {
            // if the menu item is selected, decorate it:
            textColor = Color::white;
            backgroundColor = Color::red;
        }
        else
        {
            textColor = Color::white;
            backgroundColor = Color::black;
        }

        engine->draw((setting.getName() + "    <" + setting.getOption() + ">"),m_vertical_position+counter,m_horizontal_position-setting.getName().size(),textColor,backgroundColor);
        counter++;
    }
}

void SettingsMenu::moveSelectorUp()
{
    lock_guard<mutex> guard(m_selector_mutex);
    if(m_selector != 0) m_selector--;
}

void SettingsMenu::moveSelectorDown()
{
    int numOfEntries = m_settings.size();
    lock_guard<mutex> guard(m_selector_mutex);
    if(m_selector != numOfEntries-1) m_selector++;
}


void SettingsMenu::notify(int ch)
{
    if(ch==KEY_DOWN)
    {
        moveSelectorDown();
    }
    else if(ch==KEY_UP)
    {
        moveSelectorUp();
    }
    else if(ch == KEY_LEFT)
    {
        m_settings[m_selector].previousOption();
    }
    else if(ch == KEY_RIGHT)
    {
        m_settings[m_selector].nextOption();
    }
    else if(ch==10) /* 10 = KEY_ENTER */
    {
        m_owner->kill();
    }
}

void SettingsMenu::addSetting(Setting setting)
{
    m_settings.push_back(setting);
}

void SettingsMenu::saveSettings()
{
    int settingBinary{0};
    int counter{0};

    for(const Setting & setting : m_settings)
    {
        settingBinary = settingBinary | (setting.getOptionIndex() << 4*counter);
        counter++;
    }

    try
    {
        ofstream settingsFile(FileManager::getFilePath("settings"), ifstream::binary);
        settingsFile.write((const char *) &settingBinary,sizeof(int));
        settingsFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
