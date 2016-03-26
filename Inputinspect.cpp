#include "Inputinspect.h"
#include <cctype>


/* Implementation of class Inputinspect */
bool Inputinspect::isOperator(char ch) const
{
	return (ch == '!') || (ch == '+') || (ch == '-') || (ch == '^') || (ch == '*') || (ch == '/') || (ch == '%') || (ch == '>') || (ch == '<') || (ch == '=') || (ch == '&') || (ch == '|') || (ch == '(') || (ch == ')');
}

string Inputinspect::OptimizeInput(string input)
{
	int balofBracket = 0;
	if (input.empty())
		Error_Report("The input is empty!", -1);
	string output;
	int k = 0;
	while (input[k] == ' ' || input[k] == '\t' || input[k] == '\n')
	{
		k++;
	}
	if(k==input.size())
		Error_Report("The input is empty!", -1);

	for (unsigned int i = k; i < input.size(); i++)
	{
		if (isdigit(input[i]))
		{
			output.push_back(input[i]);
			continue;
		}
		if (isOperator(input[i]))
		{
			if (input[i] == '(')
				balofBracket++;
			if (input[i] == ')')
				balofBracket--;
			if (balofBracket < 0)
				Error_Report("There is one more closing parenthesis than opening parethesis", i);
			output.push_back(input[i]);
			continue;
		}
		if (input[i] == ' '|| input[k] == '\t')
		{
			if (isdigit(input[i - 1]))
			{
				while (i < input.size())
				{
					if (input[i + 1] == ' ')
					{
						i++;
					}
					else
						break;
				}
				if (i != (input.size() - 1))
				{
					if (isdigit(input[i + 1]))
						Error_Report("Two operands in a row", i + 1);
				}
			}
		}
		if (!isdigit(input[i]) && !isOperator(input[i])&&(input[i]!=' ')&&(input[i] != '\t'))
			Error_Report("Invail symbol", i);
	}
	if (balofBracket > 0)
		Error_Report("There are more opening parenthesis than closing parenthesis", -1);
	return output;
}

void Inputinspect::InspectOperator(string text)
{
	if (text.empty())
		return;

	int Indicator = 2;
	if (isdigit(text[0]))
		Indicator = 1;
	//0 means closing bracket, 1 means binory operator, 2 means opening bracket and unary operator.

	for (unsigned int a = 0; a < text.size(); a++)
	{

		if (isdigit(text[a]))
		{
			if ((a + 1) < text.size())
			{
				if ((text[a + 1] == '+') || (text[a + 1] == '-') || (text[a + 1] == '*') || (text[a + 1] == '/') || (text[a + 1] == '%') || (text[a + 1] == '<') || (text[a + 1] == '>') || (text[a + 1] == '=') || (text[a + 1] == '|') || (text[a + 1] == '&') || (text[a + 1] == '^'))
				{
					Indicator = 1;
				}
				else if ((a + 2) < text.size() && (text[a + 1] == '!') && (text[a + 2] == '='))
					Indicator = 1;
				else
					Indicator = 0;
			}
			continue;
		}

		if (text[a] == ')')
		{
			
			if (Indicator == 0)
			{
				if ((a + 1) < text.size())
				{
					if (isOperator(text[a + 1]))
						continue;
					else
						Error_Report("The digit can't follow with the closing parethesis", a + 1);
				}
			}
			else
				Error_Report("There shouldn't be closing parenthesis in such position", a);
		}

		if (Indicator == 0) Indicator = 1;

		if ((text[a] == '^') || (text[a] == '*') || (text[a] == '/') || (text[a] == '%'))
		{
			if (Indicator == 1)
			{
				Indicator = 2;
				continue;
			}
			else
				Error_Report("Binary operator cannot appear in such position", a);
		}

		if ((text[a] == '=') || (text[a] == '&') || (text[a] == '|'))
		{
			if ((Indicator == 1) && (a < text.size() - 1))
			{
				if (text[a + 1] == text[a])
				{
					a++;
					Indicator = 2;
					continue;
				}
				else
					Error_Report("Incomplete operator", a);
			}
			else
				Error_Report("Binary operator cannot appear in such position", a);
		}

		if (text[a] == '!')
		{
			if (Indicator == 2)
			{
				continue;
			}
			else if ((Indicator == 1) && (a < text.size() - 1))
			{
				if (text[a + 1] == '=')
				{
					a++;
					Indicator = 2;
					continue;
				}
				else
					Error_Report("Incomplete operator", a);
			}
			else
				Error_Report("Operator cannot appear in such position", a);
		}

		if ((text[a] == '+') || (text[a] == '-'))
		{
			if (Indicator == 1)
			{
				Indicator = 2;
				continue;
			}
			else if (Indicator == 2)
			{
				if ((a < text.size() - 1) && (text[a + 1] == text[a]))
				{
					a++;
					continue;
				}
				else if (a == 0 && isdigit(text[a + 1]))
				{
					Indicator = 1;
					continue;
				}
				else
				{
					if ((a < text.size() - 1) && (text[a + 1] == '('))
					{
						a++;
						continue;
					}
					else
						Error_Report("Two binary operators in a row", a);
				}
			}
			else
				Error_Report("Operator cannot appear in such position", a);
		}

		if ((text[a] == '>') || (text[a] == '<'))
		{
			if (Indicator == 1)
			{
				if ((a < text.size() - 1) && (text[a + 1] == '='))
				{
					a++;
					continue;
					Indicator = 2;
				}
				else
				{
					continue;
					Indicator = 2;
				}
			}
			else
				Error_Report("Binary operator cannot appear in such position", a);
		}

		if (text[a] == '(')
		{
			if (Indicator == 2)
			{
				if ((a < text.size() - 1) && (isdigit(text[a + 1])))
				{
					Indicator = 1;
					continue;
				}
				else
				{
					continue;
				}
			}
			else
				Error_Report("Opening parenthesis cannot appear in such position", a);
		}
	}
	if (text[text.size() - 1] != ')' && !isdigit(text[text.size() - 1]))
		Error_Report("Lose the last operand at the end.", -1);
}

string Inputinspect::Processinput(string input)
{
	string output=OptimizeInput(input);
	InspectOperator(output);
	return output;
}

void Inputinspect::Error_Report(const string& theMessage, int theIndex)
{
	std::string msg;
		
	if (theIndex != -1)
		msg = theMessage + " @ char " + to_string(theIndex);
	else
		msg = theMessage;

	throw std::exception(msg.c_str());

}