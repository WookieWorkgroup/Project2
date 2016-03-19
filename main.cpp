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

using namespace std;

int main()
{
	// Variables for user input, converted postfix expression, final result, conversions
	string user_input = "( 3 + 2 ) * 5 - 4";
	string post_exp = "";
	int result = 0;
	Infix_To_Postfix in_to_post;
	Postfix_Evaluator post_eval;

	// Show input, requires spaces to tokenize properly
	cout << "Your input is " << user_input << endl << endl;
	system("pause");

	// Convert to a postfix expression
 	post_exp = in_to_post.convert(user_input);
	cout << endl;
	cout << "Your postfix expression is " << post_exp << endl << endl;
	system("pause");

	// Eval the postfix
	result = post_eval.eval(post_exp);
	cout << endl;
	cout << "Your result is " << result << endl << endl;
	system("pause");

}

