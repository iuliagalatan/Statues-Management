#include "Domain.h"
#include <iostream>
#include <string>
#include <vector>

Statue::Statue(std::string const powerWordName, std::string const material, int const age, std::string const corporealForm)
{
	this->age = age;
	this->corporealForm = corporealForm;
	this->material = material;
	this->powerWordName = powerWordName;

}

Statue::Statue()
{
	this->age = 0;
	this->corporealForm = "";
	this->material = "";
	this->powerWordName = "";
}

std::string Statue::ToString() const
{
	return "powerWordName: " + this->powerWordName + "\nmaterial: " + this->material + "\nage: " +
		std::to_string(this->age) + "\ncorporealform: " + this->corporealForm + "\n";
}


std::istream& operator>>(std::istream& istream,Statue& statue)
{
	std::string line;
	std::string templatestatue[4];
	if (std::getline(istream, line))
	{
		std::stringstream stringstream(line);

		if (
			std::getline(stringstream, templatestatue[0], ',') &&
			std::getline(stringstream, templatestatue[1], ',') &&
			std::getline(stringstream, templatestatue[2], ',') &&
			std::getline(stringstream, templatestatue[3]))
		{
			for (int i = 0; i < 4; ++i)
				templatestatue[i].erase(remove_if(templatestatue[i].begin(), templatestatue[i].end(), isspace), templatestatue[i].end());
			statue.powerWordName = templatestatue[0];
			statue.material = templatestatue[1];
			statue.age = stoi(templatestatue[2]);
			statue.corporealForm = templatestatue[3];

		}
		
	}
	return istream;
}

std::ostream& operator<<(std::ostream& os, const Statue& statue)
{
	std::string towrite = statue.GetPowerWordName() + ", " + statue.GetMaterial() + ", " + std::to_string(statue.GetAge()) + ", " + statue.GetCorporealForm();
	os << towrite;
	return os;
}
