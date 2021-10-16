#include "scoreLogger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "fileManager.h"

using namespace std;

ScoreLogger::ScoreLogger()
{
    ifstream scoreFile;

    try
    {
        ifstream scoreFile(FileManager::getFilePath("scores"), ifstream::binary);

        while(true)
        {
            time_t time;
            int score;
            scoreFile.read((char *) &time, sizeof(time_t));
            scoreFile.read((char *) &score, sizeof(int));
            if(!scoreFile.eof())
            {
                m_scoreList.push_back(make_pair(time,score));
            }
            else
            {
                break;
            }
        }
        scoreFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

ScoreLogger::~ScoreLogger()
{
}

void ScoreLogger::logScore(int score)
{
    time_t time_now{0};
    time(&time_now);

    m_scoreList.push_back(make_pair(time_now,score));

    try
    {
        ofstream scoreFile(FileManager::getFilePath("scores"), ifstream::binary | ifstream::app);
        scoreFile.write((const char *) &time_now, sizeof(time_t));
        scoreFile.write((const char *) &score, sizeof(int));
        scoreFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

vector<pair<string,string>> ScoreLogger::getLogList()
{
    vector<pair<string,string>> logList;

    vector<pair<time_t,int>> scoreListSorted(m_scoreList);

    sort(scoreListSorted.begin(),scoreListSorted.end(), [](pair<time_t,int> a, pair<time_t,int> b){return a.second > b.second;});

    for(const auto & pair : scoreListSorted)
    {
        char buffer[20];
        string date;
        string score{to_string(pair.second)};

        strftime(buffer,80,"%d %b %Y %T", localtime(&pair.first));

        date.assign(buffer);
        logList.push_back(make_pair(date,score));
    }

    return logList;
}
