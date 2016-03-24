#ifndef INFIX_EVAL
#define INFIX_EVAL

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <cctype>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Syntax_Error.h"


using namespace std;

class Infix_Eval {
public:

	// Constructor
	Infix_Eval();

	// Main expression evaluation function
	int evaluate(string s, ofstream& log_file);
	void clearData();

private:

	// Calculation functions
	void solveTop(stack<char>& operators, stack<double>& operands);
	bool isBinaryOp(char c);
	bool isOperator(char c);
	int unarySolve(int i, char c);
	double binarySolve(double i1, double i2, char c);
	int getPrecedence(char c);
	ofstream log_file;
	

	// Replace symbols for operators so all are single chars
	void replaceAll(string& str, const string& from, const string& to);
	string convertOperatorsToSingleChars(string s);

	// Our internal data
	const string OPERATORS = "!@#-^*/%+>$<~`:&|";
	const string BINARY_OPERATORS = "^* / %+->$<~`:& | ";
	stack<char> operators;
	stack<double> operands;
};

#endif