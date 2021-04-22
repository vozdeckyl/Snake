#include <iostream>
#include "SnakeConfig.h"
#include "menu.h"
#include <ncurses.h>
#include <thread>

using namespace std;


void graphics_loop(Menu * m, bool * exit)
{
    initscr();
    start_color();
    curs_set(0);
    clear();
    while(!(*exit))
    {
        erase();
        m->show();
        refresh();
        napms(1);
    }
}

int main()
{
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << endl;

    Menu myMenu({"Play","Game Settings","Exit","Test Option 7","balala ub"});

    myMenu.setPosition(15,60);

    //nodelay(stdscr, TRUE);
    
    int input;

    bool exit{false};

    thread g_thread(graphics_loop, &myMenu, &exit);

    initscr();
    start_color();
    curs_set(0);
    keypad(stdscr,TRUE);
    while(true)
    {
        //erase();
        //myMenu.show();
        //move(10,0);
        //addstr(to_string(counter).c_str());
        //refresh();
        
        input = getch();

        if(input=='q')
        {
            exit = true;
            break;
        }
        else if(input==KEY_DOWN)
        {
            myMenu.moveSelectorDown();
        }
        else if(input==KEY_UP)
        {
            myMenu.moveSelectorUp();
        }
        
    }

    g_thread.join();

    endwin();   
}