/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include"ErrorState.h"
#include"iProduct.h"

namespace AMA
{

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const int currentTAX = 13;

	class Product : public iProduct
	{
		char productType;
		char productSKU[max_sku_length + 1];
		char productUnit[max_unit_length + 1];
		char* productName;
		int quantityOnHand;
		int quantityNeed;
		double productPrice;
		bool isTaxable;
		void init(const Product&);
		ErrorState errorState;

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Product(const char type = 'N');
		Product(const char*, const char*, const char*, const int curQuantityOnHand = 0, const bool isTaxAvailable = true, const double price = 0.0, const int curQuantityOnNeed = 0);
		Product(const Product&);
		Product& operator= (const Product&);
		~Product();
		std::fstream& store(std::fstream&, bool newLine = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool linear) const;
		std::istream& read(std::istream&);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty()const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iProduct&) const;
		int operator+=(int);
	};

	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
}

#endif // !AMA_PRODUCT_H
