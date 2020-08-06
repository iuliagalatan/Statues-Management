#include "UI.h"
#include <iostream>
#include <string>
#include "Validator.h"
#include "RepositoryException.h"


// command line parammeters
enum Params {
	firstparammeter,
	secondparammeter,
	thirdparammeter,
	fourthparammeter
};

void UI::start_program()
{
	char command[100];
	int returnValue;
	std::string powerwordname;
	std::string material;
	int age;
	std::string corporealform;
	
	while (true)
	{
		std::cout << "enter command..";
		ParseCommand();
	}
}

void UI::ParseCommand()
{
	char* pointerToLine;
	char lineRead[1000];

	std::cin.getline(lineRead, 1000);
	char copyline[1000];
	strcpy(copyline, lineRead);
	if (strcmp(lineRead, "exit") == 0)
	{
		std::cout << "exit application\n";
		exit(0);
	}

	int number = 0;
	int parameters = 0;
	pointerToLine = strtok(lineRead, " ");

	if (pointerToLine == nullptr)
	{
		std::cout << "wrong command\n";
		return;
	}

	if ( strcmp(pointerToLine, "add") == 0)
	{
		AddStatueUI(pointerToLine);
		return;
	}

	if ( strcmp(pointerToLine, "update") == 0)
	{	
		UpdateStatueUI(pointerToLine);
		return;
	}

	if ( strcmp(pointerToLine, "delete") == 0)
	{		
		DeleteStatueUI(pointerToLine);
		return;
	}

	if (strcmp(pointerToLine, "list") == 0)
	{		
		ListUI(pointerToLine);
		return;
	}

	if ( strcmp(pointerToLine, "mode") == 0)
	{
		ModeChangeUI(pointerToLine);
		return;
	}

	if (strcmp(pointerToLine, "next") == 0)
	{
		NextStatueUI(pointerToLine);
		return;
	}


	if ( strcmp(pointerToLine, "save") == 0)
	{
		SaveStatueUI(pointerToLine);
		return;
	}

	if ( strcmp(pointerToLine, "mylist") == 0)
	{
		this->ListMyList();
		return;
	}
	if (strcmp(pointerToLine, "fileLocation") == 0)
	{
		this->FileLocation(copyline);
		return;
	}
	if (strcmp(pointerToLine, "mylistLocation") == 0)
	{
		this->MylistLocation(copyline);
		return;
	}
	// the command is ill formed
	std::cout << "wrong command\n";
}

void UI::MylistLocation(char* pointerToline)
{
	std::string filePath = std::string(pointerToline);
	size_t position = filePath.find(' ');
	filePath = filePath.substr(position + 1);

	std::string path;
	
	if (filePath.find(".csv") != std::string::npos)
	{
		csv_type = true;
		this->service.setSaveList("csv");
	}
	if (filePath.find(".html") != std::string::npos)
	{
		html_type = true;
		this->service.setSaveList("html");
	}
	
	if (filePath.find(".sqlite") != std::string::npos)
	{
		//sql_type = true;
		this->service.setSaveList("sql");
	}
	this->service.setSaveListPath(filePath);
	
}

void UI::FileLocation(char* pointerToline)
{
	
	std::string filePath = std::string(pointerToline);
	size_t position = filePath.find(' ');
	filePath = filePath.substr(position + 1);

	std::string path;
	/*for (char ch : filePath)
	{
		path += ch;
		if (ch == '\\')
			path += '\\';
	}*/
	//filePath = path;
	this->service.SetFilePath(filePath);
}
void UI::NextStatueUI(char* pointerToLine)
{
	if (modeB)
	{
		this->Next(position);
		position += 1;
	}
}

void UI::ModeChangeUI(char* pointerToLine)
{
	pointerToLine = strtok(NULL, " ");
	if (pointerToLine != NULL)
		if (strcmp(pointerToLine, "A") == 0)
			modeA = true, modeB = false; // mode A -  magic spells on
		else
			if (strcmp(pointerToLine, "B") == 0)
				modeB = true,
				modeA = false; // mode B spells will work
}


