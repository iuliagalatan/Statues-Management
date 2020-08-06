#pragma once

#include "Domain.h"
#include "Validator.h"
#include "BaseRepository.h"
#include "Mylist.h"
#include "CSVmylist.h"
#include <string>
#include <vector>


class CsvRepository : public BaseRepository
{
private:
	std::string file;
	Mylist* savelist;

public:

	CsvRepository() : file{ "" }, savelist{ nullptr }
	{

		file = "";
	}

	~CsvRepository()
	{
		delete savelist;

	}

	CsvRepository(std::string filegiven) : file { filegiven }, savelist{ new CSVmylist() }
	{
	}

	void setSaveList(std::string type);
	void setSaveListPath(std::string path);

	std::vector<TElems> getfromfile() const override;
	void writeTofile(std::vector<TElems> whattowrite) override;

	void addStatue(TElems statue) override;
	void updateStatue(int position, std::string PowerWordName, std::string newMaterial, int newAge, std::string newCorporealForm);
	void deleteStatue(TElems statue) override;
	int StatueIsInStatues(TElems statue) override;

	int GetSizeRepo();
	TElems GetElement(int);
	void SetFilePath(std::string path);
	void addStatueinSaveList(TElems statue);
	std::vector<Statue> GetElements() const override;
	TElems GetStatueAfterPowerWordName(std::string) override;
	bool StatueinSaveList(TElems statue) const override;
	std::vector<Statue> GetSavedElements() const override;
	bool IsMemoryRepository() const override;
	void openInApp() override;
	Type type() { return CsvRepo; }
};

