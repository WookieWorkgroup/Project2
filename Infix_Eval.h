#ifndef INFIX_EVAL
#define INFIX_EVAL

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>

using namespace std;

class Infix_Eval {
public:
	Infix_Eval();
	int evaluate(string s);
private:
	bool isOperator(char c);
	int getPrecedence(char c);
	void replaceAll(string& str, const string& from, const string& to);
	string convertOperatorsToSingleChars(string s);
	int unarySolve(int i, char c);
	double binarySolve(double i1, double i2, char c);

	const string OPERATORS = "!@#-^*/%+>$<~`:&|";
	const string PRECEDENCE = "88887666544443321";
	stack<char> operators;
	stack<double> operands;
};

#endif