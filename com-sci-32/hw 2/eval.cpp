#include <string>
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

bool validString(string& infix);
int getPrecedence(char ch);

int evaluate(string infix, string& postfix, bool& result)
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero. If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
{
	// INFIX TO POSTFIX CONVERSION STEP
	if (!validString(infix))
	{
		return 1;
	}

	postfix = "";
	stack<char> operatorStack;

	for (size_t i = 0; i < infix.size(); i++)
	{
		char ch = infix.at(i);

		switch (ch)
		{
		case 'T':
		case 'F':
			postfix += ch;
			break;
		case '(':
			operatorStack.push(ch);
			break;
		case ')':
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop();
			break;
		case '!':
		case '&':
		case '^':
			while (!operatorStack.empty() && operatorStack.top() != '(' &&
				getPrecedence(ch) <= getPrecedence(operatorStack.top()))
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(ch);
			break;
		default:
			return false;
		}
	}

	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	// EVALUATION OF THE POSTFIX EXPRESSION
	stack<bool> operandStack;

	for (size_t i = 0; i < postfix.size(); i++)
	{
		char ch = postfix.at(i);

		if (ch == 'T')
		{
			operandStack.push(true);
		}
		if (ch == 'F')
		{
			operandStack.push(false);
		}
		if (ch == '&' || ch == '^')
		{
			bool operand2 = operandStack.top();
			operandStack.pop();
			bool operand1 = operandStack.top();
			operandStack.pop();

			switch (ch)
			{
			case '&':
				operandStack.push(operand1 && operand2);
				break;
			case '^':
				operandStack.push(operand1 ^ operand2);
				break;
			}
		}
		if (ch == '!')
		{
			bool operand = operandStack.top();
			operandStack.pop();
			operandStack.push(!operand);
		}
	}

	result = operandStack.top();
	return 0;
}

bool validString(string& infix)
{
	string temp;
	for (size_t i = 0; i < infix.size(); i++)
	{
		char ch = infix.at(i);

		if (ch != ' ')
		{
			temp += ch;
		}
	}
	infix = temp;

	if (infix == "")
	{
		return false;
	}

	if (infix.at(0) == '&' || infix.at(0) == '^' || infix.at(0) == ')')
	{
		return false;
	}
	if (infix.at(infix.size() - 1) == '!' || infix.at(infix.size() - 1) == '&' ||
		infix.at(infix.size() - 1) == '^' || infix.at(infix.size() - 1) == '(')
	{
		return false;
	}

	int openP = 0;
	int closeP = 0;
	for (size_t i = 0; i < infix.size(); i++)
	{
		char ch = infix.at(i);
		if (ch == '(')
		{
			openP++;
		}
		if (ch == ')')
		{
			closeP++;
		}
	}
	if (openP != closeP)
	{
		return false;
	}

	for (size_t i = 0; i < infix.size(); i++)
	{
		char ch = infix.at(i);

		if (ch != 'T' && ch != 'F' && ch != '(' && ch != ')' && ch != '!' && ch != '&' && ch != '^')
		{
			return false;
		}
		if (ch == 'T' || ch == 'F')
		{
			if (i + 1 < infix.size())
			{
				if (infix.at(i + 1) == 'T' || infix.at(i + 1) == 'F' || infix.at(i + 1) == '(' || infix.at(i + 1) == '!')
				{
					return false;
				}
			}
		}

		if (ch == '(' || ch == '!')
		{
			if (i + 1 < infix.size())
			{
				if (infix.at(i + 1) == ')' || infix.at(i + 1) == '&' || infix.at(i + 1) == '^')
				{
					return false;
				}
			}
		}
		if (ch == ')')
		{
			if (i + 1 < infix.size())
			{
				if (infix.at(i + 1) == 'T' || infix.at(i + 1) == 'F' || infix.at(i + 1) == '(' || infix.at(i + 1) == '!')
				{
					return false;
				}
			}
		}
		if (ch == '&' || ch == '^')
		{
			if (i + 1 < infix.size())
			{
				if (infix.at(i + 1) == '&' || infix.at(i + 1) == '^' || infix.at(i + 1) == ')')
				{
					return false;
				}
			}
		}
	}

	return true;
}

int getPrecedence(char ch)
{
	switch (ch)
	{
	case '!':
		return 3;
	case '&':
		return 2;
	case '^':
		return 1;
	default:
		exit(1);
	}
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("T^(F)", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T ^ !F", pf, answer) == 0 && pf == "TF!^" && !answer);
	assert(evaluate("!(T&F)", pf, answer) == 0 && pf == "TF&!" && answer);
	assert(evaluate("!T&F", pf, answer) == 0 && pf == "T!F&" && !answer);
	assert(evaluate("T^F&F", pf, answer) == 0 && pf == "TFF&^" && answer);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer);

	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;
}