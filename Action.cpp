#include "Action.h"
#include "Action.h"
bool ActionAdd::executeUndo()
{
	Repository->deleteStatue(addedStatue);
	return true;
}


bool ActionRemove::executeRedo()
{
	Repository->deleteStatue(removedStatue);
	return true;
}


bool ActionAdd::executeRedo()
{
	Repository->addStatue(addedStatue);
	return true;
}

bool ActionRemove::executeUndo()
{
	Repository->addStatue(removedStatue);
	return true;
}

bool ActionUpdate::executeRedo()
{
	this->Repository->updateStatue(position, updatedStatue.GetPowerWordName(), updatedStatue.GetMaterial(), updatedStatue.GetAge(), updatedStatue.GetCorporealForm());
		
	return true;
}

bool ActionUpdate::executeUndo()
{
	this->Repository->updateStatue(position, updatedStatue.GetPowerWordName(), updatedStatue.GetMaterial(), updatedStatue.GetAge(), updatedStatue.GetCorporealForm());
	return true;
}


