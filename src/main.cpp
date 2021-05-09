#include <iostream>
#include "SnakeConfig.h"
#include "window.h"
#include "menu.h"
#include "counter.h"
#include "label.h"
#include "result.h"
#include "traveller.h"
#include "image.h"
#include "snake.h"
#include "scoreLogger.h"

using namespace std;

int mainMenu()
{
    Window preGameWindow;

    ObjectID menuID = preGameWindow.addElement(new Menu({"Play","Game Settings","Records","Exit"}), 15, 10);
    preGameWindow.addElement(new Counter(), 0, 0);
    preGameWindow.addElement(new Counter(1), 1, 0);
    string copyright("(C) Lubos Vozdecky, 2021");
    preGameWindow.addElement(new Label(copyright), preGameWindow.getHeight()-1, preGameWindow.getWidth()-copyright.length()-1);
    preGameWindow.addElement(new Image("../data/logo.txt"), 3, 15);

    Result preGameWindowResults = preGameWindow.run();
    int result = preGameWindowResults.getResultOfEelement(menuID);

    return result;
}

void play()
{
    Window play;

    play.addElement(new Snake(0.0,0.005), 1, 1);
    play.addElement(new Label("Press Q to quit..."), 31, 1);
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

void records()
{
    Window records;
    records.enableKillByKeyQ();

    records.addElement(new Label("Press Q to quit"), records.getHeight()-1, 1);

    ScoreLogger score;

    vector<pair<string,string>> scoresList = score.getLogList();

    int verticalPosition{4}, horizontalPosition{10};
    int offset{0};

    for(pair<string,string> scoreRecord : scoresList)
    {
        records.addElement(new Label(scoreRecord.first.append(" . . . ").append(scoreRecord.second)), verticalPosition+offset, horizontalPosition);
        offset++;
    }

    records.run();
}


int main()
{
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << endl;

    while(true)
    {
        int mainMenuResult = mainMenu();

        if(mainMenuResult == 3)
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
        else if(mainMenuResult == 2)
        {
            records();
        }
    }

}
