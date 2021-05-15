#ifndef SETTING_H
#define SETTING_H

#include <vector>
#include <string>

class Setting {
    public:
        Setting(std::string name, std::vector<std::string> options);
        ~Setting();

        std::string getName();
        std::string getOption();

        void nextOption();
        void previousOption();
        void selectOption(std::string option);

    private:
        std::string m_name;
        std::vector<std::string> m_options;
        int m_selection;
        int m_selection_max;  
};

#endif