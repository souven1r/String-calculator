#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
enum CharType {OPERATOR, OPERAND};
struct ParserValue 
{
	CharType type;
	double operand;
	char symbol;
	ParserValue(char);
	ParserValue(double);
};
class Parser
{
public:
	bool isValidString(const char*) const; // true if its can get result of expression
	std::vector<ParserValue> execute(char*); // start of parser, returns array of operators/operands as struct
private:
	int getPriority(char); // get priority of operation
	void deleteSpaces(char*&);  // delete all spaces from string
	bool isOperator(const char) const;
	bool isNumber(const char) const;
};