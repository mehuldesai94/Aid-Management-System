/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include"Date.h"
#include"Product.h"
namespace AMA
{
	class Perishable : public Product
	{
		Date date;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
}


#endif // !AMA_PERISHABLE_H

