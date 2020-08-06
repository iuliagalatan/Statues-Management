#pragma once
#include <vector>
#include <string>
#include "Domain.h"
#include "Mylist.h"

class HTMLmylist : public Mylist
{

private:
	std::string filepath;

public:
	HTMLmylist() : filepath {""}
	{ 
	}

	HTMLmylist(std::string filegiven) : filepath {filegiven}
	{ 
	}

	virtual std::vector<Statue> GetSavedElements() override;
	virtual bool StatueinSaveList(TElems) const override;
	virtual void addStatueinSaveList(TElems) override;
	std::vector<TElems> getfromfile() const override;
	void setFilePath(std::string filepath);
	void writeTofile(std::vector<TElems> whattowrite);
	std::string StatuetoHTML(TElems statue) const;
	TElems HTMLtoStatue(std::string line) const;
	void openInApp() override;
};
