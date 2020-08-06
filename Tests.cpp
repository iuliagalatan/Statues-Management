#include "Tests.h"

#include <assert.h>
#include <iostream>
#include "Service.h"
#include "FileRepository.h"
#include "CSVmylist.h"
#include "HTMLmylist.h"
#include "Domain.h"



void AddStatueService_ValidInput_AddedtoList()
{
	Repository repository{};
	Service<BaseRepository> service {repository};
	std::string examplestring = "aaa";
	service.AddStatueService(examplestring, examplestring, 1, examplestring);
	assert(service.GetSize() == 1);

}

void AddStatue_ValidInput_AddedtoList()
{
	Repository repository{};
	Service<BaseRepository> service {repository};
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	
	assert(repository.GetSizeRepo() == 1);

}


void DeleteStatueService_ValidInput_RemovedfromList()
{
	Repository repository{};
	Service<BaseRepository> service = { repository };
	std::string examplestring = "aaa";
	service.AddStatueService(examplestring, examplestring, 1, examplestring);
	service.DeleteStatueService(examplestring);
	assert(service.GetSize() == 0);
}



void DeleteStatue_ValidInput_RemovedfromList()
{
	Repository repository {};
	Service<BaseRepository> service = { repository };
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	repository.deleteStatue(statue);
	assert(repository.GetSizeRepo() == 0);
}


void UpdateStatueService_ValidInput_UpdatedinList()
{
	Repository repository{};
	Service<BaseRepository> service{ repository };
	std::string examplestring = "aaa";
	service.AddStatueService(examplestring, examplestring, 1, examplestring);
	service.UpdateStatueService("aaa", "bbb", 0, "sss");

	assert(service.GetElement(0).GetMaterial() == "bbb");
}


void UpdateStatue_ValidInput_UpdatedinList()
{
	Repository repository{};
	Service<Repository> service { repository };
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);

	repository.updateStatue(0,"aaa", "bbb", 0, "sss");

	assert(repository.GetElement(0).GetMaterial()== "bbb");
}




void StaueIsInStatues_ValidInput_Found()
{
	std::string examplestring = "aaa";
	Repository repository;
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	repository.addStatue(statue);
	
	
	statue = Statue("css", examplestring, 1, examplestring);
	repository.addStatue(statue);

	assert(repository.StatueIsInStatues(statue) == 1);

}

void StaueIsInStatues_ValidInput_NotFound()
{
	std::string examplestring = "aaa";
	Repository repository = Repository();
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	Statue statue2 = Statue("alabala", examplestring, 1, examplestring);
	assert(repository.StatueIsInStatues(statue) == 0);
}


void GetStatueAfterPowerWordName_ValidInput_returnedStatue()
{
	Repository repository{};
	Service<Repository> service { repository };
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	Statue getstatue = repository.GetStatueAfterPowerWordName("aaa");
	assert(getstatue.GetAge() == 1);
}

void GetSize_ValidInput_ReturnedSize()
{
	Repository repository{};
	Service<Repository> service { repository };
	std::string examplestring = "aaa";
	service.AddStatueService(examplestring, examplestring, 1, examplestring);
	assert(service.GetSize() == 1);
}


void Writetofile_InvalidPath_ExpectedResult()
{
	std::string s = "invld.in";
	FileRepository repository{ s };
	std::vector<TElems> list;
	list = repository.getfromfile();
	std::string examplestring = "aaa";
	int size = list.size();
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	list = repository.getfromfile();
}


void GetElement_ValidInput_ReturnedElement()
{
	Repository repository{};
	Service<Repository> service { repository };
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	std::vector<TElems> listofelems = service.GetElementsVector();
	service.AddStatueService(examplestring, examplestring, 1, examplestring);
	assert(service.GetElement(0).GetAge() == 1);


}


