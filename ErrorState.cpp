/*
Name: Mehulkumar Desai
Student number: 110288172
Email: mmdesai@myseneca.ca
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"ErrorState.h"
using namespace std;



namespace AMA
{

	bool isEmpty(const char* errorMsg)
	{
		return strcmp(errorMsg, "") == 0;
	}

	ErrorState::ErrorState(const char* errorMessage)
	{
		if (errorMessage)
		{
			ptrErrorMessage = new char[strlen(errorMessage) + 1];
			strcpy(ptrErrorMessage, errorMessage);
			//ptrErrorMessage[strlen(ptrErrorMessage) + 1] = '\0';
		}
		else
			ptrErrorMessage = nullptr;
	}


	ErrorState::~ErrorState()
	{
		delete[] ptrErrorMessage;
		ptrErrorMessage = nullptr;
	}

	bool ErrorState::isClear() const
	{
		return ptrErrorMessage == nullptr;
	}

	void ErrorState::message(const char* errMessage)
	{
		delete[] ptrErrorMessage;
		ptrErrorMessage = nullptr;
		ptrErrorMessage = new char[strlen(errMessage) + 1];
		strcpy(ptrErrorMessage, errMessage);
	}

	char* ErrorState::message() const
	{
		return ptrErrorMessage;
	}

	void ErrorState::clear()
	{
		delete[] ptrErrorMessage;
		ptrErrorMessage = nullptr;
	}

	std::ostream& operator << (std::ostream& os, const ErrorState& errorState)
	{
		if (errorState.message())
			os << errorState.message();

		return os;
	}
}
