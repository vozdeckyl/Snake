#include "setting.h"

using namespace std;

Setting::Setting(string name, std::vector<std::string> options)
{
    m_name = std::move(name);
    m_options = std::move(options);
}

Setting::~Setting()
{
}

string Setting::getName()
{
    return m_name;
}

vector<string> Setting::getOptions()
{
    return m_options;
}