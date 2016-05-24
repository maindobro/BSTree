#pragma once
#include <exception>
using namespace std;

class BSTreeException : public std::invalid_argument
{
public:
	BSTreeException() : std::invalid_argument("Unknown exception") {};
	BSTreeException(const char *_message) : std::invalid_argument(_message) {};
};
class EmptyException : public BSTreeException
{
public:
	EmptyException() : BSTreeException("Tree is empty") {};
};
class InputException : public BSTreeException
{
public:
	InputException() : BSTreeException("Error in input") {};
};
class InputFileException : public BSTreeException
{
public:
	InputFileException() : BSTreeException("Error in input from file") {};
};
