#pragma once
#include "Mylist.h"


class MemoryMylist : public Mylist
{
private:
	std::vector<TElems> savelist;
public:
	virtual std::vector<Statue> GetSavedElements()  override;
	virtual bool StatueinSaveList(TElems) const override;
	virtual void addStatueinSaveList(TElems) override;
	virtual std::vector<TElems> getfromfile() const override;
	virtual void setFilePath(std::string filepath) override {};
	virtual void writeTofile(std::vector<TElems> file) override;
	virtual TElems GetStatueAfterPowerWordName(std::string PowerWordName) override { return TElems(); }
	virtual void openInApp() override {} 

};

