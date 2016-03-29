#include "Infix_Eval.h"

Infix_Eval::Infix_Eval()
{
	//Default constructor
}

int Infix_Eval::evaluate(string s, ofstream& log_file)
{
	//The algorithm used is Edsger Dijkstra's "Shunting-Yard Algorithm" and is
	//copied from the wikipedia page.
	//See https://en.wikipedia.org/wiki/Shunting-yard_algorithm for more info

	s = convertOperatorsToSingleChars(s);
	log_file << "Converted string:\t" << s << endl;
	unsigned int token = 0;
	while (token < s.length())
	{
		// place holders 
		int prev = token;
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
		// Check to see if - is negative number or subtraction
		else if (c == '-' && (token == 0 || isOperator(s[--prev])))
		{
		// look at - symbol and see if treat as negative or subtraction
		// treat as a negative because after a operator or first in expression
		++token;
		c = s[token];

			// it is a negative number
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
				--token;
			}

			// Subtraction case
			else
			{
				while (!operators.empty() && !operands.empty() && getPrecedence(c) < getPrecedence(operators.top()) && operators.top() != '(')
				{
				solveTop(operators, operands);
				}
				operators.push(c);
			}

		}

		// Look at parens to set priority
		else if (c == '(')
		{
			operators.push(c);
		}

		// Solve the inside of the parens
		else if (c == ')')
		{
			while (!operands.empty() && !operators.empty() && operators.top() != '(')
				solveTop(operators, operands);

		}
			// Other operands, add them
		else if (isOperator(c))
		{
			// Go ahead and solve lower priortiy operators
			while (!operators.empty() && !operands.empty() && getPrecedence(c) < getPrecedence(operators.top()) && operators.top() != '(')
			{
				solveTop(operators, operands);

			}
				
			// Don't push the end of line onto the stack, that would be too much fun
			if (c != '\0')
				operators.push(c);
		}

		// Must be something we can work with (not operator, operand or paren)
		else
		{
			std::string msg = "Calc Error: Code 0_ie_cp, invalid symbol, ";
			msg += c;
			throw std::exception(msg.c_str());
		}

		// Go to the next token
		++token;
	}

	// Finish solving using postfix notation by going through remaining operators
	while (!operators.empty() && !operands.empty())
	{
		solveTop(operators, operands);

	}

	// Return the answer
	if (!operands.empty())
		return int(operands.top());

	// Error, nothing on stack
	else
	{
		std::string msg = "Calc error: no result left on stack, Code 1_ie_cp";
		throw std::exception(msg.c_str());
	}


	return int(operands.top());
}


// Runs calculation using the top operator and top one or two operands
void Infix_Eval::solveTop(stack<char>& operators, stack<double>& operands)
{
	int result = 0;

	// Get the operator
	char c;
	if (!operators.empty())
	{
		c = operators.top();
	}
		
	// Error, nothing on the stack
	else
	{
		std::string msg = "Calc error: Code 2_ie_cp, no operator left to calculate ";
		throw std::exception(msg.c_str());
	}

	// Binary operator
	if (isBinaryOp(c))
	{
		double i1;
		if (!operands.empty())
			i1 = operands.top();

		// Error, nothing on the stack
		else
		{
			std::string msg = "Calc Error: Code 3_ie_cp, no operand left to calculate ";
			msg += c;
			throw std::exception(msg.c_str());
		}

		operands.pop();
		double i2;
		if (!operands.empty())
			i2 = operands.top();

		// Error, nothing on the stack
		else
		{
			std::string msg = "Calc Error: Code 4_ie_cp, no operand left to calculate ";
			msg += c;
			throw std::exception(msg.c_str());
		}
		operands.pop();
		result = int(binarySolve(i1, i2, c));
		log_file << "Pushing " << result  << " to operands\n";
		operands.push(result);
		operators.pop();
	}

	// Unary operator
	else
	{
		double i1 = 0;
		if (!operands.empty())
			i1 = operands.top();

		// Error, nothing on the stack
		else
		{
			std::string msg = "Calc Error: Code 5_ie_cp, no operand left to calculate " + to_string(c);
			throw std::exception(msg.c_str());
		}
		operands.pop();
		result = int(unarySolve(i1, c));
		log_file << "Pushing " << result << " to operands\n";
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

	// Error, invalid operator
	default:
		string msg = "Calc error: Code 6_ie_cp, Symbol '";
		msg += c;
		msg += "' not valid for calculation, exiting calculation";
		throw std::exception(msg.c_str());
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

	// Error, invalid operator
	default:
		string msg = "Calc Error: Code 7_ie_cp, Symbol '";
		msg += c;
		msg += "' not valid for calculation, exiting calculation";
		throw std::exception(msg.c_str());
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
		// Dont divide by them zeros
		if (i1 == 0)
		{
			string msg = "Calc Error: Code 10_ie_cp, Divide by Zero, ";
			msg += to_string(int(i2));
			msg += "/";
			msg += to_string(int(i1));
			throw std::exception(msg.c_str());
		}
		else
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

	// Error, invalid operator
	default:
		string msg = "Calc Error: Code 8_ie_cp, Symbol '";
		msg += c;
		msg += "' not valid for calculation, exiting calculation";
		throw std::exception(msg.c_str());
	}
}

void Infix_Eval::clearData()
{
	
	// Clear operands
	while (!operands.empty())
		operands.pop();
	
	// Clear operators
	while (!operators.empty())
		 operators.pop();

	return;
	
}