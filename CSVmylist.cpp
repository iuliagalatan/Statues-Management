#include "CSVmylist.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

std::vector<Statue> CSVmylist::GetSavedElements()
{
	std::vector<TElems> savedElements = getfromfile();
	return savedElements;
}

bool CSVmylist::StatueinSaveList(TElems statue) const
{
	std::vector<TElems> savedElements = getfromfile();

	for (auto& _statue : savedElements)
		if (_statue == statue)
			return true;
	return false;
}

void CSVmylist::addStatueinSaveList(TElems statue)
{
	std::vector<TElems> savelist = getfromfile();
	savelist.push_back(statue);
	writeTofile(savelist);
}

std::vector<TElems> CSVmylist::getfromfile() const
{
	std::ifstream ifstream(filepath, std::ios_base::in | std::ios_base::out);
	std::vector<TElems> datafromfile;

	if (!ifstream.is_open())
	{
		std::ofstream ofstream(filepath, std::ios_base::app);
		return datafromfile;
	}

	TElems input;
	std::string line;

	while (std::getline(ifstream, line))
	{	
		Statue statue = CSVtoStatue(line);
		datafromfile.push_back(statue);
	}

	ifstream.close();
	return datafromfile;
}

void CSVmylist::setFilePath(std::string filepath)
{
	this->filepath = filepath;
}

void CSVmylist::writeTofile(std::vector<TElems> whattowrite)
{
	std::fstream FileToWriteto;

	FileToWriteto.open(filepath, std::fstream::in | std::fstream::out | std::fstream::trunc);

	for (auto statue : whattowrite)
	{
			
		FileToWriteto << StatuetoCSV(statue);
		FileToWriteto << '\n';
	}

	FileToWriteto.close();
	std::cout << "\n";
}

std::string CSVmylist::StatuetoCSV(TElems statue) const
{

	std::string towrite = statue.GetPowerWordName() + "," + statue.GetMaterial() + "," + std::to_string(statue.GetAge()) + "," + statue.GetCorporealForm();
	return towrite;
}

TElems CSVmylist::CSVtoStatue(std::string line) const
{
	int coma = line.find(',');
	std::string PowerWordName = line.substr(0, coma);
	line.erase(0, coma+1);
	int coma2 = line.find( ',');
	std::string Material = line.substr(0, coma2);
	line.erase(0, coma2+1);
	int coma3 = line.find( ',');
	std::string Age = line.substr(0, coma3 );

	std::string CorporealForm = line.substr(coma3+1);
	Statue statue;
	statue.setPowerWordName(PowerWordName);
	statue.setCorporealForm(CorporealForm);
	statue.setAge(stoi(Age));
	statue.setMaterial(Material);

	return statue;
}

void CSVmylist::openInApp()
{
	ShellExecuteA(NULL, NULL, "excel.exe", filepath.c_str(), NULL, SW_SHOWMAXIMIZED);
}