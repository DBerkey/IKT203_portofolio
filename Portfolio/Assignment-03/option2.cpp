#include "option2.h"
#include "Interpreter.h"
#include <iostream>

int RunApp()
{
	Interpreter interpreter;

	std::cout << "Interpreted Calculator (AVL-backed)\n";
	std::cout << "Enter expressions or assignments. Type 'exit' to quit.\n";

	std::string input;

	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (input == "exit")
			break;

		try
		{
			double result = interpreter.Process(input);
			std::cout << "= " << result << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
		}
	}

	return 0;
}