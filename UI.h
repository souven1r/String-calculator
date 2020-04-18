#pragma once
#include "Calc.h"
#include "Parser.h"
#include <iostream>
const int MAX_STR = 128;
class UI
{
public:
	UI();
	~UI();
	void mainMenu(); // shows main menu
private:
	char* str;
	Parser parser;
	Calc* calc;
	std::vector<ParserValue> parseResult;
};
