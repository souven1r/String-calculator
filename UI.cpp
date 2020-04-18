#include "UI.h"
UI::UI()
{
	str = new char[MAX_STR];
	calc = nullptr;
}
UI::~UI()
{
	if (calc != nullptr)
		delete calc;

	delete[] str;
}
void UI::mainMenu()
{
	int count = 0;
	char input;
	while (true)
	{
		if (count % 5 == 0 && count != 0)
		{
			std::cout << "Are you want to exit? (y/n): ";
			std::cin >> input;
			std::cin.ignore();
			if (input == 'y')
			{
				std::cout << "String calc was closed!";
				break;
			}
			else if (input == 'n')
				count++;
			else
				continue;
		}
		std::cout << "Enter the expression: ";
		gets_s(str, MAX_STR);
		if (!parser.isValidString(str))
		{
			std::cout << "Incorrect expression, try again!\n";
			continue;
		}
		parseResult = parser.execute(str); //get perser string 
		calc = new PolishEntryCalc(parseResult); // 
		std::cout << "Result: " << calc->getResult() << std::endl; // print result
		count++;
	}
}