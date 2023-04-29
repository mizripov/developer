#ifndef _MYEXCEPTION_
#define _MYEXCEPTION_

#include "Header.h"

class MyException
{
private:
	string message;
public:
	MyException(const string msg)
	{
		message = msg;
	}
	void what_mean()
	{
		cout << this->message << endl;
	}
};
#endif // !_MYEXCEPTION_
