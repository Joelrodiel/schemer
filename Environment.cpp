#include "Environment.h"

int Environment::run()
{
    for (;;)
    {
        std::cout << "scm> ";

        std::string input;

        std::getline(std::cin, input);

        if (input == "exit" || input == "(exit)")
        {
            std::cout << "Buh-bye!" << std::endl;
            return 0;
        }
        else if (input == "debug")
        {
            DEBUG = !DEBUG;
            input = (DEBUG) ? "#t" : "#f";
        }
        else if (input == "symbols")
        {
            std::cout << "GLOBAL SYMBOLS:" << std::endl;
            for (int i = 0; i < global_symbols.size(); i++)
            {
                std::cout << "I: " << i << " NAME: " << global_symbols[i].name << " VAR: " << global_symbols[i].var << std::endl;
            }
            input = "";
        }

        if (input.find('(') != std::string::npos)
        {
            std::vector<std::string> tokens = tokenize(input, global_symbols, DEBUG);

            if (DEBUG)
                std::cout << "FINAL ANSWER: ";

            execute(tokens, global_symbols, false, DEBUG);
        }
        else
        {
            std::vector<std::string> t;
            t.push_back(input);

            if (DEBUG)
                std::cout << "FINAL ANSWER: ";
            execute(t, global_symbols, false, DEBUG);
        }
    }
}
