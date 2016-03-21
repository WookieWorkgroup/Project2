#include "Infix_Eval.h"

Infix_Eval::Infix_Eval()
{
	//Default constructor, not used at the moment
}

int Infix_Eval::evaluate(string s)
{
	//The algorithm used is Edsger Dijkstra's "Shunting-Yard Algorithm" and is
	//copied from the wikipedia page.
	//See https://en.wikipedia.org/wiki/Shunting-yard_algorithm for more info

	int token = 0;
	while (token < s.length())
	{
		char c = s[token];
		if (isdigit(c))
		{
			output.push(c);
		}
		else if (isOperator(c))
		{
			if (c == '^')
			{
				while (!operators.empty() && getPrecedence(c) < getPrecedence(operators.top()))
				{
					output.push(operators.top());
					if (!operators.empty())operators.pop();
				}
			}
			else
			{
				while (!operators.empty() && getPrecedence(c) <= getPrecedence(operators.top()))
				{
					output.push(operators.top());
					if (!operators.empty())operators.pop();
				}
			}
			operators.push(c);
		}
		else if (c == '(')
		{
			operators.push(c);
		}
		else if (c == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				output.push(operators.top());
				if (!operators.empty())operators.pop();
			}
			if (!operators.empty())operators.pop(); //removes the opening parentheses
		}
		++token;
	}
	while (!operators.empty())
	{
		output.push(operators.top());
		if(!operators.empty())operators.pop();
	}

	return 0;
}

string Infix_Eval::getOutput()
{
	stringstream ss;
	while (!output.empty())
	{
		ss << output.front();
		output.pop();
	}
	return ss.str();
}

//Returns whether or not c is an operator
bool Infix_Eval::isOperator(char c)
{
	return OPERATORS.find(c) != string::npos;
}

//Gets the precedence, as an int, of operation c
int Infix_Eval::getPrecedence(char c)
{
	switch (c)
	{
	case '!':
	case '@':
	case '#':
	case '-':
		return 8;
	case '^':
		return 7;
	case '*':
	case '/':
	case '%':
		return 6;
	case '+':
		return 5;
	case '>':
	case '$':
	case '<':
	case '~':
		return 4;
	case '`':
	case ':':
		return 3;
	case '&':
		return 2;
	case '|':
		return 1;
	default:
		return -1;
	}
}

//Cleans string for processing, more details inside function
string Infix_Eval::convertOperatorsToSingleChars(string s)
{
	string result = s;
	/*
	This here function does some funky stuff, so pay attention.
	In order to treat all of the operators as a single char, we're going
	to substitute in some random chars such as @,#,etc... in place of the
	operators that are two chars long such as '=='. I have included a list for quick reference.

	++ replaced with @
	-- replaced with #
	>= replaced with $
	<= replaced with ~
	== replaced with `
	!= replaced with :
	&& replaced with &
	|| replaced with |

	This will make it easier to put onto the stack and to see what calculations we need to be doing. It
	also avoid complications because now operators such as '!' and '!=' will not share the same
	initial char.

	This way, our function just needs to get one char and use that as the operator. This function takes in one string and returns another so that we can save
	the original string value without replacing it.
	*/
	replaceAll(result, "++", "@");
	replaceAll(result, "--", "#");
	replaceAll(result, ">=", "$");
	replaceAll(result, "<=", "~");
	replaceAll(result, "==", "`");
	replaceAll(result, "!=", ":");
	replaceAll(result, "&&", "&");
	replaceAll(result, "||", "|");

	/*
	Continued confession time:

	I got rid of the minus sign as an operator for subtraction. Instead, every minus sign is treated as a negation of the following number. The following replaceAll command
	modifies each minus sign so that we can "add the negative" instead. It is important that this last step is done after the replaceAll(result, "--", "#"); call, otherwise
	the decrement operator would get screwed up.
	*/

	replaceAll(result, "-", "+-");
	return result;
}

//Given the string str, it replaces each instance of "from" with "to"
void Infix_Eval::replaceAll(string& str, const string& from, const string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

//Returns the solved unary expression of operation c on operand i
int Infix_Eval::unarySolve(int i, char c)
{
	switch (c)
	{
	case '!':
		return !i;
	case '@':
		return ++i;
	case '#':
		return --i;
	case '-':
		return -i;
	}
}

//Returns the solved binary expression of operation c on operands i1 and i2
double Infix_Eval::binarySolve(double i1, double i2, char c)
{
	switch (c)
	{
	case '^':
		return pow(i1, i2);
	case '*':
		return i1*i2;
	case '/':
		return i1 / i2;
	case '%':
		return (int)i1 % (int)i2;
	case '+':
		return i1 + i2;
	case '>':
		return i1 > i2;
	case '$':
		return i1 >= i2;
	case '<':
		return i1 < i2;
	case '~':
		return i1 <= i2;
	case '`':
		return i1 == i2;
	case ':':
		return i1 != i2;
	case '&':
		return i1 && i2;
	case '|':
		return i1 || i2;
	}
}