#ifndef _RECORDS_H_
#define _RECORDS_H_

#include "Journal.h"
#include "Exception.h"

class Records
{
public:
	explicit Records(const string);
	void addRecord(Journal&);
	void delRecord(const size_t);
	void replaceRecord(const size_t, Journal&);
	void toText();
	void searchByCourse(const size_t);
	void searchByGroup(const string&);
	void searchByStudentIdNumber(const string&);
	void searchBySurname(const string&);
	void searchByEstimation(const size_t);
	void calcAverageScoreSubject(const string&);
	void calcAverageScoreGroup(const string&);
	void calcAverageScoreCourse(const size_t);
private:
	map<size_t, Journal> Container;
	string filename;
	size_t key = 0;
	void getContainer();
};

#endif // !_RECORDS_H_
