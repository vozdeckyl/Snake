#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "setting.h"

using namespace std;

TEST(settingTest, names)
{
    Setting setting1("setting1",{"A","B","C","D"});
    Setting setting2("setting2",{"A"});
    Setting setting3("setting3",{});

    ASSERT_STREQ(setting1.getName().c_str(),"setting1");
    ASSERT_STREQ(setting2.getName().c_str(),"setting2");
    ASSERT_STREQ(setting3.getName().c_str(),"setting3");
}

TEST(settingTest, nextOption)
{
    Setting s("name",{"A","B","C"});
    ASSERT_STREQ(s.getOption().c_str(),"A");
    s.nextOption();
    ASSERT_STREQ(s.getOption().c_str(),"B");
    s.nextOption();
    ASSERT_STREQ(s.getOption().c_str(),"C");

    s.previousOption();
    s.previousOption();

    ASSERT_STREQ(s.getOption().c_str(),"A");
}

TEST(settingTest, selectOption)
{
    Setting s("name",{"A","B","C"});
    s.selectOption(2);
    ASSERT_STREQ(s.getOption().c_str(),"C");
    s.selectOption(1);
    ASSERT_STREQ(s.getOption().c_str(),"B");
    s.selectOption(0);
    ASSERT_STREQ(s.getOption().c_str(),"A");
}

TEST(settingsTest, getOptionIndex)
{
    Setting s("name",{"A","B","C"});
    ASSERT_TRUE(s.getOptionIndex() == 0);
    s.nextOption();
    ASSERT_TRUE(s.getOptionIndex() == 1);
    s.nextOption();
    ASSERT_TRUE(s.getOptionIndex() == 2);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
