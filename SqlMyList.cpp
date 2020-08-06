#include "SqlMyList.h"
#include <sstream>
#include "sqlite3.h"
#include "Validator.h"
#include <Windows.h>
#include <shellapi.h>

static std::string rows = "";

///*
//	typedef int (*sqlite3_callback)(
//   void*,     Data provided in the 4th argument of sqlite3_exec() */
//  int,      /* The number of columns in row */
//  char**,   /* An array of strings representing fields in the row */
//  char**    /* An array of strings representing column names */
//);
//*/
static int callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		std::string field(argv[i]);
		rows += field;
		if (i < argc - 1)      // the row nust not end with ',' (nee
			rows += ",";       // ',' as separator between fields is needed in >> operator for Statue
	}

	rows += '\n';              // each row end with newline. Needed for ">>" operator in Domain (Statue class)
	return 0;
}

std::vector<TElems> SqlMyList::getfromfile() const
{
	std::vector<TElems> datafromfile;

	// SELECT * FROM Statues
	sqlite3* DB;
	char* messaggeError;
	// open database
	int exit_code = sqlite3_open(databaseFileName.c_str(), &DB);

	if (exit_code)
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(DB) << std::endl;
		sqlite3_close(DB);
		return std::vector<TElems>();
	}

	std::string query = "SELECT * FROM Statues;";
	// execute query
	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
	sqlite3_close(DB);

	TElems statue;
	std::stringstream stream(rows);
	rows = "";
	while (stream >> statue)
	{
		datafromfile.push_back(statue);
	}

	return datafromfile;
}

TElems SqlMyList::GetStatueAfterPowerWordName(std::string PowerWordName)
{
	sqlite3* DB;

	// open database
	int exit_code = sqlite3_open(databaseFileName.c_str(), &DB);
	if (exit_code)
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(DB);
		sqlite3_close(DB);
		return TElems();
	}

	std::string query = "SELECT * FROM Statues WHERE powerWordName = '" + PowerWordName + "';";
	// execute query
	exit_code = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
	if (exit_code)
	{
		std::cerr << "Statue : " << PowerWordName << " was not found!\n";
		return TElems();
		sqlite3_close(DB);
	}

	sqlite3_close(DB);

	TElems statue;
	std::stringstream stream(rows);
	rows = "";
	stream >> statue;

	return statue;
}

void SqlMyList::setFilePath(std::string filePath)
{
	databaseFileName = filePath;
//	createDB();
	createTable();
}

void SqlMyList::writeTofile(std::vector<TElems> statues)
{
	std::string sql("DELETE FROM Statues;");
	executeNonQuery(sql); // delete all statues from table Statues
	bool ok = false;
	for (auto& statue : statues)
	{
		std::string powerWordName = statue.GetPowerWordName();
		std::string material = statue.GetMaterial();
		int age = statue.GetAge();
		std::string corporealForm = statue.GetCorporealForm();
		std::string sql("INSERT INTO Statues (powerWordName, material, age, corporealForm) VALUES ('" + powerWordName + "', '" +
			material + "', '" +
			std::to_string(age) + "', '" +
			corporealForm + "');");

		if (!executeNonQuery(sql)) // insert a new Statue
			ok = false;
	}
	if (ok)
		std::cout << "Query OK!" << std::endl;
}

bool SqlMyList::executeNonQuery(std::string& sql)
{
	sqlite3* DB;
	int exit_code = sqlite3_open(databaseFileName.c_str(), &DB);
	if (exit_code)
	{
		std::cerr << "Can't open database: \n";
		sqlite3_close(DB);
		return false;
	}

	char* messaggeError;
	exit_code = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit_code != SQLITE_OK)
	{
		std::cerr << "Error executing " + sql << " : " << messaggeError;
		sqlite3_free(messaggeError);
		return false;
	}

	return true;
}

int SqlMyList::createDB()
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

int SqlMyList::createTable()
{
	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS Statues ("
		"powerWordName  TEXT, "
		"material       TEXT     NOT NULL, "
		"age            INT     NOT NULL, "
		"corporealForm  TEXT NOT NULL);";

	int exit = 0;
	exit = sqlite3_open(databaseFileName.c_str(), &DB);
	char* messaggeError;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
		std::cout << "Table created Successfully" << std::endl;
	sqlite3_close(DB);
	return (0);
}

std::vector<Statue> SqlMyList::GetSavedElements()
{
	std::vector<TElems> savedelements = getfromfile();
	return savedelements;
}

bool SqlMyList::StatueinSaveList(TElems statue) const
{
	std::vector<TElems> savedElements = getfromfile();

	for (auto& _statue : savedElements)
		if (_statue == statue)
			return true;
	return false;
}

void SqlMyList::addStatueinSaveList(TElems statue)
{
	std::vector<TElems> savelist = getfromfile();
	savelist.push_back(statue);
	writeTofile(savelist);
}

void SqlMyList::openInApp()
{
	ShellExecuteA(NULL, NULL, "C:\\Program Files\\RazorSQL\\razorsql.exe", databaseFileName.c_str(), NULL, SW_SHOWMAXIMIZED);
	system("PAUSE");
}