/*! \mainpage %Snake
 *
 * This is a documentation to %Snake - a simple terminal based Linux game.
 * 
 * 
 * Dependencies
 * - \subpage ncurses-base
 * 
 */

#include <iostream>
#include <unistd.h>
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
#include "settingsMenu.h"
#include "NCursesEngine.h"
#include "fileManager.h"


#ifdef DEBUG
  #define BUILD "Debug"
#else
  #define BUILD "Release"
#endif

using namespace std;

void maximize_active_window();

int mainMenu()
{
    Window preGameWindow(new NCursesEngine());

    ObjectID menuID = preGameWindow.addElement(new Menu({"Play","Game Settings","Records","Exit"}), 15, 10);
    preGameWindow.addElement(new Counter(), 0, 0);
    preGameWindow.addElement(new Counter(1), 1, 0);
    string copyright("(C) Lubos Vozdecky, 2021");
    preGameWindow.addElement(new Label(copyright), preGameWindow.getHeight()-1, preGameWindow.getWidth()-copyright.length()-1);
    preGameWindow.addElement(new Image(FileManager::getFilePath("logo")), 3, 15);

    Result preGameWindowResults = preGameWindow.run();
    int result = preGameWindowResults.getResultOfEelement(menuID);
    
    return result;
}

void play()
{
    Window play(new NCursesEngine());

    play.addElement(new Snake(0.0,0.005), 1, 1);
    play.addElement(new Label("Press Q to quit..."), play.getHeight()-1, 1);
    play.enableKillByKeyQ();

    play.run();
}

void gameSettings()
{
    Window settings(new NCursesEngine());

    SettingsMenu * settingsMenu = new SettingsMenu();
    settingsMenu->addSetting(Setting("Map size",{"small","medium","large"}));
    settingsMenu->addSetting(Setting("Snake speed",{"slow","medium","fast"}));
    settingsMenu->addSetting(Setting("Penetrable walls",{"Yes","No"}));
    settingsMenu->loadFromFile(FileManager::getFilePath("settings"));
    
    settings.addElement(settingsMenu, 5, 20);
    settings.enableKillByKeyQ();

    settings.run();
}

void records()
{
    Window records(new NCursesEngine());
    records.enableKillByKeyQ();

    records.addElement(new Label(" TOP 10 SCORES ",Color::black,Color::white),2,10);
    records.addElement(new Label("Press Q to quit"), records.getHeight()-1, 1);

    ScoreLogger score;

    vector<pair<string,string>> scoresList = score.getLogList();

    int verticalPosition{4}, horizontalPosition{10};
    int offset{0};

    for(pair<string,string> scoreRecord : scoresList)
    {
        if(offset >= 10)
        {
            break;
        }

        records.addElement(new Label(scoreRecord.first), verticalPosition+offset, horizontalPosition);
        records.addElement(new Label(scoreRecord.second, Color::magenta), verticalPosition+offset, horizontalPosition+30);

        offset++;
    }

    records.run();
}


int main()
{
    maximize_active_window();    
    cout << "Snake v" << Snake_VERSION_MAJOR << "." << Snake_VERSION_MINOR << " " << BUILD << endl;
    sleep(1);
    
    FileManager::addFile("logo",std::vector<std::string>({"../data/logo.txt","/usr/local/share/shellsnake/logo.txt"}));
    FileManager::addFile("settings",std::vector<std::string>({"../data/settings.bin","/var/shellsnake/settings.bin"}));
    FileManager::addFile("scores",std::vector<std::string>({"../data/scores.bin","/var/shellsnake/scores.bin"}));

    
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
