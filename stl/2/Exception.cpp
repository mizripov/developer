#include "Exception.h"

MyException::MyException(const string message)
{
	this->message = message;
}

void MyException::what()
{
	cout << message << endl;
}
