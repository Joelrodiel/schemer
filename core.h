#ifndef __CORE__
#define __CORE__

#include "helpers.h"

/**
 * Function that gets tokens, parameters & symbols, & returns an output.
 *
 * @param tokens Vector of string tokens of Scheme code.
 * @param left Left side parameter.
 * @param right Right side parameter.
 * @param symbols Vector of Symbol object pointers.
 * @return String with instruction output.
 */
inline static std::string run_instruction(std::vector<std::string>& tokens, std::string left, std::string right, std::vector<Symbol*>& symbols)
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
        // If left (symbol.m_name) is not a string, throw an error!
        if (!isSymbol(left))
        {
            std::cout << "Error:\n\tNon-symbol: " << left << std::endl;
            return "Error";
        }


        if (left.find('(') == std::string::npos)
        {
        
            int symbolIndex = findSymbol(left, symbols); // Check if symbol exists.

            Symbol *s = new Symbol(left, right);
            
            // If symbol doesn't exist, create a new one.
            // If symbol exists, then overwrite it.
            if (symbolIndex == -1)
            {
                symbols.push_back(s);
                output = s->m_name;
            }
            else
            {
                if (symbols[symbolIndex]->m_type != "symbol")
                {
                    symbols[symbolIndex] = s;
                }
                else
                {
                    symbols[symbolIndex]->m_var = right;
                    delete s;
                }
                
                output = left;
            }
        }
        else
        {

            Function *f = new Function(left, right);
            
            int symbolIndex = findSymbol(f->m_name, symbols); // Check if symbol exists.

            // If function doesn't exist, create a new one.
            // If function exists, then overwrite it.
            if (symbolIndex == -1)
            {
                symbols.push_back(f);
                output = f->m_name;
            }
            else
            {
                output = f->m_name;

                if (symbols[symbolIndex]->m_type != "function") {
                    symbols[symbolIndex] = f;
                }
                else
                {
                    symbols[symbolIndex]->m_var = right;
                    output = f->m_name;
                    delete f;
                }
            }
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
            if (symbols[i]->m_name == tokens[0])
                output = symbols[i]->m_var;
        }

        // If it's empty, just return the first token
        if (output.empty())
            output = tokens[0];
    }

    return output;
}

#endif
