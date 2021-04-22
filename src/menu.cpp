#include "menu.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

// constructors
Menu::Menu(vector<string> entries) : Menu()
{
    for(auto entry : entries)
    {
        m_entries.push_back(entry);
    }
}

Menu::Menu() : m_selector(0), m_vertical_position(0), m_horizontal_position(0) {}

//copy constructor
Menu::Menu(const Menu & other) : Menu()
{
    m_entries = other.getEntries();
}

//destructor
Menu::~Menu(){}

void Menu::addEntry(string entry)
{
    m_entries.push_back(entry);
}

void Menu::setPosition(unsigned int vertical, unsigned int horizontal)
{
    m_vertical_position = vertical;
    m_horizontal_position = horizontal;
}

void Menu::draw()
{
    init_pair(1,COLOR_WHITE,COLOR_RED);

    int counter{0};

    lock_guard<mutex> guard(m_selector_mutex);

    for(string entry : m_entries)
    {
        move(m_vertical_position+counter,m_horizontal_position);
        
        if(counter==m_selector)
        {
            // if the menu item is selected, decorate it:
            attrset(COLOR_PAIR(1));
            addstr(">");
            addstr(entry.c_str());
            addstr("<");
            attrset(0); 
        }
        else
        {
            addstr(entry.c_str());
        }
        counter++;
    }   
}

void Menu::moveSelectorUp()
{
    lock_guard<mutex> guard(m_selector_mutex);
    if(m_selector != 0) m_selector--;
}

void Menu::moveSelectorDown()
{
    int numOfEntries = m_entries.size();
    lock_guard<mutex> guard(m_selector_mutex);
    if(m_selector != numOfEntries-1) m_selector++;
}

vector<string> Menu::getEntries() const
{
    return m_entries;
}