void UI::SaveStatueUI(char* pointerToLine)
{ 
	if (modeB)
	{
		pointerToLine = strtok(NULL, " ");
		std::string powerWordName = pointerToLine;
		this->SaveStatue(powerWordName);
		std::cout << "Statue saved\n";
	}
}

void UI::ListUI(char* pointerToLine)
{
	pointerToLine = strtok(NULL, ", ");
	if (pointerToLine == NULL)
		if (modeA == 1)
			this->ListAll();

	if (pointerToLine != NULL)
	{
		std::string material = pointerToLine;
		pointerToLine = strtok(NULL, ", ");
		int age = atoi(pointerToLine);

		this->filterAfterMaterialAndAge(material, age);
	}
}

void UI::AddStatueUI(char* pointerToLine)
{
	for (int i = 0; i < 4; ++i) // add needs to have 4 params
	{
		pointerToLine = strtok(NULL, ", ");
		if (pointerToLine != NULL)
		{
			GetParameters(i, pointerToLine);
		}
		else
		{
			std::cout << "not enough parammeters\n";
			return;
		}
	}

	if (modeA == 1)
	{
		try
		{
			this->service.AddStatueService(powerwordname, material, age, corporealform);
		}
		catch (FileException& exception)
		{
			std::cout << exception.what() << '\n';
		}
		catch (DuplicateStatueException& exception)
		{
			std::cout << exception.what() << '\n';
		}
		catch (StatueException & statueException)
		{
			std::cout << statueException.what() << '\n';
		}
		catch(...)
		{
			std::cout << "Another exception raised";	
		}
	}
}

void UI::UpdateStatueUI(char* pointerToLine)
{
	for (int i = 0; i < 4; ++i) //update needs to have 4 params
	{
		pointerToLine = strtok(NULL, ", ");
		if (pointerToLine != NULL)
		{
			GetParameters(i, pointerToLine);
		}
		else
		{
			std::cout << "not enough parammeters\n";
			return;				
		}
	}

	if (modeA == 1)
		this->service.UpdateStatueService(powerwordname, material, age, corporealform);
}

void UI::GetParameters(int i, char* pointerToLine)
{
	if (i == firstparammeter) // first param
		powerwordname = pointerToLine;
	if (i == secondparammeter) // second param
		material = pointerToLine;
	if (i == thirdparammeter) // third param
		age = atoi(pointerToLine);
	if (i == fourthparammeter) // forthparam
		corporealform = pointerToLine;
}


void UI::DeleteStatueUI(char* pointerToLine)
{
	for (int i = 0; i < 1; ++i) // delete needs to have 1 param
	{
		pointerToLine = strtok(NULL, " ");
		if (pointerToLine != NULL)
		{
			if (i == 0) // only one param
				powerwordname = pointerToLine;
		}
		else
		{
			std::cout << "not enough parammeters\n";
			return;
		}
	}
	
	if (modeA == 1) // if magicspell is 1, we can proceed.
		this->service.DeleteStatueService(powerwordname);	
}

void UI::ListAll()
{
	this->List(this->service.GetElementsVector());
}

void UI::List(std::vector<TElems> toprint)
{
	for (auto statue : toprint)
	{
		
		std::cout << statue.ToString() << '\n';
	}
}


void UI::Next(int position)
{
	if (position >= this->service.GetSize())
		std::cout << "NO";
	else
	{
		Statue nextstatue = this->service.GetElement(position);
		std::cout << nextstatue.ToString() << '\n';
	}
}

void UI::SaveStatue(std::string PowerWordName)
{
	this->service.SaveStatue(PowerWordName);
}

void UI::ListMyList()
{
//	std::vector<TElems> toprint = this->service.GetSavedElementsVector();
	//this->List(toprint);

	this->service.openExternApp();
}

void UI::filterAfterMaterialAndAge(std::string material, int age)
{
	std::vector<TElems> toprint = this->service.GetFilteredList(material, age);
	if (toprint.size() == 0)
		toprint = this->service.GetElementsVector();
	this->List(toprint);
}