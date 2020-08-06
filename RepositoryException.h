#pragma once

#include <exception>
#include <string>

class RepositoryException : public std::exception
{
protected:
	std::string exceptionmessage;

public:
	RepositoryException() {};
	RepositoryException(const std::string& exceptionmessage) { this->exceptionmessage = exceptionmessage; };
	virtual const char* what();
};

class DuplicateStatueException : public RepositoryException
{
public:
	const char* what();
};

class FileException : public RepositoryException
{
protected:
	std::string exceptionmessage;

public:
	FileException(const std::string& exceptionmessage) { this->exceptionmessage = exceptionmessage; };
	virtual const char* what();
};