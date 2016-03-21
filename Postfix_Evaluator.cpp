/** Implementation of the postfix_evaluator. */

#include "Postfix_Evaluator.h"
#include <sstream>
#include <cctype>
using std::stack;
using std::string;
using std::istringstream;
using std::isdigit;

const std::string Postfix_Evaluator::OPERATORS = "+-*/%";

/** Evaluates a postfix expression.
    @param expression The expression to be evaluated
    @return The value of the expression
    @throws Syntax_Error if a syntax error is detected
*/
int Postfix_Evaluator::eval(const std::string& expression) {
  
	// Be sure the stack is empty
	while (!operand_stack.empty())
		operand_stack.pop();

	// Process each token
	istringstream tokens(expression);
	char next_char;
	while (tokens >> next_char) {
		
		// Digits
		if (isdigit(next_char)) {
			tokens.putback(next_char);
			int value;
			tokens >> value;
			operand_stack.push(value);
		} 
		
		// Operators
		else if (is_operator(next_char)) {
			int result = eval_op(next_char);
			operand_stack.push(result);
		} 
		
		// Error, not supposed to be anything else
		else 
		{
		  throw Syntax_Error("Invalid character encountered");
		}
	}
	// Get answer  
	if (!operand_stack.empty()) 
	{
		int answer = operand_stack.top();
		operand_stack.pop();
		
		// Are we done
		if (operand_stack.empty()) 
		{
			  return answer;
		} 

		// Still something left after answer, error
		else 
		{
		  throw Syntax_Error("Stack should be empty");
		}
	  } 
	
	// No answer
	else 
	{
		throw Syntax_Error("Stack is empty");
	}
	}

/** Evaluates the current operator.
    This function pops the two operands off the operand
    stack and applies the operator.
    @param op A character representing the operator
    @throws Syntax_Error if top is attempted on an empty stack
*/

int Postfix_Evaluator::eval_op(char op) 
{
	// Check for empty stack
	if (operand_stack.empty()) 
		throw Syntax_Error("Stack is empty");
	
	// Unary operations
	int rhs = operand_stack.top();
		operand_stack.pop();
	switch (op)
	{
	case '!':
		return !rhs;
	case '@':
		return ++rhs;
	case '#':
		return --rhs;
	case '-':
		return -rhs;
	}
 
	// Check if empty
	if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");
 
	// Binary operations
	int lhs = operand_stack.top();
	operand_stack.pop();
  
	  int result = 0;
  
	  switch (op)
	  {
	  case '^':
		  return pow(lhs, rhs);
	  case '*':
		  return rhs*lhs;
	  case '/':
		  return lhs / rhs;
	  case '%':
		  return (int)lhs % (int)rhs;
	  case '+':
		  return lhs + rhs;
	  case '>':
		  return lhs > rhs;
	  case '$':
		  return lhs >= rhs;
	  case '<':
		  return lhs < rhs;
	  case '~':
		  return lhs <= rhs;
	  case '`':
		  return lhs == rhs;
	  case ':':
		  return lhs != rhs;
	  case '&':
		  return lhs && rhs;
	  case '|':
		  return lhs || rhs;
	  }

	  throw Syntax_Error("No calculation");
}


