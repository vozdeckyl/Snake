#include <gtest/gtest.h>
#include <iostream>
#include "fileManager.h"

TEST(fileManagerTest, singlePath)
{
    system("mkdir mockFolder");
    system("touch mockFolder/testfile");

    FileManager::addFile("myfile", "mockFolder/testfile");

    ASSERT_STREQ(FileManager::getFilePath("myfile").c_str(), "mockFolder/testfile");

    try
    {
	FileManager::getFilePath("nonexisting");	
	FAIL();
    }
    catch(FileManagerException e)
    {
	// pass
	std::cout << e.what() << std::endl;
    }


    system("rm -r mockFolder");
}

TEST(fileManagerTest, multiplePaths)
{
    system("mkdir mockFolder");
    system("touch mockFolder/testfile");
    system("touch mockFolder/anothertestfile");

    FileManager::addFile("myFile",std::vector<std::string>({"mockFolder/testfile","mockFolder/anothertestfile"}));
    FileManager::addFile("myFile2",std::vector<std::string>({"none/testfile","mockFolder/anothertestfile"}));
    FileManager::addFile("myFile3",std::vector<std::string>({"mockFolder/testfile","none/anothertestfile"}));
    FileManager::addFile("myFile4",std::vector<std::string>({"mockFolder/testfile"}));
    

    ASSERT_STREQ(FileManager::getFilePath("myFile").c_str(),"mockFolder/testfile");
    ASSERT_STREQ(FileManager::getFilePath("myFile2").c_str(),"mockFolder/anothertestfile");
    ASSERT_STREQ(FileManager::getFilePath("myFile3").c_str(),"mockFolder/testfile");
    ASSERT_STREQ(FileManager::getFilePath("myFile4").c_str(),"mockFolder/testfile");

    try
    {
	FileManager::addFile("myFile5",std::vector<std::string>({"none/testfile","none/anothertestfile"}));
	FAIL();
    }
    catch(FileManagerException e)
    {
	// pass
	std::cout << e.what() << std::endl;
    }
    
    system("rm -r mockFolder");
}

TEST(fileManagerTest, robustness)
{
    system("mkdir mockFolder");
    system("touch mockFolder/testfile");
    system("touch mockFolder/anothertestfile");
    
    try
    {
        FileManager::addFile("asd",std::vector<std::string>({"mockFolder/testfile","mockFolder/anothertestfile"}));
	FileManager::addFile("asd",std::vector<std::string>({"mockFolder/testfile","mockFolder/anothertestfile"}));
	FAIL();
    }
    catch(FileManagerException e)
    {
	// pass
	std::cout << e.what() << std::endl;
    }

    try
    {
	FileManager::addFile("asd","mockFolder/anothertestfile");
	FileManager::addFile("asd","mockFolder/anothertestfile");
	FAIL();
    }
    catch(FileManagerException e)
    {
	// pass
	std::cout << e.what() << std::endl;
    }

    try
    {
	FileManager::getFilePath("nonexistent");
	FAIL();
    }
    catch(FileManagerException e)
    {
	// pass
	std::cout << e.what() << std::endl;
    }
    
    system("rm -r mockFolder");
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
