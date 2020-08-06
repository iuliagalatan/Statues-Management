
#include "HtmlRepository.h"
#include "HTMLmylist.h"
#include "TextMyList.h"
#include "MemoryMylist.h"
#include "CSVmylist.h"
#include "SqlMyList.h"
#include <Windows.h>
#include <shellapi.h>
#include <fstream>


std::vector<TElems> HtmlRepository::getfromfile() const
{
	std::ifstream ifstream(file, std::ios_base::in | std::ios_base::out);
	std::vector<TElems> datafromfile;

	if (!ifstream.is_open())
	{
		std::ofstream ofstream(file, std::ios_base::app);
		return datafromfile;
	}

	TElems input;
	std::string line;
	int counter = 0;

	while (std::getline(ifstream, line))
	{

		if (line == "</table>")
			break;
		if (line.find("<td>") == std::string::npos)
		{

			continue;
		}
		else
		{
			counter++;
			if (counter == 1)
				continue;
		}
		Statue statue = HTMLtoStatue(line);
		datafromfile.push_back(statue);

	}

	ifstream.close();
	return datafromfile;

}

void HtmlRepository::writeTofile(std::vector<TElems> statuestowrite)
{
	std::ofstream ofstream(file);

	ofstream << "<!DOCTYPE html>" << "\n";
	ofstream << "<html>" << "\n";
	ofstream << "<head>" << "\n";
	ofstream << "<title>Coats list</title>" << "\n";
	ofstream << "</head>" << "\n";
	ofstream << "<body>" << "\n";
	ofstream << "<table border=\"1\">" << "\n";
	ofstream << "<tr>" << "\n";
	ofstream << "<td>PowerWordName</td>" << "<td>Material</td>" << "<td>Age</td>" << "<td>CorpoRealForm</td>" << "\n";
	ofstream << "</tr>" << "\n";

	for (auto statue : statuestowrite)
	{
		ofstream << StatuetoHTML(statue);
	}

	ofstream << "</table>\n</body>\n</html>\n";
	ofstream.close();

}
std::string HtmlRepository::StatuetoHTML(TElems statue) const {

	std::string htmlscript = "<tr>";
	htmlscript += "\n<td>" + statue.GetPowerWordName() + "</td>" +
		"<td>" + statue.GetMaterial() + "</td>" +
		"<td>" + std::to_string(statue.GetAge()) + "</td>" +
		"<td>" + statue.GetCorporealForm() + "</td>" + "\n" + "</tr>\n";
	return htmlscript;

}
TElems HtmlRepository::HTMLtoStatue(std::string line) const {
	int firsttd = line.find("<td>");
	int secondtd = line.find("</td>");
	std::string PowerWordName = line.substr(firsttd + 4, secondtd - firsttd - 4);
	line.erase(0, secondtd + 5);

	firsttd = line.find("<td>");
	secondtd = line.find("</td>");
	std::string Material = line.substr(firsttd + 4, secondtd - firsttd - 4);
	line.erase(0, secondtd + 5);


	firsttd = line.find("<td>");
	secondtd = line.find("</td>");
	std::string Age = line.substr(firsttd + 4, secondtd - firsttd - 4);
	line.erase(0, secondtd + 5);


	firsttd = line.find("<td>");
	secondtd = line.find("</td>");
	std::string Corporealform = line.substr(firsttd + 4, secondtd - firsttd - 4);
	line.erase(0, secondtd + 5);

	Statue statue = Statue(PowerWordName, Material, stoi(Age), Corporealform);
	return statue;
}

void HtmlRepository::setSaveListPath(std::string path)
{
	this->savelist->setFilePath(path);
}

void HtmlRepository::setSaveList(std::string type)
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

void HtmlRepository::openInApp()
{
	savelist->openInApp();
	//ShellExecuteA(NULL, NULL, "firefox.exe", file.c_str(), NULL, SW_SHOWMAXIMIZED);
	//de pe d le deschide ok

}

