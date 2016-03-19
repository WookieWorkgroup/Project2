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
    if (isdigit(next_char)) {
      tokens.putback(next_char);
      int value;
      tokens >> value;
      operand_stack.push(value);
    } else if (is_operator(next_char)) {
      int result = eval_op(next_char);
      operand_stack.push(result);
    } else {
      throw Syntax_Error("Invalid character encountered");
    }
  }
  if (!operand_stack.empty()) {
    int answer = operand_stack.top();
    operand_stack.pop();
    if (operand_stack.empty()) {
      return answer;
    } else {
      throw Syntax_Error("Stack should be empty");
    }
  } else {
    throw Syntax_Error("Stack is empty");
  }
}

/** Evaluates the current operator.
    This function pops the two operands off the operand
    stack and applies the operator.
    @param op A character representing the operator
    @throws Syntax_Error if top is attempted on an empty stack
*/
int Postfix_Evaluator::eval_op(char op) {
  if (operand_stack.empty()) 
    throw Syntax_Error("Stack is empty");
  int rhs = operand_stack.top();
  operand_stack.pop();
  if (operand_stack.empty())
    throw Syntax_Error("Stack is empty");
  int lhs = operand_stack.top();
  operand_stack.pop();
  int result = 0;
  switch(op) {
  case '+' : result = lhs + rhs;
             break;
  case '-' : result = lhs - rhs;
             break;
  case '*' : result = lhs * rhs;
             break;
  case '/' : result = lhs / rhs;
             break;
  case '%' : result = lhs % rhs;
             break;
  }
  return result;
}
