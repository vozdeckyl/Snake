#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <vector>
#include <string>
#include <mutex>
#include "IDrawable.h"

using namespace std;

class Menu : public IDrawable{
public:
    Menu(vector<string> entries);
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

    void addEntry(string entryText);
    void moveSelectorUp();
    void moveSelectorDown();
    vector<string> getEntries() const;

private:
    vector<string> m_entries;
    int m_selector;
    mutex m_selector_mutex;
};

#endif