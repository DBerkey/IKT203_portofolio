#include "option2.h"
#include "Interpreter.h"
#include <iostream>
#include <string>

int RunApp()
{


    Interpreter interpreter;

    std::cout << "Interpreted Calculator (Option 2)\n";
    std::cout << "---------------------------------\n";
    std::cout << "How to use this calculator:\n";
    std::cout << "You may enter standard expressions using:\n";
    std::cout << "    +   -   *   /   ^   (   )\n";
    std::cout << "Supported functions:\n";
    std::cout << "    ln(x)   log(x)   exp(x)\n";
    std::cout << "To store a variable, use assignment:\n";
    std::cout << "    x = 10\n";
    std::cout << "    y = (x + 5) * 3^2\n";
    std::cout << "\n";
    std::cout << "To exit the program:  exit\n";
    std::cout << "---------------------------------\n";

    while (true)
    {
        std::cout << "> ";

        std::string input;

        if (!std::getline(std::cin, input))
        {
            std::cout << "\nProgram terminated automatically.\n";
            break;
        }

        if (input.find_first_not_of(" \t") == std::string::npos)
            continue;

        if (input == "exit")
            break;

        try
        {
            double result = interpreter.Process(input);

            if (input.find('=') != std::string::npos)
            {
                size_t pos = input.find('=');
                std::string var = input.substr(0, pos);

                size_t s = var.find_first_not_of(" \t");
                size_t e = var.find_last_not_of(" \t");
                var = var.substr(s, e - s + 1);

                std::cout << "Stored: " << var << " = " << result << "\n";
            }
            else
            {
                std::cout << "= " << result << "\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}