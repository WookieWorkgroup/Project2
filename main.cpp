/*********************************************

Name:			Joshua Neustrom, jwnf7b@mail.umkc.edu, 10227835
				Daniel Mitchel
				Chen Wang, cwrp3@mail.umkc.edu, 16208411

Course:			CS303
Program:		Project2 (Wookie Workgroup)
Team:			Team1  
Due Date:		March 25, 2016
Description:	Infix Parser, uses stacks and converts expressions to postfix for evaluation
Inputs:			User given polynomial as a string
Outputs:		Result as an int

*********************************************/

#include <iostream>
#include <string> 
#include <stack>
#include "Syntax_Error.h"
#include "Infix_Eval.h"
#include "Inputinspect.h"

using namespace std;

// Functions for the menu
void displayMenu(Infix_Eval& ie, string& user_input, int& result, bool& exp_entered);

int main()
{
	// Initial variables
	Infix_Eval ie;
	string user_input = "";
	int result = 0;
	bool exp_entered = false;

	// Call the menu for entering calculations
	while (true)
	{
		displayMenu(ie, user_input, result, exp_entered);
	}
}


// A glorious menu and user interface
void displayMenu(Infix_Eval& ie, string& user_input, int& result, bool& exp_entered)
{
	
	
	
	// My choices
	int userSelection(-1);
	cout << "Please select one: \n\n";
	cout << "1:\tEnter an Infix Expression such as (3+4)/20 to calculate the result\n";
	cout << "2:\tDisplay Expression Entered One\n";
	cout << "3:\tDisplay Result\n";
	cout << "4:\tClear entries\n";
	cout << "5:\tExit\n";
	

	// Filter input so program accepts single digits only
	while (!(cin >> userSelection))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// Warn the user about an improper input
		cout << endl << "Single digits only" << endl;
		cout << "Make another selection: ";
	}

	// What happens when making a choice
	switch (userSelection)
	{
		// Give me an expression
	case 1:
		cout << endl << endl;
		cout << "Enter the Infix Expression: ";
		cin.ignore();
		getline(cin, user_input);

		// See if the polynomial is poperly entered
		try{
			Inputinspect Ins;
			Ins.Processinput(user_input);
			ie.clearData();
			result = ie.evaluate(user_input);
			cout << "Expression successfully entered\n";
			exp_entered = true;
			cout << "Result is: " << result << endl;
		}

		// Bad input, try again
		catch (const std::exception &e)
		{
			std::cout << std::endl << std::endl;
			std::cout << e.what() << std::endl;
		}

		cout << endl << endl;
		break;

	// Show the last expression entered
	case 2:
		cout << endl << endl;
		if (!exp_entered) cout << "Expression is empty, please enter a value before you add\n";
		else
		{
			cout << "You entered: " << user_input << endl;
		}
		break;

		// Show the last result
	case 3:
		cout << endl << endl;
		if (!exp_entered)
		{
			cout << "No expression found, please enter an Infix Expression\n";
		}
		else
		{
			cout << "Result of the last calculation was " << result << endl;
		}
		break;


		// Reset all input and results
	case 4:
		result = 0;
		exp_entered = false;
		user_input = "";
		cout << endl << endl;
		cout << "Entries cleared\n\n";
		break;


		// Bah bye
	case 5:
		exit(0);

		// Bad choice, try that again
	default:
		cout << endl << endl;
		cout << "Invalid menu option" << endl;
		break;
	}
}


