#pragma once
#include "MemoryRepository.h"
#include "HTMLmylist.h"
#include "CSVmylist.h"
#include "SqlMyList.h"
#include "TextMyList.h"
#include "Domain.h"
#include <iostream>
#include <vector>


void MemoryRepository::addStatue(TElems statue)
{
	if (StatueIsInStatues(statue)!= -1)
		return;
	statues.push_back(statue);
}

void MemoryRepository::updateStatue(int position, std::string PowerWordName, std::string newMaterial, int newAge, std::string newCorporealForm)
{
	TElems ourstatue = statues[position];
	TElems updated = TElems(PowerWordName, newMaterial, newAge, newCorporealForm);
	statues[position]= updated;
}

void MemoryRepository::deleteStatue( TElems statue)
{
	int deleteposition = this->StatueIsInStatues(statue);
	if( deleteposition != -1)
		statues.erase(statues.begin() + deleteposition);
}

int MemoryRepository::StatueIsInStatues(TElems statue)
{
	int position = 0;
	for (auto actualstatue:statues)
	{
		
		if (actualstatue.GetPowerWordName() == statue.GetPowerWordName())
			return position;
		position++;
	}
	return -1;
}

int MemoryRepository::GetSizeRepo()
{
	return this->statues.size();
}

TElems MemoryRepository::GetElement(int position)
{
	if (this->GetSizeRepo() > position)
	return this->statues[position];
	return TElems();

}

std::vector<TElems> MemoryRepository::GetElements() const
{
	return this->statues;
}

bool MemoryRepository::IsMemoryRepository() const
{
	return true;
}

TElems MemoryRepository::GetStatueAfterPowerWordName(std::string PowerWordName)
{
	Statue searchedstatue;
	for (auto statue:statues)
	{
		
		if (PowerWordName == statue.GetPowerWordName())
			searchedstatue =  statue;
	}
	return searchedstatue;
}

bool MemoryRepository::StatueinSaveList(TElems statue) const
{
	return my_list->StatueinSaveList(statue);
}

void  MemoryRepository::setSaveListPath(std::string path)
{
	if (path == "") return;
	this->my_list->setFilePath(path);
}

void MemoryRepository::addStatueinSaveList(TElems statue)
{

	my_list->addStatueinSaveList(statue);
}

void MemoryRepository::setSaveList(std::string type)
{
	delete my_list;
	if (type == "txt")
		my_list = new TextMyList;
	if (type == "memory")
		my_list = new MemoryMylist;
	if (type == "csv")
		my_list = new CSVmylist;
	if (type == "sql")
		my_list = new SqlMyList;
	if (type == "html")
		my_list = new HTMLmylist;
}

std::vector<Statue> MemoryRepository::GetSavedElements() const
{
	return my_list->GetSavedElements();
}

void MemoryRepository::openInApp()
{
	my_list->openInApp();
}