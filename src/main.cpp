#include <iostream>
#include <thread>
#include <ncurses.h>
#include "SnakeConfig.h"
#include "menu.h"
#include "counter.h"
#include "label.h"

using namespace std;


void graphics_loop(vector<IDrawable*> drawableElements, bool * exit)
{
    /*
     * This function runs on a separate thread. It iterates through
     * all the drawable objects and calls draw() on them.
     */

    noecho();
    while(!(*exit))
    {
        erase();
        
        for(IDrawable * element : drawableElements)
        {
            if(element->isVisible())
            {
                element->draw();
            }
        }

        refresh();
        napms(1);
    }
}

void update_loop(vector<IDrawable*> updatableElements, bool * exit)
{
    while(!(*exit))
    {
        for(IDrawable * element : updatableElements)
        {
            if(element->isUpdatable())
            {
                element->update();
            }
        }
        napms(1);
    }
}


int main()
{
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << endl;

    Menu * myMenu = new Menu({"Play","Game Settings","Exit","Test Option 7","balala ub"});
    myMenu->setPosition(15,10);

    Counter * secondCounter = new Counter();
    Counter * miliCounter = new Counter();
    miliCounter->setInterval(1);
    miliCounter->setPosition(1,0);

    Label * versionNumber = new Label("This is snake version 0.1");
    versionNumber->setPosition(5,10);

    vector<IDrawable*> elements;
    elements.push_back(myMenu);
    elements.push_back(secondCounter);
    elements.push_back(miliCounter);
    elements.push_back(versionNumber);
    
    int input;
    bool exit{false};

    thread g_thread(graphics_loop, elements, &exit);
    thread u_thread(update_loop, elements, &exit);

    

    initscr();
    start_color();
    curs_set(0);
    keypad(stdscr,TRUE);
    cbreak();
    noecho();

    while(true)
    {   
        input = getch();

        if(input=='q')
        {
            exit = true;
            break;
        }
        
        for(IDrawable * element : elements)
        {
            if(element->isNotifiable())
            {
                element->notify(input);
            }
        }
    }

    g_thread.join();
    u_thread.join();

    delete myMenu;
    delete secondCounter;
    delete miliCounter;
    delete versionNumber;

    endwin();
}