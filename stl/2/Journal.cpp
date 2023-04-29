#include "Journal.h"

Journal::Journal(size_t id,
	             size_t course, 
	             const char* group_code,
	             const char* surname,
	             const char* student_id_number,
	             const char* subject,
	             size_t estimation)
	: ID(id),
	  Course(course),
	  Estimation(estimation)
{
	strcpy_s(Group_Code, group_code);
	strcpy_s(Surname, surname);
	strcpy_s(Student_ID_number, student_id_number);
	strcpy_s(Subject, subject);
}

ostream& operator<<(ostream& out, const Journal& journal)
{
	out << journal.ID << " "
		<< journal.Course << " "
		<< journal.Group_Code << " "
		<< journal.Surname << " "
		<< journal.Student_ID_number << " "
		<< journal.Subject << " "
		<< journal.Estimation;
	return out;
}

istream& operator>>(istream& in, Journal& journal)
{
	cout << "Input course number: ";
	in >> journal.Course;
	cout << "Input group code: ";
	in >> journal.Group_Code;
	cout << "Input surname: ";
	in >> journal.Surname;
	cout << "Input student id number: ";
	in >> journal.Student_ID_number;
	cout << "Input subject: ";
	in >> journal.Subject;
	cout << "Input estimation: ";
	in >> journal.Estimation;
	return in;
}
