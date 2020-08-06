#pragma once
#include <iostream>
#include <vector>
#include  "Domain.h"
#include <algorithm>
typedef Statue TElems;


class BaseRepository
{
public:
	virtual ~BaseRepository() {}
	virtual void addStatue(TElems statue) = 0;
	virtual void updateStatue(int position, std::string PowerWordName, std::string newMaterial, 
							  int newAge, std::string newCorporealForm) = 0;
	virtual void addStatueinSaveList(TElems) = 0;
	virtual void deleteStatue(TElems statue)= 0;
	virtual int StatueIsInStatues(TElems statue) = 0;
	virtual bool StatueinSaveList(TElems statue) const = 0;
	virtual TElems GetStatueAfterPowerWordName(std::string powerWordName) = 0;
	virtual int GetSizeRepo() = 0;
	virtual TElems GetElement(int) = 0;
	virtual std::vector<Statue> GetElements() const = 0;

	virtual std::vector<Statue> GetSavedElements() { return std::vector<TElems>(); };
	virtual void setSaveList(std::string type) {};
	virtual void setSaveListPath(std::string path) {};
	virtual void SetFilePath(std::string path) {};
	virtual void openInApp() {};

	virtual std::vector<TElems> getfromfile() const { return std::vector<TElems>(); };
	virtual void writeTofile(std::vector<TElems> whattowrite) {};	
};

