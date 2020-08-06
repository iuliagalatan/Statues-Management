#pragma once
#include "BaseRepository.h"
#include "MemoryRepository.h"
#include "FileRepository.h"
#include <vector>
#include "RepositoryException.h"
#include "Validator.h"
#include "Action.h"

template <class BaseRepository>
class Service
{
private:
	BaseRepository& repository;
	typename BaseRepository::Type repoType;
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;
public:
	Service(BaseRepository& repository) : 
		repository { repository },
		repoType { repository.type() }
	{
	}

	typename BaseRepository::Type RepositoryType() { return repoType; }

	void AddStatueService(std::string PowerWordName, std::string Material, int Age, std::string CorporealForm);
	void UpdateStatueService(std::string PowerWordName, std::string Material, int Age, std::string CorporealForm);
	void DeleteStatueService(std::string PowerWordName);
	int GetSize();
	TElems GetElement(int);
	std::vector<TElems> GetElementsVector();
	
	std::vector<TElems> GetFilteredList(std::string, int);
	void SetFilePath(std::string Filepath);

	int SaveStatue(std::string);
	std::vector<TElems> GetSavedElementsVector();
	TElems GetStatueByPowerWordName(std::string powerwordname);

	void setSaveList(std::string filetype);
	void setSaveListPath(std::string path);
	void openExternApp();

	bool Undo();
	bool Redo();
};

/*
Adds a statue to the list of statues
params: PowerWordName
		Material
		Age
		CorporealForm
*/
template <class BaseRepository>
void Service<BaseRepository>::AddStatueService(std::string PowerWordName, std::string Material, int Age, std::string CorporealForm)
{

	TElems Statue = TElems(PowerWordName, Material, Age, CorporealForm);
	if (this->repository.StatueIsInStatues(Statue) == -1)
	{
		try {
			this->repository.addStatue(Statue);
			std::unique_ptr<Action> addAction = std::make_unique<ActionAdd>(&repository, Statue);
			//std::unique_ptr<Action> addAction2 = std::make_unique<ActionAdd>(&repository, statue);
			undoStack.push_back(std::move(addAction));
		}
		catch (StatueException& statueException)
		{
			throw statueException;
		}
	}
	else
		 throw DuplicateStatueException();
}


/*
	Updates info from a statue in the list of statues
params: PowerWordName - existent powerwordname
		Material - new material
		Age - new age
		CorporealForm - new form
*/
template <class BaseRepository>
void Service<BaseRepository>::UpdateStatueService(std::string PowerWordName, std::string Material, int Age, std::string CorporealForm)
{
	std::string emptystring = "";
	int age = 0;
	TElems Statue = TElems(PowerWordName, emptystring, age, emptystring);
	int position = this->repository.StatueIsInStatues(Statue);
	if (position != -1)
	{

		TElems initialStatue = repository.GetStatueAfterPowerWordName(PowerWordName);
		
		this->repository.updateStatue(position, PowerWordName, Material, Age, CorporealForm);
		TElems statue = repository.GetStatueAfterPowerWordName(PowerWordName);
		std::unique_ptr<Action> addAction = std::make_unique<ActionUpdate>(&repository, initialStatue, position);
		//std::unique_ptr<Action> addAction2 = std::make_unique<ActionRemove>(&repository, statue);
		this->undoStack.push_back(std::move(addAction));
	}
}


/*
Deletes a statue after it s PowerWordName
*/
template <class BaseRepository>
void Service<BaseRepository>::DeleteStatueService(std::string PowerWordName)
{
	std::string emptystring = "";
	int age = 0;
	TElems Statue = TElems(PowerWordName, emptystring, age, emptystring);
	this->repository.deleteStatue(Statue);
	std::unique_ptr<Action> addAction = std::make_unique<ActionRemove>(&repository, Statue);
	//std::unique_ptr<Action> addAction2 = std::make_unique<ActionRemove>(&repository, statue);
	this->undoStack.push_back(std::move(addAction));
}

template <class BaseRepository>
int Service<BaseRepository>::GetSize()
{
	return this->repository.GetSizeRepo();
}

template <class BaseRepository>
TElems Service<BaseRepository>::GetElement(int position)
{
	return this->repository.GetElement(position);
}

template <class BaseRepository>
std::vector<Statue> Service<BaseRepository>::GetElementsVector()
{
	return this->repository.GetElements();
}

template <class BaseRepository>
int Service<BaseRepository>::SaveStatue(std::string powerWordName)
{
	Statue statue = this->repository.GetStatueAfterPowerWordName(powerWordName);
	if (this->repository.StatueinSaveList(statue))
		return 0;

	this->repository.addStatueinSaveList(statue);
	return 1;

}

template <class BaseRepository>
std::vector<TElems> Service<BaseRepository>::GetSavedElementsVector()
{
	return this->repository.GetSavedElements();
}

template <class BaseRepository>
std::vector<TElems> Service<BaseRepository>::GetFilteredList(std::string material, int age)
{
	std::vector<TElems> WholeListofStatues = this->repository.GetElements();
	std::vector<TElems> FilteredListofStatues;
	for (auto statue : WholeListofStatues)
	{

		if (statue.GetAge() < age && statue.GetMaterial() == material)
		{
			FilteredListofStatues.push_back(statue);
		}

	}
	return FilteredListofStatues;
}


template <class BaseRepository>
void Service<BaseRepository>::SetFilePath(std::string Filepath)
{

	this->repository.SetFilePath(Filepath);
	
}

template <class BaseRepository>
void Service<BaseRepository>::setSaveList(std::string filetype)
{
	this->repository.setSaveList(filetype);
}

template <class BaseRepository>
void Service<BaseRepository>::setSaveListPath(std::string path)
{
	this->repository.setSaveListPath(path);
}

template <class BaseRepository>
void Service<BaseRepository>::openExternApp()
{
	this->repository.openInApp();
}

template <class BaseRepository>
TElems Service<BaseRepository>::GetStatueByPowerWordName(std::string powerwordname)
{
	return this->repository.GetStatueAfterPowerWordName(powerwordname);
}




template <class BaseRepository>
bool Service<BaseRepository>::Undo()
{
	if (undoStack.size() == 0)
		return false;
	std::unique_ptr<Action> action = std::move(this->undoStack.back());
	this->undoStack.pop_back();
	
	action->executeUndo();
	this->redoStack.push_back(std::move(action));
	return true;


}

template <class BaseRepository>
bool Service<BaseRepository>::Redo()
{
	if (redoStack.size() == 0)
		return false;
	std::unique_ptr<Action> action = std::move(this->redoStack.back());
	this->redoStack.pop_back();
	action->executeRedo();
	return true;

}

