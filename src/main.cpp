#include <iostream>
#include "SnakeConfig.h"
#include "menu.h"
#include <ncurses.h>
#include <thread>
#include "counter.h"

using namespace std;


void graphics_loop(vector<IDrawable*> drawableElements, bool * exit)
{
    /*
     * This function runs on a separate thread. It iterates through
     * all the drawable objects and calls draw() on them.
     */

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

    Counter * counterOfSeconds = new Counter();

    vector<IDrawable*> elements;
    elements.push_back(myMenu);
    elements.push_back(counterOfSeconds);
    
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