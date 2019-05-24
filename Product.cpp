/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<fstream>
#include"Product.h"
#include"ErrorState.h"
using namespace std;

namespace AMA
{
	//function receives the address of a C-style null-terminated string that holds the name of the product and store in class variable
	void Product::name(const char* pName)
	{
		if (pName != nullptr)
		{
			if (productName != nullptr)
			{
				delete[] productName;
				productName = nullptr;
			}

			productName = new char[(strlen(pName)) + 1];
			strcpy(productName, pName);
		}
		else
			productName = nullptr;
	}

	// returns the name of the product
	const char* Product::name() const
	{
		if (productName != nullptr)
			return productName;
		else
			return nullptr;
	}

	// returns the sku of the product
	const char* Product::sku() const
	{
		return productSKU;
	}

	// returns unit of the product
	const char* Product::unit() const
	{
		return productUnit;
	}

	// return taxable status of the product TRUE or FALSE
	bool Product::taxed() const
	{
		return isTaxable;
	}

	// returns the price of the product
	double Product::price() const
	{
		return productPrice;
	}

	// returns taxable price to the product
	double Product::cost() const
	{
		if (isTaxable)
			return productPrice* (((double)currentTAX / 100) + 1);
		else
			return productPrice;
	}

	// stores an error message in the ErrorState object
	void Product::message(const char* errMessage)
	{
		errorState.message(errMessage);
	}

	// returns of the ErrorState object is clear or not
	bool Product::isClear() const
	{
		if (errorState.isClear())
			return true;
		else
			return false;
	}

	// common code to be called from copy constructor and copy assignment operator
	void Product::init(const Product& product)
	{
		productType = product.productType;
		strncpy(productSKU, product.productSKU, strlen(product.productSKU));
		productSKU[strlen(product.productSKU)] = '\0';
		strncpy(productUnit, product.productUnit, strlen(product.productUnit));
		productUnit[strlen(product.productUnit)] = '\0';
		quantityOnHand = product.quantityOnHand;
		quantityNeed = product.quantityNeed;
		productPrice = product.productPrice;
		isTaxable = product.isTaxable;
		productName = nullptr;
		name(product.productName);
	}

	// sets object to safe empty state
	Product::Product(const char proType)
	{
		productType = proType;
		productSKU[0] = '\0';
		productUnit[0] = '\0';
		productName = nullptr;
		quantityOnHand = 0;
		quantityNeed = 0;
		productPrice = 0;
		isTaxable = false;
		errorState.ErrorState::clear();

	}

	// ]sets received data to the current object
	Product::Product(const char* sku, const char* pname, const char* unit, const int curQuantityOnHand, const bool isTaxAvailable, const double price, const int curQuantityOnNeed)
	{
		if (sku != nullptr)
		{
			strncpy(productSKU, sku, strlen(sku));
			productSKU[strlen(sku)] = '\0';
		}

		productName = nullptr;
		name(pname);
		strncpy(productUnit, unit, strlen(unit));
		productUnit[strlen(unit)] = '\0';

		quantityOnHand = curQuantityOnHand;
		isTaxable = isTaxAvailable;
		productPrice = price;
		quantityNeed = curQuantityOnNeed;
	}


	// copies received object to the current object
	Product::Product(const Product& localProduct)
	{
		init(localProduct);
	}

	// replaces current object with a reference object
	Product& Product::operator=(const Product& localProduct)
	{
		if (this != &localProduct)
		{
			delete[] productName;
			productName = nullptr;
			init(localProduct);
		}
		return *this;
	}

	// deallocates allocated memory of product name
	Product::~Product()
	{
		delete[] productName;
		productName = nullptr;
	}

	// inserts data into fstream data from current object
	std::fstream& Product::store(std::fstream& file, bool newLine) const
	{
		file << productType << "," << productSKU << "," << productName<< ",";
		file << productUnit << "," << isTaxable  << "," << productPrice  << ",";
		file << quantityOnHand << "," << quantityNeed;

		if (newLine)
			file << endl;

		return file;
	}

	// extracts the fields from fstream to temporary object and copies that object to the current object
	std::fstream& Product::load(std::fstream& file)
	{
		Product productTemp;
		char name[max_name_length + 1];
		char tax;
		//file.ignore();
		file.getline(productTemp.productSKU, max_sku_length, ',');
		//file.ignore();
		file.getline(name, max_name_length + 1, ',');;
		productTemp.name(name);
		file.getline(productTemp.productUnit, max_unit_length, ',');
		//file.ignore();
		
		//file.ignore();
		file >> tax;

		if (tax == '1')
			productTemp.isTaxable = true;
		else if (tax == '0')
			productTemp.isTaxable = false;

		file.ignore();
		file >> productTemp.productPrice;
		file.ignore();
		file >> productTemp.quantityOnHand;
		file.ignore();
		file >> productTemp.quantityNeed;
		file.ignore();
		
		*this = productTemp;

		return file;
	}

