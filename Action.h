#pragma once
#include "BaseRepository.h"
#include "Domain.h"
class Action
{
private:
public:
	virtual bool executeUndo() {
		return false;
	}
	virtual bool executeRedo() {
		return false;
	};
};

class ActionAdd : public Action
{
private:

	BaseRepository* Repository;
	Statue addedStatue;
public:
	ActionAdd(BaseRepository* repository, Statue statue) : Repository{ repository }, addedStatue{ statue }{}
	bool executeUndo() override;
	bool executeRedo() override;
};

class ActionRemove : public Action
{
private:

	BaseRepository* Repository;
	Statue removedStatue;
public:
	ActionRemove(BaseRepository* repository, Statue statue) : Repository{ repository }, removedStatue{ statue }{}
	bool executeUndo() override;
	bool executeRedo() override;

};

class ActionUpdate : public Action
{
private:

	BaseRepository* Repository;
	
	Statue updatedStatue;
	int position;
public:
	ActionUpdate(BaseRepository* repository, Statue statue, int position) : Repository{ repository }, updatedStatue{ statue }, position{ position }{}
	bool executeUndo() override;
	bool executeRedo() override;

};
