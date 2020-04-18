#pragma once

class Calc  // base class 
{
public:
	virtual double getResult() = 0; // virtual function for implementation
	virtual ~Calc() {};
	inline double sum(double, double);
	inline double sub(double, double);
	inline double multi(double, double);
	inline double div(double, double);
	inline double exponent(double, double);
protected:
	virtual double operate(double, double, char) = 0;
};

#include "Parser.h"
class PolishEntryCalc : public Calc // polish entry calculator
{
public:
	double getResult();  // get the result of the expression
	PolishEntryCalc(std::vector<ParserValue>&);
private:
	std::vector<ParserValue> parseStr; // array of ParserValue
	bool isOperator(ParserValue) const; // true if its operator, false if  isn't
	bool isOperand(ParserValue) const;  // true if its operand, false if isn't
	double operate(double, double, char); // get the result of 2 operands
};
