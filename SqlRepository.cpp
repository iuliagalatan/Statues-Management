#pragma once
#include "SqlRepository.h"
#include "TextMyList.h"
#include "MemoryMylist.h"
#include "HTMLmylist.h"
#include "CSVmylist.h"
#include  "FileRepository.h"
#include "RepositoryException.h"
#include "SqlMyList.h"
#include <sstream>
#include "sqlite3.h"
#include "Validator.h"

static std::string rows = "";

static int callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		std::string field(argv[i]);
		rows += field;
		if (i < argc - 1)      // the row nust not end with ',' (nee
				rows += ",";   // ',' as separator between fields is needed in >> operator for Statue
	}
	
	rows += '\n';                   // each row end with newline. Needed for ">>" operator in Domain (Statue class)
	return 0;
}

int callbackCount(void* count, int argc, char** argv, char** azColName)
{
	int* c = (int*)count;
	*c = atoi(argv[0]);
	return 0;
}

SqlRepository::SqlRepository(std::string filePath)
{
	databaseFileName = filePath;
//	createDB(filePath.c_str());
	createTable(filePath.c_str());
}

std::vector<TElems> SqlRepository::getfromfile() const
{	
	std::vector<TElems> datafromfile;

	// SELECT * FROM Statues
	sqlite3* DataBase;
	char* messaggeError;
	// open database
	int exit_code = sqlite3_open(databaseFileName.c_str(), &DataBase);
	
	if (exit_code)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DataBase));
		sqlite3_close(DataBase);
		return std::vector<TElems>();
	}

	std::string query = "SELECT * FROM Statues;";
	// execute query
	sqlite3_exec(DataBase, query.c_str(), callback, NULL, NULL);
	sqlite3_close(DataBase);

	TElems statue;
	std::stringstream stream(rows);
	rows = "";
	while (stream >> statue)
	{
		datafromfile.push_back(statue);
	}

	return datafromfile;
}

void SqlRepository::writeTofile(std::vector<TElems> statues)
{
}

void SqlRepository::addStatue(TElems statue)
{
	Validator validator;
	//validator.validate_statue(statue);//this raises an exception if statue is not ok
	
	std::string powerWordName = statue.GetPowerWordName();
	std::string material = statue.GetMaterial();
	int age = statue.GetAge();
	std::string corporealForm = statue.GetCorporealForm();
	std::string sql("INSERT INTO Statues (powerWordName, material, age, corporealForm) VALUES ('" + powerWordName + "', '" +
		material + "', '" +
		std::to_string(age) + "', '" +
		corporealForm + "');");

	executeNonQuery(sql); // insert a new Statue
}

void SqlRepository::executeNonQuery(std::string& sql)
{
	sqlite3* DataBase;
	int exit_code = sqlite3_open(databaseFileName.c_str(), &DataBase);
	if (exit_code)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DataBase));
		sqlite3_close(DataBase);
	}

	char* messaggeError;
	exit_code = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messaggeError);
	if (exit_code != SQLITE_OK)
	{
		std::cerr << "Error executing " + sql << " : " << messaggeError;
		sqlite3_free(messaggeError);
	}
	else
		std::cout << "Query OK!" << std::endl;
}

void SqlRepository::updateStatue(int position, std::string PowerWordName, std::string newMaterial, int newAge, std::string newCorporealForm)
{
	std::string sql("UPDATE Statues SET material = '" + newMaterial + "', " +
		"age = " + std::to_string(newAge)+ "," +
		"corporealform = '" + newCorporealForm + "' WHERE powerWordName = '" + PowerWordName + "';");
	
	executeNonQuery(sql); // Update statue with given PowerWordName
}

void SqlRepository::deleteStatue(TElems statue)
{
	std::string powerWordName = statue.GetPowerWordName();
	std::string sql("DELETE FROM Statues WHERE powerWordName = '" + powerWordName + "';");

	executeNonQuery(sql); // delete 
}


