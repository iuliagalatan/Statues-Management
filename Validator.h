#pragma once
#include <exception>
#include "Domain.h"
#include <vector>

class Validator
{
public:

	void validate_statue(const Statue& statue);
};

class StatueException : public std::exception
{
private:
	std::vector<std::string> errors;

public:
	StatueException(std::vector<std::string> _errors);
	const char* what();
};