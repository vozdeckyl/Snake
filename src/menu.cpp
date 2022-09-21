#include "menu.h"
#include "colors.h"
#include "window.h"
#include <ncurses.h>

using namespace std;

// constructors
Menu::Menu(vector<string> entries) : Menu()
{
    for (const string& entry : entries)
    {
        m_entries.push_back(entry);
    }
}

Menu::Menu() : IDrawable(), m_selector(0)
{
}

// copy constructor
Menu::Menu(const Menu& other) : Menu()
{
    m_entries = other.getEntries();
}

// destructor
Menu::~Menu()
{
}

void Menu::addEntry(string entry)
{
    m_entries.push_back(entry);
}

void Menu::draw(const IGraphicsEngine* engine)
{

    int counter{0};

    for (const string& entry : m_entries)
    {
        if (counter == m_selector.load())
        {
            engine->draw((">" + entry + "<"), m_vertical_position + counter, m_horizontal_position - 1, Color::white,
                         Color::red);
        }
        else
        {
            engine->draw(entry, m_vertical_position + counter, m_horizontal_position, Color::white, Color::black);
        }
        counter++;
    }
}

void Menu::notify(int ch)
{
    if (ch == KEY_DOWN)
    {
        moveSelectorDown();
    }
    else if (ch == KEY_UP)
    {
        moveSelectorUp();
    }
    else if (ch == 10) /* 10 = KEY_ENTER */
    {
        m_owner->kill();
    }
}

void Menu::moveSelectorUp()
{
    if (m_selector.load() != 0)
        m_selector--;
}

void Menu::moveSelectorDown()
{
    int numOfEntries = m_entries.size();
    if (m_selector.load() != numOfEntries - 1)
        m_selector++;
}

vector<string> Menu::getEntries() const
{
    return m_entries;
}
