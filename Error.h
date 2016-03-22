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
	Error() :index(-1) { ; } //Default constructor
	Error(const string& theMessage, int theIndex) :message(theMessage), index(theIndex) { ; } //Defining constructor

																											//Member function
	void Report() const; //Report the error in the main program.
};

#endif