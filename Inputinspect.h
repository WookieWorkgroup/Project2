#pragma once

#ifndef INPUTINSPECT_H
#define INPUTINSPECT_H

#include<iostream>
#include <string>
#include <vector>
using namespace std;

/* Inspect if the input is correct. */
class Inputinspect
{
private:

	//Error message
	string message;
	int index;

public:
	//Constructors
	Inputinspect() {; };					 //Default constructor
	bool isOperator(char ch) const;			 //Judge if the character is a operator
	string OptimizeInput(string input);		 //Inspect the space error and remove the space	
	void InspectOperator(string text);		 //inspect the operator error
	string Processinput(string input);		 //the wrapper function
	void Error_Report(const string& theMessage, int theIndex);		//Error report function
};

#endif
