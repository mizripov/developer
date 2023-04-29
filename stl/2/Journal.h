#ifndef _JOURNAL_H_
#define _JOURNAL_H_

#include "Header.h"

struct Journal
{
	size_t ID;
	size_t Course;
	char Group_Code[10];
	char Surname[25];
	char Student_ID_number[10];
	char Subject[25];
	size_t Estimation;

	Journal() = default;
	Journal(size_t, size_t, const char*, const char*, const char*, const char*, size_t);

	friend ostream& operator<<(ostream&, const Journal&);
	friend istream& operator>>(istream&, Journal&);

};

#endif // !_JOURNAL_H_
