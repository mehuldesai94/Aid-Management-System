/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#define _CRT_SECURE_NO_WARNINGS

#include"Perishable.h"
using namespace std;

namespace AMA
{
	Perishable::Perishable() :Product('P')
	{
		
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Product::store(file, false);
		file << ",";
		file << date;
		if (newLine)
			file << "\n";

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file)
	{
		Product::load(file);
		date.read(file);
		//file.ignore();
		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		Product::write(os, linear);

		if (!isClear())
			return os;
		if (linear)
			date.write(os);
		else
		{
			os << endl << " Expiry date: ";
			date.write(os);
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		is.clear();
		Product::read(is);
		if (isClear())
		{
			cout << " Expiry date (YYYY/MM/DD): ";
			Date temp;
			temp.read(is);
			if (temp.bad())
			{
				switch (temp.errCode())
				{
				case 1: message("Invalid Price Entry");
					break;
				case 2: message("Invalid Year in Date Entry");
					break;
				case 3: message("Invalid Month in Date Entry");
					break;
				case 4: message("Invalid Day in Date Entry");
				}
				is.setstate(std::ios::failbit);
			}
			if (!is.fail())
				date = temp;
		}
		return is;
	}

	const Date & Perishable::expiry() const
	{
		return date;
	}
}