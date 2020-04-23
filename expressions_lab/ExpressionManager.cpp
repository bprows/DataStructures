#include "ExpressionManager.h" 
#include <sstream>
#include <cctype>
#include <stack>
#include <string>

using namespace std;
    
    /*
	* Checks whether an expression is balanced on its parentheses
	*
	* - The given expression will have a space between every number or operator
	*
	* @return true if expression is balanced
	* @return false otherwise
	*/
// The set of opening parentheses.

const string OPEN = "([{";

// The corresponding set of closing parentheses.
const string CLOSE = ")]}";

bool is_open(char ch) {
    return OPEN.find(ch) != string::npos;
}

bool is_close(char ch) {
    return CLOSE.find(ch) != string::npos;
}

bool ExpressionManager::isBalanced(string expression)
{
    cout << "In isBalanced expression "<< expression<< endl;
    
    stack<char> s;
    bool balanced = true;
    for (string::const_iterator iter = expression.begin();
     balanced && (iter != expression.end());
     iter++) {
        char next_ch = *iter;
        if (is_open(next_ch)) {
            s.push(next_ch);
        } else if (is_close(next_ch)) {
            if (s.empty()) {
                balanced = false;
            } else {
                char top_ch = s.top();
                s.pop();
                balanced = 
                 OPEN.find(top_ch) == CLOSE.find(next_ch);
            }
        }
    }
    return balanced && s.empty();
}

	/*
	* Converts a postfix expression into an infix expression
	* and returns the infix expression.
	*
	* - The given postfix expression will have a space between every number or operator.
	* - The returned infix expression must have a space between every number or operator.
	* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix expression.
	* otherwise, return the correct infix expression as a string.
	*/
	
string ExpressionManager::postfixToInfix(string postfixExpression)
{
	    cout << "In postfixToInfix "<< postfixExpression << endl;
// Be sure the stack is empty
    while (!infix_exp.empty()) {
      infix_exp.pop();
    }

  // Process each token
  istringstream tokens(postfixExpression);
  char next_char;
  while (tokens >> next_char) {
    if (isdigit(next_char)) {
      tokens.putback(next_char);
      string value;
      tokens >> value;
      if (value.find(".") == string::npos) {
        infix_exp.push(value);  
      }
      else {
        return("invalid");
      }
    } else if (is_operator(next_char)) {
      string exp;
      string num1, num2;
      if (infix_exp.empty()) {
        return("invalid");
      } 
      num1 = infix_exp.top();
      infix_exp.pop();
      if (infix_exp.empty()) {
        return("invalid");
      } 
      else {
        num2 = infix_exp.top();
        infix_exp.pop();
        exp = "( " + num2 + " " + next_char + " " + num1 + " )";
        infix_exp.push(exp);
      }
    }
  }
  if (!infix_exp.empty()) {
    string answer = infix_exp.top();
    infix_exp.pop();
    if (infix_exp.empty()) {
      return answer;
    } else {
      //cout << "at end stack not empty";
      return("invalid");
    }
  } else {
    //cout << "at end answer not on stack";
    return("invalid");
  }
}

	/*
	* Evaluates a postfix expression returns the result as a string
	*
	* - The given postfix expression will have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix Expression
	* otherwise, return the correct evaluation as a string
	*/

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
  cout << "In postfixEvaluate "<< postfixExpression<<endl;
// Be sure the stack is empty
  while (!operand_stack.empty())
    operand_stack.pop();

  // Process each token
  istringstream tokens(postfixExpression);
  char next_char;
  while (tokens >> next_char) {
    if (isdigit(next_char)) {
      tokens.putback(next_char);
      int value;
      tokens >> value;
      operand_stack.push(value);
    } else if (is_operator(next_char)) {
      int result;
      try {
        result = eval_op(next_char);
      }
      catch(int which) {
          //cout << "not enough operands";
          return("invalid");
      }
      operand_stack.push(result);
    } else {
      //cout << "not digit or operand";
      return("invalid");
    }
  }
  if (!operand_stack.empty()) {
    string answer = to_string(operand_stack.top());
    operand_stack.pop();
    if (operand_stack.empty()) {
      return answer;
    } else {
      //cout << "at end stack not empty";
      return("invalid");
    }
  } else {
    //cout << "at end answer not on stack";
    return("invalid");
  }
}

