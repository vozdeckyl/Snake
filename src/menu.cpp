#include <ncurses.h>
#include <mutex>
#include "menu.h"
#include "window.h"
#include "colors.h"

using namespace std;


// constructors
Menu::Menu(vector<string> entries) : Menu()
{
    for(auto entry : entries)
    {
        m_entries.push_back(entry);
    }
}

Menu::Menu() : IDrawable(), m_selector(0){}

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


void Menu::draw(const IGraphicsEngine * engine)
{

    int counter{0};

    lock_guard<mutex> guard(m_selector_mutex);

    for(string entry : m_entries)
    {
        //move(m_vertical_position+counter,m_horizontal_position);
        
        if(counter==m_selector)
        {
            // if the menu item is selected, decorate it:
            /*
            Colors::activateColor(COLOR_WHITE,COLOR_RED);
            mvprintw(m_vertical_position+counter,m_horizontal_position-1, (">" + entry + "<").c_str());
            Colors::deactivateColor();
            */
            engine->draw((">" + entry + "<"),m_vertical_position+counter,m_horizontal_position-1,Color::white,Color::red);
        }
        else
        {
            //addstr(entry.c_str());
            //mvprintw(m_vertical_position+counter,m_horizontal_position, entry.c_str());
            engine->draw(entry,m_vertical_position+counter,m_horizontal_position,Color::white,Color::black);
        }
        counter++;
    }   
}

void Menu::notify(int ch)
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