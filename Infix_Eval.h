#ifndef INFIX_EVAL
#define INFIX_EVAL

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <sstream>
#include <cctype>

using namespace std;

class Infix_Eval {
public:
	Infix_Eval();
	int evaluate(string s);
	string getOutput();
private:
	bool isOperator(char c);
	void replaceAll(string& str, const string& from, const string& to);
	string convertOperatorsToSingleChars(string s);
	int unarySolve(int i, char c);
	double binarySolve(double i1, double i2, char c);
	int getPrecedence(char c);
	const string OPERATORS = "!@#-^*/%+>$<~`:&|";
	stack<char> operators;
	queue<char> output;
};

#endif