void Getfromfile_NonexistentFileInput_createdFile()
{
	
	FileRepository repository{};
	Service<FileRepository> service { repository };
	service.SetFilePath("nonexistentFile111.in");
	std::vector<TElems> list;
	list = repository.getfromfile();
	int size = repository.GetSizeRepo();
	//for (auto statue : list)
		//std::cout << statue;
	assert(size == 0);
}

void Getfromfile_ValidInput_ReturnedVector()
{

	FileRepository repository{ "texttest.in" };
	std::vector<TElems> list;
	list = repository.getfromfile();
	//for (auto statue : list)
		//std::cout << statue;
	assert(list.size() == 2);
}

void Writetofile_ValidPath_ExpectedResult()
{
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";

	FileRepository repository {s};
	std::vector<TElems> list;
	list = repository.getfromfile();
	std::string examplestring = "aaa";
	int size = list.size();
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	list.push_back(statue);
	repository.writeTofile(list);
	list = repository.getfromfile();
	//for (auto statue : list)
		//std::cout << statue.ToString()<< '\n';
	assert(size + 1 == list.size());
}



void AddStatueFileRepository_ValidInput_AddedtoFile()
{
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";

	FileRepository repository {s};
	std::vector<TElems> list;
	list = repository.getfromfile();
	std::string examplestring = "aaac";
	int size = list.size();
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	list = repository.getfromfile();
	//for (auto statue : list)
		//std::cout << statue.ToString()<< '\n';
	assert(size + 1 == list.size());

}


void StatueisinStatues_ValidInput_ReturnedTrue()
{
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";

	FileRepository repository = FileRepository(s);
	std::vector<TElems> list;
	list = repository.getfromfile();
	int size = list.size();
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	assert(repository.StatueIsInStatues(statue) == 2);

}
void StatueisinStatues_ValidInput_ReturnedFalse()
{
	
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";

	FileRepository repository = FileRepository();
	std::vector<TElems> list;
	repository.SetFilePath(s);
	list = repository.GetElements();
	
	int size = list.size();
	std::string examplestring = "bbb";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	assert(repository.StatueIsInStatues(statue) == -1);

}


void UpdateStatueFileRepository_VlaidInput_updatedFile()
{
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";
	FileRepository repository = FileRepository(s);
	std::vector<TElems> list;
	list = repository.getfromfile();
	repository.updateStatue(0, "bb", "aaaaa", 2, "cal");

}
void DeleteStatueFileRepository_VlaidInput_updatedFile()
{
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";
	FileRepository repository = FileRepository(s);
	std::vector<TElems> list;
	list = repository.getfromfile();
	int size = list.size();
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.deleteStatue(statue);
	list = repository.getfromfile();
	assert(list.size() == size - 1);
	 statue = Statue("aaac", "aaac", 1, "aaac");
	repository.deleteStatue(statue);

}


void GetStatueAfterPowerWordNameFile_ValidInput_returnedStatue()
{
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";
	FileRepository repository = FileRepository(s);

	
	assert(repository.GetStatueAfterPowerWordName("bb").GetAge() == 2);
}



void StaueinSaveList_ValidInput_returnedTrue()
{
	Repository repository{};
	Service<Repository> service {repository};
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	repository.addStatueinSaveList(statue);
	std::vector<TElems> savedlist = repository.GetSavedElements();
	assert(repository.StatueinSaveList(statue) == true);
}

void StaueinSaveList_invalidInput_returnedFalse()
{
	Repository repository {};
	Service<Repository> service {repository};
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);

	std::vector<TElems> savedlist = repository.GetSavedElements();
	assert(repository.StatueinSaveList(statue) == false);
}

void SaveStatue_ValidInput_savedtomylist()
{
	Repository repository{};
	Service<Repository> service { repository };
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	std::vector<TElems> savedlist = repository.GetSavedElements();
	int size = savedlist.size();
	service.SaveStatue("aaa");
	 savedlist = repository.GetSavedElements();
	assert(size + 1 == savedlist.size());
}

