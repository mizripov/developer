#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "Header.h"

class FileNotFound
{
public:
	FileNotFound()
	{
		error.assign("ERROR: File is not found.");
	}
	void getError()
	{
		cout << error << endl;
	}
private:
	string error;
};

#endif // !_EXCEPTION_H_