const std::string ExpressionManager::OPERATORS = "+-*/%";

/* Evaluates the current operator.
    This function pops the two operands off the operand
    stack and applies the operator.
    @param op A character representing the operator
    @throws Syntax_Error if top is attempted on an empty stack
*/

int ExpressionManager::eval_op(char op) {
  if (operand_stack.empty()) 
    throw 1;
  int rhs = operand_stack.top();
  operand_stack.pop();
  if (rhs == 0 && op == '/') {
    throw 3;
  }
  if (operand_stack.empty())
    throw 2;
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
	/*
	* Converts an infix expression into a postfix expression
	* and returns the postfix expression
	*
	* - The given infix expression will have a space between every number or operator.
	* - The returned postfix expression must have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if infixExpression is not a valid infix expression.
	* otherwise, return the correct postfix expression as a string.
	*/
	
int get_precedence(char op) {
  int precedence;
  switch(op) {
  case '(' : precedence = 0;
             break;
  case '[' : precedence = 0;
             break;
  case '{' : precedence = 0;
             break;
  case '+' : precedence = 1;
             break;
  case '-' : precedence = 1;
             break;
  case '*' : precedence = 2;
             break;
  case '/' : precedence = 2;
             break;
  case '%' : precedence = 2;
             break;
  case ')' : precedence = 3;
             break;
  case ']' : precedence = 3;
             break;
  case '}' : precedence = 3;
             break;
  }
  return precedence;
}
	
void ExpressionManager::process_operator() {
  
  if (operator_stack.empty() || get_precedence(next_char) == 0 ) {
    operator_stack.push(next_char);
  } 
  else {
      if (get_precedence(next_char) == 3) { // find closing paren
        while (get_precedence(operator_stack.top()) != 0) { // not going to add parens to postfix
          postfix = postfix + " " + operator_stack.top();
          operator_stack.pop();
        }
        operator_stack.pop(); // might need a conditional to check it stack empty
      }
      else if ( get_precedence(next_char) > get_precedence(operator_stack.top()) || get_precedence(next_char) == 0 ) {
        operator_stack.push(next_char);
      } 
      else { //precedence is less than or equal and not opening paren 
        while ( !operator_stack.empty() && (get_precedence(next_char) <= get_precedence(operator_stack.top())) ) {
          postfix = postfix + " " + operator_stack.top();
          operator_stack.pop();
        }
        operator_stack.push(next_char);
      } 
  }
}
	

string ExpressionManager::infixToPostfix(string infixExpression) {
  postfix = "";
  // clear the stack.
  while (!operator_stack.empty()) {
    operator_stack.pop();
  }
  
  if (isBalanced(infixExpression)) {
      // Process each token
    istringstream tokens(infixExpression);
  
    while (tokens >> next_char) {
      if (isdigit(next_char)) {
        tokens.putback(next_char);
        string new_num;
        tokens >> new_num;
        if (new_num.find(".") == string::npos) {
          if (postfix == "") {
            postfix = new_num;
          }
          else {
            postfix = postfix +  " " + new_num; 
          }
        }
        else {
          return("invalid");
        }
      } 
      else if ( is_operator(next_char) || is_open(next_char) || is_close(next_char) ) {
	      process_operator();
     }
      else {
        return("invalid");
      }
    }
    // empty the stack
    while (!operator_stack.empty()) {
      if (get_precedence(operator_stack.top()) == 0) {
        return("invalid");
      }
      else {
        postfix = postfix + " " + operator_stack.top();
	      operator_stack.pop(); 
      }
    }
    if (postfixEvaluate(postfix) == "invalid") {
      return("invalid");
    }
    else {
      return postfix; 
    }
  }
  else {
    return("invalid");
  }
}
