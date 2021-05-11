#include "settingsMenu.h"
#include "colors.h"
#include "window.h"
#include <ncurses.h>

using namespace std;

SettingsMenu::SettingsMenu() : IDrawable(), m_selector(0), m_option_selector(0), m_option_selector_max(0)
{
}

SettingsMenu::~SettingsMenu()
{
}

void SettingsMenu::draw()
{
    int counter{0};

    lock_guard<mutex> guard(m_selector_mutex);

    for(Setting setting : m_settings)
    {
        //move(m_vertical_position+counter,m_horizontal_position);
        
        if(counter==m_selector)
        {
            // if the menu item is selected, decorate it:
            Colors::activateColor(COLOR_WHITE,COLOR_RED);
            mvprintw(m_vertical_position+counter,m_horizontal_position-1, ("< " + setting.getName() + " >").c_str());
            Colors::deactivateColor();
        }
        else
        {
            mvprintw(m_vertical_position+counter,m_horizontal_position, setting.getName().c_str());
        }
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
    else if(ch==10) /* 10 = KEY_ENTER */
    {
        m_owner->kill();
    }
}

void SettingsMenu::addSetting(Setting setting)
{
    m_settings.push_back(setting);
}