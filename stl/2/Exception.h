#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "Header.h"

class MyException
{
public:
	MyException(const string);
	void what();
private:
	string message;
};

#endif // !_EXCEPTION_H_
