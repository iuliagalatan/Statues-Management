#pragma once
#include "MemoryMylist.h"



bool MemoryMylist::StatueinSaveList(TElems statue) const
{
	bool ok = false;
	for (auto savedstatue : savelist)
		if (savedstatue.GetPowerWordName() == statue.GetPowerWordName())
			ok = true;

	return ok;
}


void MemoryMylist::addStatueinSaveList(TElems statue)
{
	savelist.push_back(statue);
}

std::vector<TElems> MemoryMylist::getfromfile() const
{
	return savelist;
}

void MemoryMylist::writeTofile(std::vector<TElems> file)
{
}

std::vector<Statue> MemoryMylist::GetSavedElements() 
{
	return savelist;
}
