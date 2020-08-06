#pragma once
//#include "BaseRepository.h"
#include "Mylist.h"

class CSVmylist : public Mylist
{
private:
	std::string filepath;

public:
	CSVmylist() : filepath {""}
	{
	}

	CSVmylist(std::string filegiven) : filepath {filegiven}
	{
	}
	virtual std::vector<Statue> GetSavedElements() override;
	virtual bool StatueinSaveList(TElems) const;
	virtual void addStatueinSaveList(TElems) override;
	std::vector<TElems> getfromfile() const override;
	void setFilePath(std::string filepath);
	void writeTofile(std::vector<TElems> whattowrite);
	std::string StatuetoCSV(TElems statue) const;
	TElems CSVtoStatue(std::string line) const;
	void openInApp() override;
};

