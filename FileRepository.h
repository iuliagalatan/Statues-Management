#pragma once
#include <iostream>
#include  "Domain.h"
#include "BaseRepository.h"
#include "Mylist.h"
#include "TextMyList.h"
#include <vector>
#include <string>
#include <algorithm>
//typedef Statue TElems;



class FileRepository : public BaseRepository
{
protected:
	std::string file;
	//std::vector<Statue> savelist;
	Mylist* savelist;

public:

	FileRepository() : file {""}, savelist {nullptr}
	{
		
		file = "";
	}

	~FileRepository()
	{
		delete savelist;

	}

	FileRepository(std::string filegiven) : file { filegiven }, savelist { new TextMyList() }
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
	Type type() { return FileRepo; } 
};

