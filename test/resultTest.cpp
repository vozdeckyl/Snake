#include <gtest/gtest.h>

#include "IDrawable.h"
#include "label.h"
#include "menu.h"
#include "objectid.h"
#include "result.h"
#include <map>
#include <memory>

TEST(resultTest, menuResults)
{
    Menu* menu = new Menu({"A", "B", "C"});

    std::map<ObjectID, std::unique_ptr<IDrawable>> results;

    results.emplace(std::make_pair(1, std::unique_ptr<IDrawable>(static_cast<IDrawable*>(menu))));

    Result result(results);

    ASSERT_TRUE(result.getResultOfEelement(1) == 0);

    menu->moveSelectorDown();

    Result result2(results);

    ASSERT_TRUE(result2.getResultOfEelement(1) == 1);
}

TEST(resultTest, labelResults)
{
    std::map<ObjectID, std::unique_ptr<IDrawable>> results;
    results.emplace(std::make_pair(1, std::unique_ptr<IDrawable>(new Label("a"))));
    Result result(results);
    ASSERT_TRUE(result.getResultOfEelement(1) == -1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
