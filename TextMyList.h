#pragma once
#include "Mylist.h"
#include <string>

class TextMyList :	public Mylist
{
private:
	std::string filepath;
public:
	
	virtual bool StatueinSaveList(TElems) const;
	virtual void addStatueinSaveList(TElems statue) override;

	std::vector<TElems> getfromfile() const override;
	virtual std::vector<Statue> GetSavedElements() override;
	void setFilePath(std::string filepath);
	void writeTofile(std::vector<TElems> whattowrite);
	std::string StatueToText(TElems statue) const;
	TElems TextToStatue(std::string line) const;
	void openInApp() override;
};

