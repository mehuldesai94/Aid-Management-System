/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include<iostream>
using namespace std;

namespace AMA
{
	class ErrorState
	{
		char* ptrErrorMessage;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState& operator= (const ErrorState&) = delete;
		virtual ~ErrorState();
		bool isClear() const;
		void message(const char*);
		char* message() const;
		void clear();
	};

	std::ostream& operator << (std::ostream& os, const ErrorState& errorState);
}

#endif // !ERROR_STATE_H
