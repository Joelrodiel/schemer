#include "Environment.h"

/**
 * Main environment loop.
 * Gets user input, splits it into tokens & executes it accordingly.
 *
 * @return An integer for control handling (Will implement later in the future...)
 */
int Environment::run()
{
    for (;;)
    {
        std::cout << "scm> "; // That iconic interpreter prompt

        std::string input;

        std::getline(std::cin, input); // Get input using getline

        // Handle custom interpreter calls
        if (input == "exit" || input == "(exit)") // Exit interpreter
        {
            std::cout << "Buh-bye!" << std::endl;
            return 0;
        }
        else if (input == "debug") // Switch debug flag on/off
        {
            DEBUG = !DEBUG;
            input = (DEBUG) ? "#t" : "#f";
        }
        else if (input == "symbols") // Print a list of all global symbols
        {
            std::cout << "GLOBAL SYMBOLS:" << std::endl;
            for (int i = 0; i < global_symbols.size(); i++)
            {
                std::cout << "I: " << i << " NAME: " << global_symbols[i].name << " VAR: " << global_symbols[i].var << std::endl;
            }
            input = "";
        }

        // If input is a call expression (because first character is '('), then treat it as a call expression.
        // Otherwise, execute the input as a single token.
        if (input.find('(') != std::string::npos)
        {
            std::vector<std::string> tokens = tokenize(input, global_symbols, DEBUG);

            if (DEBUG)
                std::cout << "FINAL ANSWER: ";

            execute(tokens, global_symbols, false, DEBUG);
        }
        else
        {
            std::vector<std::string> t; // Temporary vector to store single token
            t.push_back(input);

            if (DEBUG)
                std::cout << "FINAL ANSWER: ";

            execute(t, global_symbols, false, DEBUG);
        }
    }
}
