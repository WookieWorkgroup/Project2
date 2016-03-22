#pragma once
#include<iostream>;

#ifndef Operatorinspect_H
#define Operatorinspect_H

#include "Error.h"
#include <string>
#include <vector>
using namespace std;

/* Inspect if the input is correct. */
class Operatorinspect
{
private:

	//Data fields
	string brac_front;
	string binoper;
	string brac_back;

public:

	//Constructors
	Operatorinspect() { ; }; //Default constructor

							 //Member functions
	void SplitOperator(const string& text, const vector<int>& indices); //Split the operator into bracket_back, binaryoperator, and bracket_front spaces.
	void SplitFrontOperator(const string& text, const vector<int>& indices); //Split the operator in front of all the operands (if the expression has).
	void SplitBackOperator(const string& text, const vector<int>& indices); //Split the operator after all the operands.
};

#endif