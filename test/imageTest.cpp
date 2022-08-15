#include <gtest/gtest.h>

#include "image.h"
#include "mockScreen.h"
#include <fstream>

using namespace std;

TEST(imageTest, boolStates)
{
    auto image = new Image("");
    ASSERT_TRUE(image->isVisible());
    ASSERT_FALSE(image->isUpdatable());
    ASSERT_FALSE(image->isNotifiable());

    delete image;
}

TEST(imageTest, drawing)
{
    // create a test image
    ofstream testImg;

    try
    {
        testImg.open("test/testimg.txt");
        testImg << "All work and no play makes Jack a dull boy";
        testImg.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    mockScreen engine(100, 100);
    auto image = new Image("test/testimg.txt");
    image->setPosition(0, 0);

    image->draw(engine);
    ASSERT_TRUE(engine.testScreen('A', 0, 0));
    ASSERT_TRUE(engine.testScreen('l', 0, 1));
    ASSERT_TRUE(engine.testScreen('l', 0, 2));
    ASSERT_TRUE(engine.testScreen(' ', 0, 3));
    ASSERT_TRUE(engine.testScreen('w', 0, 4));
    ASSERT_TRUE(engine.testScreen('o', 0, 5));
    ASSERT_TRUE(engine.testScreen('r', 0, 6));

    ASSERT_TRUE(engine.testScreen('y', 0, 41));
    ASSERT_TRUE(engine.testScreen(' ', 0, 42));
    
    delete image;
}

TEST(imageTest, multiline)
{
    // create a test image
    ofstream testImg;

    try
    {
        testImg.open("test/testimg.txt");
        testImg << "A\n";
        testImg << "B\n";
        testImg << "C\n";
        testImg << "D\n";
        testImg << "E\n";
        testImg << "F\n";
        testImg.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    mockScreen engine(100, 100);
    auto image = new Image("test/testimg.txt");
    image->setPosition(0, 0);

    image->draw(engine);
    ASSERT_TRUE(engine.testScreen('A', 0, 0));
    ASSERT_TRUE(engine.testScreen('B', 1, 0));
    ASSERT_TRUE(engine.testScreen('C', 2, 0));
    ASSERT_TRUE(engine.testScreen('D', 3, 0));
    ASSERT_TRUE(engine.testScreen('E', 4, 0));
    ASSERT_TRUE(engine.testScreen('F', 5, 0));

    ASSERT_TRUE(engine.testScreen(' ', 6, 0));
    
    delete image;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
