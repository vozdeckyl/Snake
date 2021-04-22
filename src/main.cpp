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

    noecho();
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

void update_loop(vector<IUpdatable*> updatableElements, bool * exit)
{
    while(!(*exit))
    {
        for(IUpdatable * element : updatableElements)
        {
            element->update();
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

    vector<IDrawable*> drawables;
    drawables.push_back(myMenu);
    drawables.push_back(secondCounter);
    drawables.push_back(miliCounter);

    vector<IUpdatable*> updatables;
    updatables.push_back(secondCounter);
    updatables.push_back(miliCounter);
    
    int input;
    bool exit{false};

    thread g_thread(graphics_loop, drawables, &exit);
    thread u_thread(update_loop, updatables, &exit);

    

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
    u_thread.join();

    delete myMenu;
    delete secondCounter;
    delete miliCounter;

    endwin();   
}