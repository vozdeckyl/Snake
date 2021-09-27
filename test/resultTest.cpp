#include <gtest/gtest.h>

#include "result.h"
#include "objectid.h"
#include "IDrawable.h"
#include "menu.h"
#include "label.h"
#include <map>

TEST(resultTest, menuResults)
{
    Menu * menu = new Menu({"A","B","C"});
    std::map<ObjectID,IDrawable *> results;

    results.emplace(std::make_pair(1,menu));

    Result result(results);

    ASSERT_TRUE(result.getResultOfEelement(1) == 0);

    menu->moveSelectorDown();

    Result result2(results);

    ASSERT_TRUE(result2.getResultOfEelement(1) == 1);
    
    delete menu;
    menu = nullptr;
}

TEST(resultTest, labelResults)
{
    Label * label = new Label("a");
    std::map<ObjectID,IDrawable *> results;                                                                                                          
    results.emplace(std::make_pair(1,label));
    Result result(results);
    ASSERT_TRUE(result.getResultOfEelement(1) == -1);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