void GetFilteredList_ValidInput_ReturnedList()
{
	Repository repository{};
	Service<Repository> service {repository};
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	std::vector<TElems> filteredlist = service.GetFilteredList("aaa", 2);
	assert(filteredlist.size() == 1);
}


void SaveStatue_InvalidInput_unmodifiedlist()
{
	Repository repository{};
	Service<Repository> service {repository};
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	repository.addStatue(statue);
	std::vector<TElems> savedlist = service.GetSavedElementsVector();
	int size = savedlist.size();
	service.SaveStatue("aaa");
	service.SaveStatue("aaa");
	assert(size == savedlist.size());

}

void ToString_ValidInput_ExpectedResult()
{
	std::string examplestring = "aaa";
	Statue statue = Statue(examplestring, examplestring, 1, examplestring);
	std::string tostring = statue.ToString();
	
	assert(tostring.size() == 42);
}

void GetElementFile_ValidInput_returnedStatue()
{
	std::string s = "C:\\Users\\User\\source\\repos\\Assigment 7\\ProjectCPP\\texttest.in";

	FileRepository repository = FileRepository(s);
	assert(repository.GetElement(0).GetPowerWordName() == "bb");
}



void CsvToSTatue_ValidInput_good()
{
	CSVmylist mylist;
	Statue s = mylist.CSVtoStatue("ana,saci,2,om");
	//std::cout << s.GetMaterial() << '\n' << s.GetCorporealForm() << '\n' << s.GetPowerWordName();
	assert(s.GetMaterial() == "saci");
	assert(s.GetAge() == 2);
	assert(s.GetPowerWordName() == "ana");
	assert(s.GetCorporealForm() == "om");
}

void HTMLToStatue_ValidInput_good()
{
	HTMLmylist mylist;
	Statue s = mylist.HTMLtoStatue("<td>ana</td><td>saci</td><td>2</td><td>om</td>");
	//std::cout << s.GetMaterial() << '\n' << s.GetCorporealForm() << '\n' << s.GetPowerWordName();
	assert(s.GetMaterial() == "saci");
	assert(s.GetAge() == 2);
	assert(s.GetPowerWordName() == "ana");
	assert(s.GetCorporealForm() == "om");
}

void Start_tests()
{
	HTMLToStatue_ValidInput_good();
	CsvToSTatue_ValidInput_good();
	AddStatueService_ValidInput_AddedtoList();
	AddStatue_ValidInput_AddedtoList();
	UpdateStatueService_ValidInput_UpdatedinList();
	UpdateStatue_ValidInput_UpdatedinList();
	DeleteStatueService_ValidInput_RemovedfromList();
	DeleteStatue_ValidInput_RemovedfromList();
	StaueIsInStatues_ValidInput_Found();
	StaueIsInStatues_ValidInput_NotFound();
	Getfromfile_ValidInput_ReturnedVector();
	Writetofile_ValidPath_ExpectedResult();
	Writetofile_InvalidPath_ExpectedResult();
	AddStatueFileRepository_ValidInput_AddedtoFile();
	StatueisinStatues_ValidInput_ReturnedTrue();
	StatueisinStatues_ValidInput_ReturnedFalse();
	DeleteStatueFileRepository_VlaidInput_updatedFile();
	GetStatueAfterPowerWordName_ValidInput_returnedStatue();
	StaueinSaveList_ValidInput_returnedTrue();
	UpdateStatueFileRepository_VlaidInput_updatedFile();
	SaveStatue_ValidInput_savedtomylist();
	GetFilteredList_ValidInput_ReturnedList();
	SaveStatue_InvalidInput_unmodifiedlist();
	GetSize_ValidInput_ReturnedSize();
	GetElement_ValidInput_ReturnedElement();
	ToString_ValidInput_ExpectedResult();
	StaueinSaveList_invalidInput_returnedFalse();
	Getfromfile_NonexistentFileInput_createdFile();
	GetStatueAfterPowerWordNameFile_ValidInput_returnedStatue();
	GetElementFile_ValidInput_returnedStatue();
}
