#include "RepositoryException.h"

const char* FileException::what()
{
	return exceptionmessage.c_str();
}


const char* RepositoryException::what()
{
	return this->exceptionmessage.c_str();
}

const char* DuplicateStatueException::what()
{
	return " There is another Statue with the same PowerWordName";
}