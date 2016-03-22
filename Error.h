#pragma once
#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>
using namespace std;

class Error
{
private:

	//Data fields
	string message;
	int index;

public:

	//Constructors
	Error(const string& theMessage, int theIndex) :message(theMessage), index(theIndex) {} //Defining constructor

	void Report() const; //Report the error in the main program.
};

#endif