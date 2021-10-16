#include "setting.h"
#include <algorithm>

using namespace std;

Setting::Setting(string name, std::vector<std::string> options) : m_selection(0)
{
    m_name = std::move(name);
    m_options = std::move(options);
    m_selection_max = m_options.size()-1;
}

Setting::~Setting()
{
}

string Setting::getName() const
{
    return m_name;
}

int Setting::getOptionIndex() const
{
    return m_selection;
}

string Setting::getOption() const
{
    return m_options[m_selection];
}

void Setting::nextOption()
{
    if(m_selection < m_selection_max) m_selection++;
}

void Setting::previousOption()
{
    if (m_selection > 0) m_selection--; 
}

void Setting::selectOption(int option)
{
    m_selection = option;
}
