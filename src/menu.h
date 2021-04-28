#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include "IDrawable.h"

class Menu : public IDrawable{
public:
    Menu(std::vector<std::string> entries);
    Menu();
    Menu(const Menu & other);
    ~Menu();

    void draw() override;
    bool isVisible() override {return true;}

    void update() override {};
    bool isUpdatable() override {return false;}

    void notify(int ch) override;
    bool isNotifiable() override {return true;}

    virtual int getResult() override {return m_selector;}

    void addEntry(std::string entryText);
    void moveSelectorUp();
    void moveSelectorDown();
    std::vector<std::string> getEntries() const;

private:
    std::vector<std::string> m_entries;
    int m_selector;
    std::mutex m_selector_mutex;
};

#endif