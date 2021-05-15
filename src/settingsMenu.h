#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "IDrawable.h"
#include "setting.h"
#include <vector>
#include <mutex>

class SettingsMenu : public IDrawable {
    public:
        SettingsMenu();
        ~SettingsMenu();
        void draw() override;
        bool isVisible() override {return true;}

        void update() override {};
        bool isUpdatable() override {return false;}

        void notify(int ch) override;
        bool isNotifiable() override {return true;}

        void addSetting(Setting setting);

        void moveSelectorDown();
        void moveSelectorUp();

    private:
        std::vector<Setting> m_settings;
        std::mutex m_selector_mutex;
        int m_selector;
};

#endif