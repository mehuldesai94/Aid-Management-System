/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#ifndef DATE_H
#define DATE_H
#include<iostream>
using namespace std;

namespace AMA
{

#define NO_ERROR 0 //--No error - the date is valid
#define CIN_FAILED 1 //--istream failed on information entry
#define YEAR_ERROR 2 //--Year value is invalid
#define MON_ERROR 3 //--Month value is invalid
#define DAY_ERROR 4 //--Day value is invalid
	const int min_year = 2000;
	const int max_year = 2030;

	class Date
	{

		int year;
		int month;
		int dayOfMonth;
		int comparator;
		int errorState;
		int mdays(int, int) const;
		void errCode(int);
	public:
		Date();
		Date(int, int, int);
		bool isEmpty() const;
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};


	std::istream& operator >> (std::istream& is, Date& date);
	std::ostream& operator << (std::ostream& os, const Date& date);
}


#endif // !DATE_H