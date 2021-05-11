#ifndef SETTING_H
#define SETTING_H

#include <vector>
#include <string>

class Setting {
    public:
        Setting(std::string name, std::vector<std::string> options);
        ~Setting();

        std::string getName();
        std::vector<std::string> getOptions();
    
    private:
        std::string m_name;
        std::vector<std::string> m_options;    
};

#endif