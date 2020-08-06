#pragma once
#include <iostream>
#include "BaseRepository.h"
#include "Domain.h"
#include <vector>
#include "Mylist.h"
#include "MemoryMylist.h"

//typedef Statue TElems;



class MemoryRepository: public BaseRepository
{
private:
	
	Mylist* my_list;
	std::vector<Statue> statues;

public:

	MemoryRepository() : my_list { new MemoryMylist{} }
	{
	}

	~MemoryRepository()
	{
		delete my_list;
	}

	void addStatue(TElems statue) override;
	void updateStatue(int position, std::string PowerWordName, std::string newMaterial, 
			int newAge, std::string newCorporealForm) override;
	void deleteStatue(TElems statue) override;
	int StatueIsInStatues(TElems statue) override;
	int GetSizeRepo() override;
	TElems GetStatueAfterPowerWordName(std::string) override;
	TElems GetElement(int ) override;
	std::vector<Statue> GetElements() const override;
	bool IsMemoryRepository() const override;
	std::vector<Statue> GetSavedElements() const;
	bool StatueinSaveList(TElems) const;
	void addStatueinSaveList(TElems);
	void setSaveList(std::string file) override;
	void openInApp() override;
	void  setSaveListPath(std::string path) override;
	Type type() { return InMemoryRepo; }
};

