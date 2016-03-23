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
		Error("The input is empty!", -1);	
	string output;
	int k = 0;
	while (input[k] == ' ' || input[k] == '\t' || input[k] == '\n')
	{
		k++;
		Pairs[k].first.push_back(input[k]);
		Pairs[k].second.push_back(k);
	}
	for (int i= k; i < input.size(); i++)
	{
		if (isdigit(input[i]))
		{
			output.push_back(input[i]);
			Pairs[k].first.push_back(input[k]);
			Pairs[i].second.push_back(i);
			continue;
		}
		if (isOperator(input[i]))
		{
			if (input[i] == '(')
				balofBracket++;
			if (input[i] == ')')
				balofBracket--;
			if (balofBracket < 0)
				Error("There is one more closing parenthesis than opening parethesis", i);
			output.push_back(input[i]);
			Pairs[k].first.push_back(input[k]);
			Pairs[i].second.push_back(i);
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
						Pairs[k].first.push_back(input[k]);
						Pairs[i].second.push_back(i);
					}
					else
						break;
				}
				if (i != (input.size()-1))
				{
					if (isdigit(input[i + 1]))
						Error("Two operands in a row", i + 1).Report();
				}
			}
		}
	}
	if (balofBracket > 0)
		Error("There are more opening parenthesis than closing parenthesis", -1);
	return output;
}


void Inputinspect::InspectOperator()
{
	for (int j = 0; j < Pairs.size(); j++)
	{
		if (j == 0)
			this->SplitFrontOperator(Pairs[j].first, Pairs[j].second);
		else if (j == Pairs.size() - 1)
			this->SplitBackOperator(Pairs[j].first, Pairs[j].second);
		else
			this->SplitOperator(Pairs[j].first, Pairs[j].second);
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


string Inputinspect::Processinput(string input)
{
	OptimizeInput(input);
	InspectOperator();
	return OptimizeInput(input);
}