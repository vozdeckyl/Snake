#ifndef SCORELOGGER_H
#define SCORELOGGER_H

#include <utility>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class ScoreLogger {
    public:
        ScoreLogger();
        ~ScoreLogger();

        void logScore(int score);
        void print();
    
    private:
        vector<pair<time_t,int>> m_scoreList;
};

#endif