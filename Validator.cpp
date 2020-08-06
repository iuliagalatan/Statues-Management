#include "Validator.h"
#include <cstring>

void Validator::validate_statue(const Statue& statue)
{
	std::vector<std::string> errors;
	/*
	if (statue.GetPowerWordName().size() <= 1)
		errors.push_back("The Statue id cannot be less than 1 character!\n");
	if (statue.GetAge() < 0)
		errors.push_back("The Age of the statue can t be negative!");
	if (statue.GetCorporealForm().size() < 1)
		errors.push_back("The statue resembles nothing but a piece of dirt. No worries. Just dont let the CorporealForm field empty");
		*/
	if (errors.size() > 0)
		throw StatueException(errors);
}

StatueException::StatueException(std::vector<std::string> errors)
{
	this->errors = errors;
}

const char* StatueException::what()
{
	//char buff[1000] = "";
	std::string buff;
	for (auto error : errors)
		buff += error;
	return buff.c_str();
}