int SqlRepository::StatueIsInStatues(TElems statue)
{
	std::vector<TElems> listofstatues = this->getfromfile();  // SELECT * FROM Statues
	int position = -1;
	for (auto liststatue : listofstatues)
	{
		position++;
		if (liststatue.GetPowerWordName() == statue.GetPowerWordName())
			return position;
	}
	return -1;
}


TElems SqlRepository::GetStatueAfterPowerWordName(std::string PowerWordName)
{
	sqlite3* DataBase;

	// open database
	int exit_code = sqlite3_open(databaseFileName.c_str(), &DataBase);
	if (exit_code)
	{
		std::cerr <<  "Can't open database: " << sqlite3_errmsg(DataBase);
		sqlite3_close(DataBase);
		return TElems();
	}

	std::string query = "SELECT * FROM Statues WHERE powerWordName = '" + PowerWordName + "';";
	// execute query
	exit_code = sqlite3_exec(DataBase, query.c_str(), callback, NULL, NULL);
	if (exit_code)
	{
		std::cerr << "Statue : " << PowerWordName << " was not found!\n";
		return TElems();
		sqlite3_close(DataBase);
	}

	sqlite3_close(DataBase);

	TElems statue;
	std::stringstream stream(rows);
	rows = "";
	stream >> statue;

	return statue;
}

void SqlRepository::SetFilePath(std::string filePath)
{
	databaseFileName = filePath;
//	createDB(filePath.c_str());
	createTable(filePath.c_str());
}

std::vector<Statue> SqlRepository::GetElements() const
{
	return this->getfromfile();
}


TElems SqlRepository::GetElement(int positionofLineinFile)
{
	std::vector<TElems> listofstatues = this->getfromfile();
	int position = 0;
	TElems Savestatue;
	for (auto liststatue : listofstatues)
	{

		if (position == positionofLineinFile)
			Savestatue = liststatue;
		position++;
	}
	return Savestatue;
}

int  SqlRepository::GetSizeRepo()
{
	return this->getfromfile().size();
}


bool SqlRepository::StatueinSaveList(TElems statue) const
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

void SqlRepository::addStatueinSaveList(TElems statue)
{
	std::vector<TElems> listofstatues = this->savelist->getfromfile();
	listofstatues.push_back(statue);
	savelist->addStatueinSaveList(statue);
	this->savelist->writeTofile(listofstatues);
}

std::vector<Statue> SqlRepository::GetSavedElements() const
{
	std::vector<Statue> savedstatues = this->savelist->getfromfile();
	return savedstatues;
}

void SqlRepository::setSaveList(std::string type)
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


void  SqlRepository::setSaveListPath(std::string path)
{
	if (path == "") return;
	this->savelist->setFilePath(path);
}

void SqlRepository::openInApp()
{
	this->savelist->openInApp();
}

bool SqlRepository::IsMemoryRepository() const
{
	return false;
}

int SqlRepository::createDB(const char* s)
{
	sqlite3* DB = nullptr;
	int exit = sqlite3_open(databaseFileName.c_str(), &DB);

	if (exit)
	{
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return (-1);
	}

	std::cout << "Opened Database Successfully!" << std::endl;
	sqlite3_close(DB);

	return (0);

}

int SqlRepository::createTable(const char* s)
{
	sqlite3* DataBase;
	std::string sql = "CREATE TABLE IF NOT EXISTS Statues ("
		"powerWordName  TEXT, "
		"material       TEXT     NOT NULL, "
		"age            INT     NOT NULL, "
		"corporealForm  TEXT NOT NULL);";

	int exit = 0;
	exit = sqlite3_open(databaseFileName.c_str(), &DataBase);
	char* messaggeError;
	exit = sqlite3_exec(DataBase, sql.c_str(), NULL, 0, &messaggeError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
		std::cout << "Table created Successfully" << std::endl;
	sqlite3_close(DataBase);
	return (0);
}

