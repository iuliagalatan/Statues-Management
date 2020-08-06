#include  "FileRepository.h"
#include "RepositoryException.h"
#include "TextMyList.h"
#include "MemoryMylist.h"
#include "HTMLmylist.h"
#include "CSVmylist.h"
#include "SqlMyList.h"
#include <fstream>
#include "Validator.h"
#include "Domain.h"

std::vector<TElems> FileRepository::getfromfile() const
{
	std::ifstream ifstream(file, std::ios_base::in | std::ios_base::out);
	std::vector<TElems> datafromfile;
	
	if (!ifstream)
		throw FileException("File couldn't be opened");
	if (!ifstream.is_open())
	{
		std::ofstream ofstream(file, std::ios_base::app);
		return datafromfile;
	}

	TElems input;

	while (ifstream >> input)
	{
		datafromfile.push_back(input);
	}

	ifstream.close();
	return datafromfile;

}

void FileRepository::writeTofile(std::vector<TElems> whattowrite)
{
	std::ofstream ofstream(file);	// will append data
	

	int position = 1;
	for (TElems statue : whattowrite)
	{
		if (position < int(whattowrite.size()))
			ofstream << statue << '\n';
		else
			ofstream << statue;
		position++;
	}

	ofstream.close();
}


void FileRepository::addStatue(TElems statue)
{
	Validator validator;
	validator.validate_statue(statue);//this raises an exception if statue is not ok
	std::vector<TElems> listofstatues = this->getfromfile();
	listofstatues.push_back(statue);
	this->writeTofile(listofstatues);
}

void FileRepository::updateStatue(int position, std::string PowerWordName, std::string newMaterial, int newAge, std::string newCorporealForm)
{
	std::vector<TElems> listofstatues = this->getfromfile();

	TElems ourstatue = listofstatues[position];
	TElems updated = TElems(PowerWordName, newMaterial, newAge, newCorporealForm);
	listofstatues[position] = updated;
	this->writeTofile(listofstatues);

}

void FileRepository::deleteStatue(TElems statue)
{
	std::vector<TElems> newlistofstatues;
	std::vector<TElems> listofstatues = this->getfromfile();
	for (auto readstatue : listofstatues)
	{
		if (readstatue.GetPowerWordName() != statue.GetPowerWordName())
			newlistofstatues.push_back(readstatue);
	}
	this->writeTofile(newlistofstatues);
}



int FileRepository::StatueIsInStatues(Statue statue)
{

	std::vector<TElems> listofstatues = this->getfromfile();
	int position = -1;
	for (auto liststatue : listofstatues)
	{
		position++;
		if (liststatue.GetPowerWordName() == statue.GetPowerWordName())
			return position;
	}
	return -1;
}


TElems FileRepository::GetStatueAfterPowerWordName(std::string PowerWordName)
{
	std::vector<TElems> listofstatues = this->getfromfile();
	int position = -1;
	TElems Savestatue;
	for (auto liststatue : listofstatues)
	{
		if (liststatue.GetPowerWordName() == PowerWordName)
			Savestatue= liststatue;
	}
	return Savestatue;
}

void FileRepository::SetFilePath(std::string path)
{
	this->file = path;
}

std::vector<Statue> FileRepository::GetElements() const
{
	return this->getfromfile();
}


TElems FileRepository::GetElement(int positionofLineinFile)
{
	std::vector<TElems> listofstatues = this->getfromfile();
	int position = 0;
	TElems Savestatue;
	for (auto liststatue : listofstatues)
	{

		if (position == positionofLineinFile)
			Savestatue= liststatue;
		position++;
	}
	return Savestatue;
}

int  FileRepository::GetSizeRepo()
{
	return this->getfromfile().size();
}

bool FileRepository::StatueinSaveList(TElems statue) const
{
	std::vector<TElems> listofstatues = this->savelist->getfromfile();
	int position = -1;
	for (auto liststatue : listofstatues)
	{
		position++;
		if (liststatue.GetPowerWordName() == statue.GetPowerWordName())
			return true;
	}
	return false;
}

void FileRepository::addStatueinSaveList(TElems statue)
{
	std::vector<TElems> listofstatues = this->savelist->getfromfile();
	savelist->addStatueinSaveList(statue);
	listofstatues.push_back(statue);
	this->savelist->writeTofile(listofstatues);
}

std::vector<Statue> FileRepository::GetSavedElements() const
{
	std::vector<Statue> savedstatues = this->savelist->getfromfile();
	return savedstatues;
}

bool FileRepository::IsMemoryRepository() const
{
	return false;
}

void FileRepository::setSaveList(std::string type)
{
	delete savelist;
	if (type == "txt")
		savelist = new TextMyList;
	if (type == "memory")
		savelist = new MemoryMylist;
	if (type == "csv")
		savelist = new CSVmylist;
	if (type == "sql")
		savelist = new SqlMyList;
	if (type == "html")
		savelist = new HTMLmylist;


}

void  FileRepository::setSaveListPath(std::string path)
{
	this->savelist->setFilePath(path);
}

void FileRepository::openInApp()
{
	this->savelist->openInApp();
}
