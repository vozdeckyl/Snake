#include <iostream>
#include "SnakeConfig.h"
#include "window.h"
#include "menu.h"
#include "counter.h"
#include "label.h"
#include "result.h"
#include "traveller.h"

using namespace std;


int main()
{
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << endl;
    int outcome;
    {
        //Menu * myMenu = new Menu({"Play","Game Settings","Exit","Test Option 7","balala ub"});
        Counter * secondCounter = new Counter();
        Counter * miliCounter = new Counter(1);
        Label * helpText = new Label("Press Q to quit");
        Traveller * snake = new Traveller(0.0,0.005);

        Window preGameWindow;

        //ObjectID menuID = preGameWindow.addElement(myMenu,15,10);
        //preGameWindow.addElement(secondCounter,0,0);
        //preGameWindow.addElement(miliCounter,1,0);
        //preGameWindow.addElement(helpText,30,0);
        preGameWindow.addElement(snake,10,0);
        
        Result * preGameWindowResults = preGameWindow.run();
        //outcome = preGameWindowResults->getResultOfEelement(menuID); 
    }
    cout << outcome << endl;
}