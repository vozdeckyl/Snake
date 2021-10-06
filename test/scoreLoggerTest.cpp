#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <string>
#include "scoreLogger.h"
#include "fileManager.h"

using namespace std;

TEST(scoreLoggerTest, scores)
{
    system("touch scores.dat && rm scores.dat");
    system("touch scores.dat");
    
    FileManager::addFile("scores","scores.dat");

    ScoreLogger score;

     score.logScore(0);
     score.logScore(1);
     score.logScore(2);
     score.logScore(3);
     score.logScore(4);
     score.logScore(5);
     score.logScore(6);
     
    vector<pair<string,string>> scoreList = score.getLogList();

    ASSERT_STREQ(scoreList[0].second.c_str(),"6");
    ASSERT_STREQ(scoreList[1].second.c_str(),"5");
    ASSERT_STREQ(scoreList[2].second.c_str(),"4");
    ASSERT_STREQ(scoreList[3].second.c_str(),"3");
    ASSERT_STREQ(scoreList[4].second.c_str(),"2");
    ASSERT_STREQ(scoreList[5].second.c_str(),"1");
    ASSERT_STREQ(scoreList[6].second.c_str(),"0");
}

TEST(scoreLoggerTest, logFile)
{
    system("touch scores.dat && rm scores.dat");
    system("touch scores.dat");

    ScoreLogger score;

     score.logScore(0);
     score.logScore(1);
     score.logScore(2);
     score.logScore(3);
     score.logScore(4);
     score.logScore(5);
     score.logScore(6);

     ScoreLogger anotherLogger;

     vector<pair<string,string>> scoreList = anotherLogger.getLogList();

    ASSERT_STREQ(scoreList[0].second.c_str(),"6");
    ASSERT_STREQ(scoreList[1].second.c_str(),"5");
    ASSERT_STREQ(scoreList[2].second.c_str(),"4");
    ASSERT_STREQ(scoreList[3].second.c_str(),"3");
    ASSERT_STREQ(scoreList[4].second.c_str(),"2");
    ASSERT_STREQ(scoreList[5].second.c_str(),"1");
    ASSERT_STREQ(scoreList[6].second.c_str(),"0");
     
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
