#include "Inputinspect.h"
#include <cctype>


/* Implementation of class Inputinspect */
bool Inputinspect::isOperator(char ch) const
{
	return (ch == '!') || (ch == '+') || (ch == '-') || (ch == '^') || (ch == '*') || (ch == '/') || (ch == '%') || (ch == '>') || (ch == '<') || (ch == '=') || (ch == '&') || (ch == '|') || (ch == '(') || (ch == ')');
}

string Inputinspect::ReadInput (string input, string output, vector<int> indices, string operators)
{
	if (input.empty())
		 Error("The input is empty!", -1);
	int i = 0;
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		i++;
	for (i; i <= input.size; i++)
	{
		if (isdigit(input[i]))
		{
			output.push_back(input[i]);  
			continue;
		}
		if (isOperator(input[i]))
		{
			output.push_back(input[i]);
			indices.push_back(i);
			operators.push_back(input[i]);
			continue;
		}
		if (input[i] == ' ' || input[i] == '\t')
		{
			int numofspace;
			while (i <= input.size)
			{
				
				if (input[i + 1] == ' ' || input[i + 1] == '\t')
					i++;

				if (isdigit(input[i - 1]) && isdigit(input[i + 1]))
				Error("Two operands in a row", i+1).Report();
			continue;

			}
			
		}



	}



}


void Inputinspect::SplitOperator(const string& text, const vector<int>& indices)
{
	if (text.empty())
		return;

	int Indicator = 0; //0 means "in brac_back space", 1 "in binoper", 2 "in brac_front space".

	for (int a = 0; a < text.size(); a++)
	{
		if (text[a] == ')')
		{
			if (Indicator == 0)
			{
				brac_back += text[a];
				continue;
			}
			else
				Error("There shouldn't be closing parenthesis in such position", indices[a]).Report();
		}

		if (Indicator == 0) Indicator = 1;

		if ((text[a] == '^') || (text[a] == '*') || (text[a] == '/') || (text[a] == '%'))
		{
			if (Indicator == 1 && binoper.empty())
			{
				binoper += text[a];
				Indicator = 2;
				continue;
			}
			else
				Error("Operator cannot appear in such position", indices[a]).Report();
		}

		if ((text[a] == '=') || (text[a] == '&') || (text[a] == '|'))
		{
			if ((Indicator == 1) && binoper.empty() && (a < text.size() - 1))
			{
				if (text[a + 1] == text[a])
				{
					binoper += text[a];
					a++;
					binoper += text[a];
					Indicator = 2;
					continue;
				}
				else
					Error("Incomplete operator", indices[a]).Report();
			}
			else
				Error("Operator cannot appear in such position", indices[a]).Report();
		}

		if (text[a] == '!')
		{
			if (Indicator == 2)
			{
				brac_front += text[a];
				continue;
			}
			else if ((Indicator == 1) && (binoper.empty()) && (a < text.size() - 1))
			{
				if (text[a + 1] == '=')
				{
					binoper += text[a];
					a++;
					binoper += text[a];
					Indicator = 2;
					continue;
				}
				else
					Error("Incomplete operator", indices[a]).Report();
			}
			else
				Error("Operator cannot appear in such position", indices[a]).Report();
		}

		if ((text[a] == '+') || (text[a] == '-'))
		{
			if ((Indicator == 1) && binoper.empty())
			{
				binoper += text[a];
				Indicator = 2;
				continue;
			}
			else if (Indicator == 2)
			{
				if ((a < text.size() - 1) && (text[a + 1] == text[a]))
				{
					brac_front += text[a];
					a++;
					brac_front += text[a];
					continue;
				}
				else
				{
					if (!brac_front.empty() && brac_front[brac_front.size() - 1] == '(')
					{
						brac_front += text[a];
						continue;
					}
					else
						Error("Two binary operators in a row", indices[a]).Report();
				}
			}
			else
				Error("Operator cannot appear in such position", indices[a]).Report();
		}

		if ((text[a] == '>') || (text[a] == '<'))
		{
			if ((Indicator == 1) && binoper.empty())
			{
				if ((a < text.size() - 1) && (text[a + 1] == '='))
				{
					binoper += text[a];
					a++;
					binoper += text[a];
				}
				else
					binoper += text[a];

				continue;
			}
			else
				Error("Operator cannot appear in such position", indices[a]).Report();
		}

		if (text[a] == '(')
		{
			if (Indicator == 2)
			{
				brac_front += text[a];
				continue;
			}
			else
				Error("Opening parenthesis cannot appear in such position", indices[a]).Report();
		}
	}
}

void Inputinspect::SplitFrontOperator(const string& text, const vector<int>& indices)
{
	if (text.empty())
		return;

	for (int i = 0; i < indices.size(); i++)
	{
		if ((text[i] == '|') || (text[i] == '&') || (text[i] == '=') || (text[i] == '<') || (text[i] == '>') || (text[i] == '%') || (text[i] == '/') || (text[i] == '*') || (text[i] == '^'))
			Error("No operand before a binary operator", indices[i]).Report();

		if (text[i] == ')')
			Error("Expression cannot start with a closing parenthesis", indices[i]).Report();

		if ((text[i] == '+') || (text[i] == '-'))
		{
			if (i < text.size() - 1)
			{
				if (text[i + 1] == text[i])
				{
					brac_front += text[i];
					i++;
					brac_front += text[i];
					continue;
				}
				else
				{
					if (brac_front.empty())
					{
						brac_front += text[i];
						continue;
					}
					else
					{
						if (brac_front[brac_front.size() - 1] == '(')
						{
							brac_front += text[i];
							continue;
						}
						else
							Error("Operator cannot appear in such position", indices[i]).Report();
					}
				}
			}
			else
			{
				if (brac_front.empty())
				{
					brac_front += text[i];
					continue;
				}
				else
				{
					if (brac_front[brac_front.size() - 1] == '(')
					{
						brac_front += text[i];
						continue;
					}
					else
						Error("Operator cannot appear in such position", indices[i]).Report();
				}
			}
		}

		if ((text[i] == '!') || (text[i] == '('))
		{
			brac_front += text[i];
			continue;
		}
	}
}

void Inputinspect::SplitBackOperator(const string& text, const vector<int>& indices)
{
	if (text.empty())
		return;

	for (int i = 0; i < indices.size(); i++)
	{
		if (text[i] == ')')
		{
			brac_back += text[i];
			continue;
		}
		else
			Error("operator cannot appear in such position", indices[i]).Report();
	}
}