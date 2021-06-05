#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "IDrawable.h"
#include "setting.h"
#include <vector>
#include <mutex>

/*!
    @brief Drawable settings menu

    The settings can be changed by pressing left/right arrows.
*/
class SettingsMenu : public IDrawable {
    public:
        SettingsMenu();
        ~SettingsMenu();
        
        /*!
            @brief Loads the saved settings from a file
            @param fileName file path
        */
        void loadFromFile(std::string fileName);

        void draw(const IGraphicsEngine * engine) override;
        bool isVisible() override {return true;}

        void update() override {};
        bool isUpdatable() override {return false;}

        void notify(int ch) override;
        bool isNotifiable() override {return true;}

        /*!
            @brief add a setting to the setting menu
            @param setting setting to be added
        */
        void addSetting(Setting setting);

        /*!
            @brief move the selector up in the menu
        */
        void moveSelectorDown();

        /*!
            @brief move the selector down in the menu
        */
        void moveSelectorUp();

        /*!
            @brief save the settings into the file
        */
        void saveSettings();

    private:
        std::vector<Setting> m_settings;
        std::mutex m_selector_mutex;
        int m_selector;
};

#endif