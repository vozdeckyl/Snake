#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <mutex>

using namespace std;

class Menu {
public:
    Menu(vector<string> entries);
    Menu();
    ~Menu();
    
    void addEntry(string entryText);
    void setPosition(unsigned int vertical, unsigned int horizontal);
    void show();
    void moveSelectorUp();
    void moveSelectorDown();

private:
    vector<string> m_entries;
    int m_selector;
    mutex m_selector_mutex;
    unsigned int m_vertical_position;
    unsigned int m_horizontal_position;

};

#endif