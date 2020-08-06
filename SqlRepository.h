#pragma once
#include "BaseRepository.h"
#include "Mylist.h"

class SqlRepository : public BaseRepository
{
	std::string databaseFileName;
	Mylist* savelist = nullptr;

public:

	SqlRepository()
	{

		databaseFileName = "";
	}

	~SqlRepository()
	{
		delete savelist;

	}

	SqlRepository(std::string filegiven);

	void setSaveList(std::string type);
	void setSaveListPath(std::string path);

	std::vector<TElems> getfromfile() const override;
	void writeTofile(std::vector<TElems> whattowrite) override;

	void addStatue(TElems statue) override;
	void executeNonQuery(std::string& sql);
	void updateStatue(int position, std::string PowerWordName, std::string newMaterial, int newAge, std::string newCorporealForm);
	void deleteStatue(TElems statue) override;
	int StatueIsInStatues(TElems statue) override;
	std::vector<Statue> GetElements() const override;
	TElems GetStatueAfterPowerWordName(std::string) override;
	void SetFilePath(std::string path) override;


	
	int GetSizeRepo();
	TElems GetElement(int);


	bool StatueinSaveList(TElems statue) const override;
	void addStatueinSaveList(TElems statue);
	std::vector<Statue> GetSavedElements() const override;
	void openInApp() override;
	bool IsMemoryRepository() const override;
	int createDB(const char* s);
	int createTable(const char* s);
	Type type() { return SqlRepo; }
};

