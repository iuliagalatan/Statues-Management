//#include "Service.h"
//#include "Repository.h"
//#include "FileRepo.h"
//#include <vector>
///*
//Adds a statue to the list of statues
//params: PowerWordName
//		Material
//		Age
//		CorporealForm
//*/
//void Service::AddStatueService(std::string PowerWordName, std::string Material, int Age, std::string CorporealForm)
//{
//	TElems Statue = TElems(PowerWordName, Material, Age, CorporealForm);
//	if( this->repository.StaueIsInStatues(Statue)==-1)
//		this->repository.addStatue(Statue);
//}
//
//
///*
//	Updates info from a statue in the list of statues
//params: PowerWordName - existent powerwordname
//		Material - new material 
//		Age - new age
//		CorporealForm - new form
//*/
//void Service::UpdateStatueService(std::string PowerWordName, std::string Material, int Age, std::string CorporealForm) 
//{
//	std::string emptystring = "";
//	int age = 0;
//	TElems Statue = TElems(PowerWordName, emptystring, age, emptystring);
//	int position = this->repository.StaueIsInStatues(Statue);
//	if (position !=-1)
//	{
//		this->repository.updateStatue(position, PowerWordName, Material, Age, CorporealForm);
//	}
//
//}
//
//
///*
//Deletes a statue after it s PowerWordName
//*/
//void Service::DeleteStatueService(std::string PowerWordName)
//{
//	std::string emptystring = "";
//	int age = 0;
//	TElems Statue = TElems(PowerWordName, emptystring, age, emptystring);
//	this->repository.deleteStatue(Statue);
//	
//}
//
//int Service::GetSize()
//{
//
//	return this->repository.GetSizeRepo();
//}
//
//TElems Service::GetElement(int position)
//{
//	return this->repository.GetElement(position);
//}
//
//
//std::vector<Statue> Service::GetElementsVector()
//{
//	return this->repository.GetElements();
//}
//
//int Service::SaveStatue(std::string powerWordName)
//{
//	Statue statue = this->repository.GetStatueAfterPowerWordName(powerWordName);
//	if (this->repository.StaueinSaveList(statue))
//		return 0;
//	
//		this->repository.addStatueinSaveList(statue);
//		return 1;
//	
//}
//
//std::vector<TElems> Service::GetSavedElementsVector()
//{
//	return this->repository.GetSavedElements();
//}
//
//std::vector<TElems> Service::GetFilteredList(std::string material, int age)
//{
//	std::vector<TElems> WholeListofStatues = this->repository.GetElements();
//	std::vector<TElems> FilteredListofStatues;
//	for (auto statue : WholeListofStatues  )
//	{
//		
//		if (statue.GetAge() < age && statue.GetMaterial() == material)
//		{
//			FilteredListofStatues.push_back(statue);
//		}
//
//	}
//	return FilteredListofStatues;
//}
//void Service::SetFilePath(std::string Filepath)
//{
//	this->repository.SetFile(Filepath);
//}