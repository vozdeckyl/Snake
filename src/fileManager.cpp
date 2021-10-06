#include <fileManager.h>
#include <filesystem>

namespace fs = std::filesystem;

std::map<std::string,std::string> FileManager::m_paths;

void FileManager::addFile(std::string nickname, std::vector<std::string> filePaths)
{
    if(m_paths.find(nickname) != m_paths.end())
    {
	throw FileManagerException("Declaring a file nickname that is already used");
    }
    
    for(const std::string & filePath : filePaths)
    {
	if(fs::exists(filePath))
	{
	    m_paths[nickname] = filePath;
	    return;
	}
    }

    throw FileManagerException("None of the file paths exist");
}

void FileManager::addFile(std::string nickname, std::string filePath)
{
    addFile(nickname, std::vector<std::string>({filePath}));
}

std::string FileManager::getFilePath(std::string nickname)
{
    if(m_paths.find(nickname) != m_paths.end())
    {
	return FileManager::m_paths[nickname];
    }
    else
    {
	throw FileManagerException("Unknown file nickname");
    }
}
