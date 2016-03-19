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
	//STUFF THAT DANIEL ADDED
	//READ THE README ON GITHUB!!!!!!!
	Infix_Eval ie;
	string user_input = "3+4*12/6";
	string post_exp = "";
	int result = 0;
	Postfix_Evaluator post_eval;


	// show input, requires spaces to tokenize properly
	cout << "your input is " << user_input << endl << endl;
	system("pause");


	


	// convert to a postfix expression
	ie.evaluate(user_input);
	post_exp = ie.returnOutput();
	cout << endl;
	cout << "your postfix expression is " << post_exp << endl << endl;
	system("pause");

	// eval the postfix
	result = post_eval.eval(post_exp);
	cout << endl;
	cout << "your result is " << result << endl << endl;
	system("pause");

}

