#include <gtest/gtest.h>
#include "counter.h"

TEST(counterTest, boolStates)
{
    auto c = new Counter();
    ASSERT_TRUE(c->isVisible());
    ASSERT_TRUE(c->isUpdatable());
    ASSERT_FALSE(c->isNotifiable());
}
 
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}