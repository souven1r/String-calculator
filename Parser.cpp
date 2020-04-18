#include "Parser.h"
ParserValue::ParserValue(char ch)
{
	symbol = ch;
	type = OPERATOR;
}
ParserValue::ParserValue(double n)
{
	operand = n;
	type = OPERAND;
}
bool Parser::isValidString(const char* str) const
{
	int count = 0;
	bool result = true;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '(')
			count++;
		else if (str[i] == ')')
			count--;

		if (count < 0) // if bracket closed before it was open
		{
			result = false;
			break;
		}
		if (!isOperator(str[i]) && !isNumber(str[i]) && str[i] != '.' && str[i] != ' ')
		{
			result = false;
			break;
		}
	}
	if (count > 0) // if bracket is not closed
		result = false;
	return result;
}
void Parser::deleteSpaces(char*& str) 
{
	int size = strlen(str);
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == ' ')
		{
			for (int j = i; j < size-1; j++)
			{
				str[j] = str[j + 1];
			}
			count++;
		}
	}
	str[size - count] = '\0';
}
bool Parser::isOperator(char ch) const // all operators
{
	if (ch == '*' || ch == '^' || ch == '/'
		|| ch == '+' || ch == '-' || ch == '(' || ch == ')')
		return true;
	return false;
}
bool Parser::isNumber(char ch) const // all operands
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
int Parser::getPriority(char ch) // prioirity of operator
{
	if (ch == '(' || ch == ')')
		return 0;
	else if (ch == '+' || ch == '-') // 1 lvl
		return 1;
	else if (ch == '*' || ch == '/') // 2 level
		return 2;
	else if (ch == '^') // 3 level
		return 3;
	else 
		return -1;
}
std::vector<ParserValue> Parser::execute(char* str)
{
	deleteSpaces(str); // deleting all spaces
	std::stack<ParserValue> operators; // stack of operators
	std::vector<ParserValue> operands; // vector of operands
	int size = strlen(str); // size of string
	for (int i = 0; i < size; i++)
	{
		if (isNumber(str[i]))
		{
			if ((str[i - 1] == '-' && i - 1 == 0 && i > 0) // if its negative number
				|| (str[i - 1] == '-' && isOperator(str[i - 2]) && i - 2 >= 0))
			{
				i--;
			}
			int startNumber = i;
			char* numberStr = new char[20];
			for (int k = 0; i < size && k < 20; i++,k++) // get total number 
			{
				if (isNumber(str[i]) || i == startNumber || str[i] == '.')
				{
					numberStr[k] = str[i];
				}
				else
				{
					break;
				}
			}
			ParserValue value(std::atof(numberStr)); // add to operands
			operands.push_back(value);
			delete[] numberStr;
		}
		if (isOperator(str[i]))
		{
			if ((str[i] == '-' && i == 0 && isNumber(str[i+1]))
				|| (str[i] == '-' && isOperator(str[i-1]) && isNumber(str[i+1])))
			{
				continue;
			}
			if (str[i] == '(' && isNumber(str[i - 1]) && i - 1 > 0) // open bracket
			{
				ParserValue value('*'); // add operation of multiply
				operators.push(value); // add to operators
			}
			if (str[i] == ')') // closing bracket
			{
				for (int j = operators.size() - 1; j >= 0; j--)
				{
					if (operators.top().symbol == '(') // if last operator is bracket
					{
						operators.pop(); // remove bracket from operators
						break;
					}
					else
					{
						operands.push_back(operators.top()); // add operator to operands
						operators.pop(); // delete this operator from operators
					}
				}
				continue;
			}
			if (!operators.empty()) // if operators is not empty
			{
				if (getPriority(operators.top().symbol) >= getPriority(str[i]) && getPriority(str[i]) > 0)
				{
					operands.push_back(operators.top());
					operators.pop();
				}
			}
			ParserValue value(((char)str[i]));
			operators.push(value);
		}
	}
	for (int i = operators.size(); i >= 0; i--) // transfer all operators to vector of operands
	{
		if (operators.empty())
			break;
		operands.push_back(operators.top());
		operators.pop();
	}
	return operands;
}