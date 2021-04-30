#include <iostream>
#include "SnakeConfig.h"
#include "window.h"
#include "menu.h"
#include "counter.h"
#include "label.h"
#include "result.h"
#include "traveller.h"

using namespace std;

int mainMenu()
{
    Window preGameWindow;

    ObjectID menuID = preGameWindow.addElement(new Menu({"Play","Game Settings","Exit","Test Option 7","balala ub"}), 15, 10);
    preGameWindow.addElement(new Counter(), 0, 0);
    preGameWindow.addElement(new Counter(1), 1, 0);
    string copyright("(C) Lubos Vozdecky, 2021");
    preGameWindow.addElement(new Label(copyright), preGameWindow.getHeight()-1, preGameWindow.getWidth()-copyright.length()-1);

    Result * preGameWindowResults = preGameWindow.run();
    int result = preGameWindowResults->getResultOfEelement(menuID);

    return result;
}

void play()
{
    Window play;

    play.addElement(new Traveller(0.0,0.005), 10, 0);
    play.addElement(new Label("Press Q to quit..."), 30, 5);
    play.enableKillByKeyQ();

    play.run();
}

void gameSettings()
{
    Window settings;

    settings.addElement(new Label("Game settings \n A \n BKLA \n kakak"), 0, 0);
    settings.enableKillByKeyQ();

    settings.run();
}



int main()
{
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << endl;

    while(true)
    {
        std::system("clear");

        int mainMenuResult = mainMenu();

        if(mainMenuResult == 2)
        {
            break;
        }
        else if(mainMenuResult == 0)
        {
            play();
        }
        else if(mainMenuResult == 1)
        {
            gameSettings();
        }
    }
}