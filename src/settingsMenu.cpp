#include "settingsMenu.h"
#include "colors.h"
#include "window.h"
#include <ncurses.h>
#include <iostream>
#include <fstream>

using namespace std;

SettingsMenu::SettingsMenu() : IDrawable(), m_selector(0)
{
}


void SettingsMenu::loadFromFile(string fileName)
{
    ifstream settingsFile;

    try
    {
        ifstream settingsFile(fileName, ifstream::binary);
        
        int numberOfSettings;

        settingsFile.read((char *) &numberOfSettings, sizeof(int));
        
        for(int i=1;i<numberOfSettings;i++)
        {
            int nameLength;
            settingsFile.read((char *) &nameLength, sizeof(int));
            char * name = new char[nameLength+1];
            settingsFile.read(name,nameLength*sizeof(char));
            name[nameLength]='\0';

            int optionLength;
            settingsFile.read((char *) &optionLength, sizeof(int));
            char * option = new char[optionLength+1];
            settingsFile.read(option,optionLength*sizeof(char));
            option[optionLength]='\0';

            string nameString = to_string(*name);
            string optionString = to_string(*option);

            for(Setting s : m_settings)
            {
                if(s.getName() == nameString)
                {
                    s.selectOption(optionString);
                }
            }

            delete[] name;
            delete[] option;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

SettingsMenu::~SettingsMenu()
{
    this->saveSettings();
}

void SettingsMenu::draw()
{
    int counter{0};

    lock_guard<mutex> guard(m_selector_mutex);

    for(Setting setting : m_settings)
    {   
        if(counter==m_selector)
        {
            // if the menu item is selected, decorate it:
            Colors::activateColor(COLOR_WHITE,COLOR_RED);
        }
        mvprintw(m_vertical_position+counter,m_horizontal_position-setting.getName().size(), (setting.getName() + "    <" + setting.getOption() + ">").c_str());
        Colors::deactivateColor();
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
    try
    {
        ofstream settingsFile("../data/settings.bin", ifstream::binary);

        int numberOfSettings = m_settings.size();
        settingsFile.write((const char *) &numberOfSettings,sizeof(int));

        for(Setting setting : m_settings)
        {
            string name = setting.getName();
            int nameSize = name.size();
            string option = setting.getOption();
            int optionSize = option.size();
            settingsFile.write((const char *) &nameSize,sizeof(int));
            settingsFile.write(name.c_str(), nameSize*sizeof(char));
            settingsFile.write((const char *) &optionSize,sizeof(int));
            settingsFile.write(option.c_str(), optionSize*sizeof(char));
        }
        settingsFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}