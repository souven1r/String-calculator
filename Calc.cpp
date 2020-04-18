#include "Calc.h"
PolishEntryCalc::PolishEntryCalc(std::vector<ParserValue>& str) : parseStr(str)
{
}
bool PolishEntryCalc::isOperator(ParserValue value) const
{
	if (value.type == CharType::OPERATOR)
		return true;
	else
		return false;
}
bool PolishEntryCalc::isOperand(ParserValue value) const
{
	if (value.type == CharType::OPERAND)
		return true;
	else
		return false;
}
double PolishEntryCalc::operate(double r1, double r2, char operate)
{
	double result;
	switch (operate)
	{
		case '+':
			result = sum(r1, r2);
			break;
		case '-':
			result = sub(r1, r2);
			break;
		case '*':
			result = multi(r1, r2);
			break;
		case '/':
			result = div(r1, r2);
			break;
		case '^':
			result = exponent(r1, r2);
			break;
	}
	return result;
}
double PolishEntryCalc::getResult()
{
	double result = 0;
	std::vector<double> results;

	for (int i = 0; i < parseStr.size(); i++)
	{
		if (isOperand(parseStr[i]))
		{
			results.push_back(parseStr[i].operand);
		}
		else if (isOperator(parseStr[i]))
		{
			double d1 = results.back();
			results.pop_back();
			double insert = operate(results.back(), d1, parseStr[i].symbol);
			results.pop_back();
			results.push_back(insert);
		}
	}
	if (results.size() > 1) // if its invalid expression
	{
		std::cout << "Error! Misspelled expression\n";
		return 999999.9999;
	}
	result = results.back();
	return result;
}
double Calc::sum(double n1, double n2)
{
	return (n1 + n2);
}
double Calc::sub(double n1, double n2)
{
	return (n1 - n2);
}
double Calc::multi(double n1, double n2)
{
	return (n1*n2);
}
double Calc::div(double n1, double n2)
{
	if (n2 == 0)
	{
		std::cout << "Erorr! Division by zero!\n";
		return 999999.9999;
	}
	return (n1 / n2);
}
double Calc::exponent(double n1, double n2)
{
	if (!n2)
		return 1;
	else
		return n1* exponent(n1, --n2);
}