#pragma once
#include<iostream>;

#ifndef INPUTINSPECT_H
#define INPUTINSPECT_H

#include "Error.h"
#include <string>
#include <vector>
using namespace std;

/* Inspect if the input is correct. */
class Inputinspect
{
private:

	//Data fields
	string brac_front;
	string binoper;
	string brac_back;

public:

	//Constructors
	Inputinspect() { ; }; //Default constructor

	bool Inputinspect::isOperator(char ch) const;
	string Inputinspect::ReadInput(string input, string output, vector<int> indices, string operators);
							 //Member functions
	void SplitOperator(const string& text, const vector<int>& indices); //Split the operator into bracket_back, binaryoperator, and bracket_front spaces.
	void SplitFrontOperator(const string& text, const vector<int>& indices); //Split the operator in front of all the operands (if the expression has).
	void SplitBackOperator(const string& text, const vector<int>& indices); //Split the operator after all the operands.
};

#endif