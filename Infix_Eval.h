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
#include "Syntax_Error.h"


using namespace std;

class Infix_Eval {
public:
	Infix_Eval();
	int evaluate(string s);
	string returnOutput();
private:
	void solveTop(stack<char>& operators, stack<double>& operands);
	bool isBinaryOp(char c);
	bool isOperator(char c);
	void replaceAll(string& str, const string& from, const string& to);
	string convertOperatorsToSingleChars(string s);
	int unarySolve(int i, char c);
	double binarySolve(double i1, double i2, char c);
	int getPrecedence(char c);
	const string OPERATORS = "!@#-^*/%+>$<~`:&|";
	const string BINARY_OPERATORS = "^* / %+->$<~`:& | ";
	stack<char> operators;
	stack<double> operands;
	string output;
};

#endif