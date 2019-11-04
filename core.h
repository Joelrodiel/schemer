#ifndef __CORE__
#define __CORE__

#include "helpers.h"

/**
 * Function that gets tokens, parameters & symbols, & returns an output.
 *
 * @param tokens Vector of string tokens of Scheme code.
 * @param left Left side parameter.
 * @param right Right side parameter.
 * @param symbols Vector of Symbol objects.
 * @return String with instruction output.
 */
inline static std::string run_instruction(std::vector<std::string>& tokens, std::string left, std::string right, std::vector<Symbol>& symbols)
{
    std::string output;

    // Okay so this might not be the best way to do this... But it works.
    if (tokens[0] == "+")
        output = std::to_string(stoi(left) + stoi(right));
    else if (tokens[0] == "-")
        output = std::to_string(stoi(left) - stoi(right));
    else if (tokens[0] == "*")
        output = std::to_string(stoi(left) * stoi(right));
    else if (tokens[0] == "=")
        output = (left == right) ? "#t" : "#f";
    else if (tokens[0] == "<")
        output = (left < right) ? "#t" : "#f";
    else if (tokens[0] == ">")
        output = (left > right) ? "#t" : "#f";
    else if (tokens[0] == "if")
        output = (left != "#f") ? std::to_string(stoi(right)) : (tokens.size() >= 4) ? tokens[3] : "";
    else if (tokens[0] == "define")
    {
        // If left (symbol name) is not a string, throw an error!
        if (!isSymbol(left))
        {
            std::cout << "Error:\n\tNon-symbol: " << left << std::endl;
            return "Error";
        }

        int symbolIndex = findSymbol(tokens[1], symbols); // Check if symbol exists.

        // If symbol doesn't exist, create a new one.
        // If symbol exists, then overwrite it.
        if (symbolIndex == -1)
        {
            Symbol *s = new Symbol(tokens[1], tokens[2]);
            symbols.push_back(*s);
            output = s->name;
        }
        else
        {
            symbols[symbolIndex].var = tokens[2];
            output = tokens[1];
        }
    }
    else if (tokens[0] == "eq?")
        output = (left == right) ? "#t" : "#f";
    else if (tokens[0] == "print")
        output = left;
    else
    {
        // Check if its an existing symbol, and output its value
        for (int i = 0; i < symbols.size(); i++)
        {
            if (symbols[i].name == tokens[0])
                output = symbols[i].var;
        }

        // If it's empty, just return the first token
        if (output.empty())
            output = tokens[0];
    }

    return output;
}

#endif
