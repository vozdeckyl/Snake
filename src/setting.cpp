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

string Setting::getName()
{
    return m_name;
}

string Setting::getOption()
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

void Setting::selectOption(string option)
{
    auto iter = find(m_options.begin(), m_options.end(), option);
    if( iter != m_options.end())
    {
        int index = std::distance(m_options.begin(), iter);
        m_selection = index;
    }
}