#ifndef SCORELOGGER_H
#define SCORELOGGER_H

#include <ctime>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*!
    @brief Game score logger reponsible for logging and saving scores

    This class loads the file with the saved scores (in data/scores.bin) on its initialization and saves the score
   whenever a game is played.
*/
class ScoreLogger
{
  public:
    ScoreLogger();
    ~ScoreLogger();

    /*!
        @brief Logs the game score
        @param score game score
    */
    void logScore(int score);

    /*!
        @brief Returns the logged scores

        The scores are returned as a list of string pairs. First element is the date and second is the score. The list
       is sorted by scores.
    */
    vector<pair<string, string>> getLogList();

  private:
    vector<pair<time_t, int>> m_scoreList;
};

#endif