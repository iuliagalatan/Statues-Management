#pragma once
#include <string>
#include <map>
#include "BaseRepository.h"

class Settings
{
private:
	std::string filePath;
	std::map<std::string, std::string> settings;
	
public:
	Settings(std::string filePath);
	void ReadSettings();
	BaseRepository* SetConfiguration();
};

