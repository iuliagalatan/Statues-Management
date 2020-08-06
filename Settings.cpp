#include "Settings.h"
#include "BaseRepository.h"
#include "SqlRepository.h"
#include "MemoryRepository.h"
#include "FileRepository.h"
#include "CsvRepository.h"
#include "HtmlRepository.h"
#include <fstream>
#include <string>

Settings::Settings(std::string filePath) : filePath{ filePath }
{
	ReadSettings();
}

void Settings::ReadSettings()
{
	std::ifstream fin(filePath);
	if (!fin)
	{
		return;
	}
	std::string repository;
	std::string repositoryType;
	std::getline(fin, repository, ':');
	std::getline(fin, repositoryType);
	settings[repository] = repositoryType;
}

BaseRepository* Settings::SetConfiguration()
{
	if ( settings["repository"] == "in-memory")
	{
		return new MemoryRepository();
	}
	
	if (settings["repository"] == "fileRepository")
	{

		return  new FileRepository();
	}

	if (settings["repository"] == "sqlRepository")
	{
		
		return  new SqlRepository();
	}
	
	if (settings["repository"] == "csvRepository")
	{
		return  new CsvRepository();
	}

	if (settings["repository"] == "htmlRepository")
	{
		return  new HtmlRepository();
	}
}
