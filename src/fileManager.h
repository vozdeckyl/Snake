#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <map>

/*!
@brief Static class for managing files and their paths

Each file is given a nickname and a list of possible paths.
If the file is not found in the first path the next one is tried.
IF the file is not found in any of the paths, error is thrown. 
*/
class FileManager {

public:
    /*!
      @brief Add a file and the list of possible paths
      @param nickname The name by which the file is referred to as in the code
      @param filePaths The possible paths where the file can be found
     */
    static void addFile(std::string nickname, std::vector<std::string> filePaths);

    /*!
      @brief Add a file and its path
      @param nickname The name by which the file is referred to as in the code
      @param filePath The path to the file
     */
    static void addFile(std::string nickname, std::string filePath);

    /*!
      @brief Retrieve the path to the file
      @param nickname File nickname given to the file using the addFile method
     */
    static std::string getFilePath(std::string nickname);
    
private:
    /*!
      @brief Private constructor to prevent instances
     */
    FileManager();
    
    std::map<std::string,std::string> paths;
};

#endif
