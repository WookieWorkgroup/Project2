#include "Infix_Eval.h"

Infix_Eval::Infix_Eval()
{

}

int Infix_Eval::evaluate(string s)
{
	char op;
	double d1, d2;
	int current_precedence = 8;
	s = convertOperatorsToSingleChars(s);

	for (int i = 0; i < s.length(); ++i)
	{
		if (isdigit(s[i]) || s[i] == '(')
		{
			cout << "s[i] is a number or opening parentheses\n";
			operands.push(s[i]);
		}
		else if (isOperator(s[i]))
		{
			cout << "s[i] is operator\n";
			if (!operators.empty())
			{
				while (getPrecedence(operators.top()) >= getPrecedence(s[i]))
				{
					if (!operators.empty())op = operators.top();
					operators.pop();

					d1 = operands.top() - 48;
					operands.pop();

					d2 = operands.top() - 48;
					operands.pop();

					operands.push(binarySolve(d1, d2, op));
					cout << "Pushing operation: " << d1 << " " << op << " " << d2 << endl;
				}
			}
			else
			{
				operators.push(s[i]);
			}
		}
		else if (s[i] == ')')
		{
			cout << "s[i] is a closing parenteses\n";
			while (operands.top() != ')')
			{
				if (!operators.empty())op = operators.top();
				operators.pop();

				d1 = operands.top() - 48;
				operands.pop();

				d2 = operands.top() - 48;
				operands.pop();

				operands.push(binarySolve(d1, d2, op));
				cout << "Pushing operation: " << d1 << " " << op << " " << d2 << endl;
			}
		}
		else
		{
			cout << "s[i] is in the else\n";
			while (!operators.empty())
			{
				if (!operators.empty())op = operators.top();
				operators.pop();

				d1 = operands.top() - 48;
				operands.pop();

				d2 = operands.top() - 48;
				operands.pop();

				operands.push(binarySolve(d1, d2, op));
				cout << "Pushing operation: " << d1 << " " << op << " " << d2 << endl;
			}
		}
	}
	while (!operators.empty())
	{
		op = operators.top();
		operators.pop();

		d1 = operands.top() - 48;
		operands.pop();

		d2 = operands.top() - 48;
		operands.pop();
		operands.push(binarySolve(d1, d2, op));
		cout << "Pushing operation: " << d1 << " " << op << " " << d2 << endl;
	}
	return operands.top();
}

bool Infix_Eval::isOperator(char c)
{
	return OPERATORS.find(c) != string::npos;
}

int Infix_Eval::getPrecedence(char c)
{
	return (int)PRECEDENCE[OPERATORS.find(c)] - 48;
}

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
	*/
	replaceAll(result, "++", "@");
	replaceAll(result, "--", "#");
	replaceAll(result, ">=", "$");
	replaceAll(result, "<=", "~");
	replaceAll(result, "==", "`");
	replaceAll(result, "!=", ":");
	replaceAll(result, "&&", "&");
	replaceAll(result, "||", "|");
	replaceAll(result, "-", "+-");
	return result;
}

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