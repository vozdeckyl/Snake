#include "scoreLogger.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

ScoreLogger::ScoreLogger()
{
    ifstream scoreFile;

    try
    {
        ifstream scoreFile("../data/scores.bin", ifstream::binary);

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
        ofstream scoreFile("../data/scores.bin", ifstream::binary | ifstream::app);
        scoreFile.write((const char *) &time_now, sizeof(time_t));
        scoreFile.write((const char *) &score, sizeof(int));
        scoreFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }


    
    
}

void ScoreLogger::print()
{
    for(auto pair : m_scoreList)
    {
        cout << asctime(localtime(&pair.first)) << " " << pair.second << endl; 
    }
}