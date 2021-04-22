#include <iostream>
#include "SnakeConfig.h"
#include "menu.h"
#include <ncurses.h>
#include <thread>

using namespace std;


void graphics_loop(vector<IDrawable*> drawableElements, bool * exit)
{
    initscr();
    start_color();
    curs_set(0);
    clear();
    while(!(*exit))
    {
        erase();
        
        for(IDrawable * element : drawableElements)
        {
            element->draw();
        }

        refresh();
        napms(1);
    }
}

int main()
{
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << endl;

    Menu * myMenu = new Menu({"Play","Game Settings","Exit","Test Option 7","balala ub"});
    myMenu->setPosition(15,10);

    Menu * myOtherMenu = new Menu({"A","B","C","D"});

    vector<IDrawable*> elements;
    elements.push_back(myMenu);
    elements.push_back(myOtherMenu);
    
    int input;
    bool exit{false};

    thread g_thread(graphics_loop, elements, &exit);

    initscr();
    start_color();
    curs_set(0);
    keypad(stdscr,TRUE);
    while(true)
    {   
        input = getch();

        if(input=='q')
        {
            exit = true;
            break;
        }
        else if(input==KEY_DOWN)
        {
            myMenu->moveSelectorDown();
        }
        else if(input==KEY_UP)
        {
            myMenu->moveSelectorUp();
        }
        
    }

    g_thread.join();

    endwin();   
}