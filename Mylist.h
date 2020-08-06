#pragma once
#include <vector>
#include "Domain.h"



class Mylist
{
public:
	virtual std::vector<Statue> GetSavedElements()  = 0;
	virtual bool StatueinSaveList(TElems) const = 0;
	virtual void addStatueinSaveList(TElems) = 0;
	virtual void setFilePath(std::string filepath) = 0;
	virtual void writeTofile(std::vector<TElems> whattowrite) = 0;
	virtual std::vector<TElems> getfromfile() const = 0;
	virtual TElems GetStatueAfterPowerWordName(std::string PowerWordName) { return TElems(); }
	virtual void openInApp() = 0;
	virtual ~Mylist() {}
};

