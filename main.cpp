/*********************************************

Name:			Joshua Neustrom, jwnf7b@mail.umkc.edu, 10227835

Course:			CS303
Program:		Project2 (Wookie Workgroup)
Team:			Team1  
Due Date:		March 12, 2016
Description:	Infix Parser, uses stacks and converts expressions to postfix for evaluation
Inputs:			User given polynomial as a string
Outputs:		Result as an int

*********************************************/

#include <iostream>
#include <string> 
#include <stack>
#include "Syntax_Error.h"
#include "Postfix_Evaluator.h"
#include "Infix_To_Postfix.h"
#include "Infix_Eval.h"

using namespace std;

int main()
{
	//Create the Infix_Eval object and a string to be used as input
	Infix_Eval ie;
	string user_input = "4<=4";

	//Shows the user's input
	cout << "Your input:\t" << user_input << endl << endl;

	//Prints out the result of the Infix_Eval::evaluate function on our given string
	cout << "Infix_Eval result:\t" << ie.evaluate(user_input) << endl;
	system("pause");
}

