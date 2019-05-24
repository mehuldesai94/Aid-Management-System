// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
// learn different types of functions such as helper fucntion, constroctor, operator function.
//
//
//
// Revision History
// -----------------------------------------------------------
// Name: Mehulkumar Desai              Date: 14/03/2018                 Reason:NA
/////////////////////////////////////////////////////////////////

/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#include "Date.h"

namespace AMA {

	//year validator function
	bool yearValidator(int year)
	{
		return year >= min_year && year <= max_year;
	}

	//month validator function
	bool monthValidator(int month)
	{
		return month > 0 && month <= 12;
	}
	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	//set error code to class variable
	void Date::errCode(int errorCode)
	{
		errorState = errorCode;
	}

	//default constroctor
	Date::Date()
	{
		year = 0000;
		month = 00;
		dayOfMonth = 00;
		comparator = 0;
		errorState = NO_ERROR;
	}

	//pramaterise constroctor take date arrguments
	Date::Date(int userYear, int userMonth, int userDay)
	{
		if (yearValidator(userYear) && monthValidator(userMonth) && (userDay > 0 && userDay <= mdays(userMonth, userYear)))
		{
			year = userYear;
			month = userMonth;
			dayOfMonth = userDay;
			comparator = userYear * 372 + userMonth * 13 + userDay;
			errCode(NO_ERROR);
		}
		else if (!yearValidator(userYear))
		{
			*this = Date();
			errCode(YEAR_ERROR);
		}
		else if (!monthValidator(userMonth))
		{
			*this = Date();
			errCode(MON_ERROR);
		}
		else if (userDay < 0 || userDay >= mdays(month, year))
		{
			*this = Date();
			errCode(DAY_ERROR);
		}
		else
		{
			*this = Date();
		}
	}


	//check that object in safe state..
	bool Date::isEmpty() const
	{
		return (year == 0000 && month == 00 && dayOfMonth == 00 && comparator == 0 && errorState == NO_ERROR);
	}

	//check both obj are equal
	bool Date::operator==(const Date& rhs) const
	{
		return (!isEmpty() && !rhs.isEmpty()) ? ((comparator == rhs.comparator) ? true : false) : false;
	}

	//check both obj are not equal
	bool Date::operator!=(const Date& rhs) const
	{
		return (!isEmpty() && !rhs.isEmpty()) ? ((comparator != rhs.comparator) ? true : false) : false;
	}

	//check current object is less than second object
	bool Date::operator<(const Date& rhs) const
	{
		return (!isEmpty() && !rhs.isEmpty()) ? ((comparator < rhs.comparator) ? true : false) : false;
	}

	//check current object is greater than second object
	bool Date::operator>(const Date& rhs) const
	{
		return (!isEmpty() && !rhs.isEmpty()) ? ((comparator > rhs.comparator) ? true : false) : false;
	}

	//check current object is less than or equal second object
	bool Date::operator<=(const Date& rhs) const
	{
		return (!isEmpty() && !rhs.isEmpty()) ? ((comparator <= rhs.comparator) ? true : false) : false;
	}

	//check current object is grater than or qual second object
	bool Date::operator>=(const Date& rhs) const
	{
		return (!isEmpty() && !rhs.isEmpty()) ? ((comparator >= rhs.comparator) ? true : false) : false;
	}

	//return error code of current object
	int Date::errCode() const
	{
		return errorState;
	}

	//return fals of error code is none
	bool Date::bad() const
	{
		return errorState != NO_ERROR;
	}

	//read date from buffer
	std::istream& Date::read(std::istream& istr)
	{
		char slash;
		int tempYear = 0;
		int tempMonth = 0;
		int tempDay = 0;
		istr >> tempYear >> slash >> tempMonth >> slash >> tempDay;
		int monthDays = mdays(tempMonth, tempYear);

		if (istr.fail())
			errCode(CIN_FAILED);
		else if (!yearValidator(tempYear))
			errCode(YEAR_ERROR);
		else if (!monthValidator(tempMonth))
			errCode(MON_ERROR);
		else if (tempDay < 1 || tempDay > monthDays)
			errCode(DAY_ERROR);
		else
		{
			year = tempYear;
			month = tempMonth;
			dayOfMonth = tempDay;
		}

		return istr;
	}

	//print string to output window
	std::ostream& Date::write(std::ostream& ostr) const
	{
		ostr << year << "/";
		ostr.width(2);
		ostr.fill('0');
		ostr << month << "/";
		ostr.width(2);
		ostr.fill('0');
		ostr << dayOfMonth;

		return ostr;
	}

	//istream operator to read date
	std::istream& operator >> (std::istream& is, Date& date)
	{
		return date.read(is);
	}

	//ostream operator to print date
	std::ostream& operator << (std::ostream& os, const Date& date)
	{
		return date.write(os);
	}

}