	// insert current object's fields into ostream in different format accorfing to flag
	std::ostream& Product::write(std::ostream& os, bool linear) const
	{

		if (!errorState.isClear())
		{
			os << errorState.message();
			return os;
		}
		if (linear)
		{
			os.fill(' ');
			os.width(max_sku_length);
			os.setf(ios::left);
			os << productSKU << "|";

			os.fill(' ');
			os.width(20);
			os.fill(' ');
			os << productName << "|";
			os.unsetf(ios::left);

			os.fill(' ');
			os.setf(ios::fixed);
			os.width(7);
			os.precision(2);
			os << cost() << "|";
			
			os.fill(' ');
			os.width(4);
			os << quantityOnHand << "|";


			os.setf(ios::left);
			os.fill(' ');
			os.width(10);
			os << unit() << "|";

			os.unsetf(ios::left);
			os.fill(' ');
			os.width(4);
			os << quantityNeed << "|";
			os.setf(ios::fixed);
		}
		else
		{
			os << " Sku: " << sku() << endl;
			os << " Name (no spaces): " << name() << endl;
			os << " Price: " << price() << endl;
			if (taxed())
				os << " Price after tax: " << cost() << endl;
			else
				os << " Price after tax: " << "N/A" << endl;

			os << " Quantity on Hand: " << quantityOnHand << ' ' << unit() << endl;
			os << " Quantity needed: " << quantityNeed;
		}
		return os;
	}

	// extracts the data field of current object from istream
	std::istream& Product::read(std::istream& is)
	{
		errorState.clear();
		char sku[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit_[max_unit_length + 1];
		int  unitsQuantity, productNeeded;
		double price_;
		char taxable;
		bool end = false;

		while (end == false)
		{
			end = true;
			cout << " Sku: ";
			is >> sku;
			cout << " Name (no spaces): ";
			is >> name;
			cout << " Unit: ";
			is >> unit_;
			cout << " Taxed? (y/n): ";
			is >> taxable;
			if (taxable != 'y' && taxable != 'Y' && taxable != 'n' && taxable != 'N')
			{
				errorState.message("Only (Y)es or (N)o are acceptable");
				is.setstate(std::ios::failbit);
				break;
			}


			cout << " Price: ";
			is >> price_;
			if (is.fail())
			{
				errorState.message("Invalid Price Entry");
				is.setstate(std::ios::failbit);
				break;
			}

			cout << " Quantity on hand: ";
			is >> unitsQuantity;
			if (is.fail())
			{
				errorState.message("Invalid Quantity Entry");
				is.setstate(std::ios::failbit);
				break;
			}

			cout << " Quantity needed: ";
			is >> productNeeded;
			if (is.fail())
			{
				errorState.message("Invalid Quantity Needed Entry");
				break;
			}

			is.clear();    // Restore input stream to working state
			is.ignore();
		}

		if (!is.fail() && errorState.isClear())
		{
			strcpy(productSKU, sku);
			this->name(name);
			strcpy(productUnit, unit_);
			quantityOnHand = unitsQuantity;
			if (taxable == 'y' || taxable == 'Y')
				isTaxable = true;
			else if (taxable == 'n' || taxable == 'N')
				isTaxable = false;
			productPrice = price_;
			quantityNeed = productNeeded;
		}

		
		return is;
	}

	// returns true if the string is identical to the sku of the current object
	bool Product::operator==(const char* curSKU) const
	{
		return (sku() == curSKU) ? true : false;
	}

	// returns the total cost of all items
	double Product::total_cost() const
	{
		return cost()*quantityOnHand;
	}

	// resets the number of units on hand 
	void Product::quantity(int currUnits)
	{
		quantityOnHand = currUnits;
	}

	// returns true if the object is in a safe empty state
	bool Product::isEmpty()const
	{
		return((quantityOnHand == -1) && (productSKU[0] == '\0') &&
			(productName == nullptr) && (quantityNeed == -1) &&
			(quantityNeed == -1) && (productPrice == -1) && (isTaxable == 0));
	}

	// returns the number of products that are needed
	int Product::qtyNeeded() const
	{
		return quantityNeed;
	}

	// returns the number of product that are on hand
	int Product::quantity() const
	{
		return quantityOnHand;
	}

	// returns true if the sku of the current object is greater than client code
	bool Product::operator>(const char* currSKU) const
	{
		return sku() > currSKU;
	}

	// returns true if the name of the current object is greater than client code name
	bool Product::operator>(const iProduct& product) const
	{
		return (strlen(productName)>strlen(product.name()));
	}

	//add into current quantity if positive value
	int Product::operator+=(int newUnits) {
		if (newUnits > 0)
			quantityOnHand += newUnits;

		return quantityOnHand;
	}

	// set a Product record into the ostream
	ostream& operator<<(std::ostream& os, const iProduct& product)
	{
		return product.write(os, true);
	}

	// extracts the Product record from the istream
	istream& operator>>(istream& is, iProduct& product)
	{
		return product.read(is);
	}

	// adds the	total cost of the Product object to the double received
	double operator+=(double& finalDouble, const iProduct& product)
	{
		finalDouble += product.total_cost();
		return finalDouble;
	}
}


