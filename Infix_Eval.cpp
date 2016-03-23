#include "Infix_Eval.h"

Infix_Eval::Infix_Eval()
{
	//Default constructor
}

int Infix_Eval::evaluate(string s)
{
	//The algorithm used is Edsger Dijkstra's "Shunting-Yard Algorithm" and is
	//copied from the wikipedia page.
	//See https://en.wikipedia.org/wiki/Shunting-yard_algorithm for more info

	s = convertOperatorsToSingleChars(s);
	cout << "Converted string:\t" << s << endl;
	int token = 0;
	while (token < s.length())
	{
		char c = s[token];
		if (isdigit(c))
		{
			// Check for more digits
			int number = 0;
			while (token < s.length() && isdigit(c))
			{
				
				number *= 10;
				number += c - 48;
				++token;
				c = s[token];
			}
			--token;
			c = s[token];

			// put the number into the stack
			operands.push(number);
		}
		else if (isOperator(c))
		{
			// look at - symbol and see if treat as negative or subtraction
			int temp = token;		

			// treat as a negative because after a operator or first in expression
			if (c == '-' && (token == 0 || isOperator(s[--temp])))
			{
				++token;
				c = s[token];

				// Get the number
				if (isdigit(c))
				{
					// Check for more digits
					int number = 0;
					while (token < s.length() && isdigit(c))
					{
						number *= 10;
						number += c - 48;
						++token;
						c = s[token];
					}

					// Make it negative and add to operands
					number *= -1;
					operands.push(number);
				
				}
			
				

			}
			
			// Look at exponet
			else if (c == '^')
			{
				while (!operators.empty() && !operands.empty() && getPrecedence(c) < getPrecedence(operators.top()))
				{
					solveTop(operators, operands);
					if (!operators.empty())operators.pop();
				}
			}

			// Other operands
			else
			{
				while (!operators.empty() && !operands.empty() && getPrecedence(c) <= getPrecedence(operators.top()))
				{
					solveTop(operators, operands);
					if (!operators.empty())operators.pop();
				}
			}

			// Don't push the end of line onto the stack, that would be too much fun
			if (c != '\0')
				operators.push(c);
		}

		// Look at parens to set priority
		else if (c == '(')
		{
			operators.push(c);
		}

		else if (c == ')')
		{
			while (!operands.empty() && !operators.empty() && operators.top() != '(')
			{
				solveTop(operators, operands);
				if (!operators.empty())operators.pop();
			}
			if (!operators.empty())operators.pop();
		}

		// Go to the next token
		++token;
	}

	// Finish solving using postfix notation by going through remaining operators
	while (!operators.empty() && !operands.empty())
	{
		solveTop(operators, operands);
		if(!operators.empty())operators.pop();
	}

	// Return the answer
	return operands.top();
}


// Runs calculation using the top operator and top one or two operands
void Infix_Eval::solveTop(stack<char>& operators, stack<double>& operands)
{
	int result = 0;

	// Get the operator
	char c = operators.top();

	// Binary operator
	if (isBinaryOp(c))
	{
		double i1 = operands.top();
		operands.pop();
		double i2 = operands.top();
		operands.pop();
		result = binarySolve(i1, i2, c);
		cout << "Pushing " << result  << " to operands\n";
		operands.push(result);
		operators.pop();
	}

	// Unary operator
	else
	{
		double i1 = operands.top();
		operands.pop();
		result = unarySolve(i1, c);
		cout << "Pushing " << result << " to operands\n";
		operands.push(result);
		operators.pop();
	}
	
}



// Calcualation for binary operator
bool Infix_Eval::isBinaryOp(char c)
{
	return BINARY_OPERATORS.find(c) != string::npos;
}



//Returns whether or not c is an operator
bool Infix_Eval::isOperator(char c)
{
	return OPERATORS.find(c) != string::npos;
}


//Gets the precedence, as an int, of operation c, higher numbers are higher presendence 
int Infix_Eval::getPrecedence(char c)
{
	switch (c)
	{
	case '(':
	case ')':
		return 9;
	case '!':
	case '@':
	case '#':
		return 8;
	case '^':
		return 7;
	case '*':
	case '/':
	case '%':
		return 6;
	case '+':
	case '-':
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

	//replaceAll(result, "-", "+-");
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
	case '(':
		return i;

		return i;
	}
}


//Returns the solved binary expression of operation c on operands i1 and i2
double Infix_Eval::binarySolve(double i1, double i2, char c)
{
	switch (c)
	{
	case '-':
		return(i2 - i1);
	case '^':
		return pow(i2, i1);
	case '*':
		return i2*i1;
	case '/':
		return i2 / i1;
	case '%':
		return (int)i2 % (int)i1;
	case '+':
		return i2 + i1;
	case '>':
		return i2 > i1;
	case '$':
		return i2 >= i1;
	case '<':
		return i2 < i1;
	case '~':
		return i2 <= i1;
	case '`':
		return i2 == i1;
	case ':':
		return i2 != i1;
	case '&':
		return i2 && i1;
	case '|':
		return i2 || i1;


	}
}