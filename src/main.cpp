#include <iostream>
#include <thread>
#include <ncurses.h>
#include "SnakeConfig.h"
#include "window.h"
#include "menu.h"
#include "counter.h"
#include "label.h"

using namespace std;


int main()
{
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << endl;

    Menu * myMenu = new Menu({"Play","Game Settings","Exit","Test Option 7","balala ub"});
    Counter * secondCounter = new Counter();
    Counter * miliCounter = new Counter(1);
    Label * versionNumber = new Label("This is snake version 0.1");

    Window preGameWindow;

    preGameWindow.addElement(myMenu,15,10);
    preGameWindow.addElement(secondCounter,0,0);
    preGameWindow.addElement(miliCounter,1,0);
    preGameWindow.addElement(versionNumber,5,10);
    
    preGameWindow.run();
}