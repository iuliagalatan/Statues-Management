#pragma once
#include "Mylist.h"
#include "BaseRepository.h"

class SqlMyList : public Mylist
{
private:
	std::string databaseFileName;
public:
	std::vector<TElems> getfromfile() const override;
	virtual void setFilePath(std::string filepath) override;
	virtual void writeTofile(std::vector<TElems> whattowrite) override;
	virtual void openInApp();
	virtual TElems GetStatueAfterPowerWordName(std::string PowerWordName);
	bool executeNonQuery(std::string& sql);
	int createDB();
	int createTable();


	virtual std::vector<Statue> GetSavedElements() override;
	virtual bool StatueinSaveList(TElems) const;
	virtual void addStatueinSaveList(TElems);
};


