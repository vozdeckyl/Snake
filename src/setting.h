#ifndef SETTING_H
#define SETTING_H

#include <vector>
#include <string>

/*!
    @brief Represents a particular game setting and the options
*/
class Setting {
    public:
        /*!
            @brief Constructor
            @param name name of the game setting
            @param options list of options
        */
        Setting(std::string name, std::vector<std::string> options);

        ~Setting();

        /*!
            @brief Return the name of the setting
        */
        std::string getName() const;

        /*!
            @brief Returns the selected option
        */
        std::string getOption() const;

        /*!
            @brief Return the index of the selected option
        */
        int getOptionIndex() const;

        /*!
            @brief Changes the setting to its next option
        */
        void nextOption();

        /*!
            @brief Changes the setting to its previous option
        */
        void previousOption();

        /*!
            @brief Select the option of this setting
        */
        void selectOption(int option);

    private:
        std::string m_name;
        std::vector<std::string> m_options;
        int m_selection;
        int m_selection_max;  
};

#endif
