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

	for (int i = k; i < input.size(); i++)
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
		if (input[i] == ' ')
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

	for (int a = 0; a < text.size(); a++)
	{
		if (text[a] == ')')
		{
			if (Indicator == 0)
			{
				continue;
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
				Error_Report("Operator cannot appear in such position", a);
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
				Error_Report("Operator cannot appear in such position", a);
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
					Indicator == 2;
				}
				else
				{
					continue;
					Indicator == 2;
				}
			}
			else
				Error_Report("Operator cannot appear in such position", a);
		}

		if (text[a] == '(')
		{
			if (Indicator == 2)
			{
				if ((a < text.size() - 1) && (text[a + 1] == '('))
					continue;
				else
				{
					Indicator = 0;
					continue;
				}
			}
			else
				Error_Report("Opening parenthesis cannot appear in such position", a);
		}
	}
}

string Inputinspect::Processinput(string input)
{
	string output=OptimizeInput(input);
	InspectOperator(output);
	return output;
}

void Inputinspect::Error_Report(const string& theMessage, int theIndex)
{
	cerr << message << " @ char " << ((index == -1) ? "N/A" : to_string(index)) << endl << endl;
	cerr << "Program exited.\n\n";

	system("pause");
	exit(-1);
}