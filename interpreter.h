#ifndef __INTERP__
#define __INTERP__

#include <iostream>
#include <vector>

#include "core.h"

inline static std::vector<std::string> tokenize(std::string input, std::vector<Symbol>& symbols, bool literal, bool DEBUG);

/**
 * Execute Scheme code by evaluating tokens.
 * 
 * @param tokens Vector of strings represeting scheme code.
 * @param symbols Vector of Symbols.
 * @param silent Boolean to silence console output of 'output' string. (Should probably remove...)
 * @param debug Boolean to switch debug printing.
 * @return String of final output.
 */
inline static std::string execute(std::vector<std::string> tokens, std::vector<Symbol>& symbols, bool silent, bool DEBUG)
{
    std::string left = (tokens.size() >= 2) ? tokens[1] : "0"; // If not enough tokens for left side, assume its 0.
    std::string right = (tokens.size() >= 3) ? tokens[2] : "0"; // If not enough tokens for right side, assume its 0.
    std::string output; // String to store final output in.

    // If left side is not an integer or a define call expression, get symbol value
    if (isSymbol(left) && tokens[0] != "define")
    {
        int symbI = findSymbol(left, symbols);
        if (symbI != -1)
            left = symbols[symbI].m_var;
    }

    // If right side is not an integer or a define call expression, get symbol value
    if (isSymbol(right) && tokens[0] != "define")
    {
        int symbI = findSymbol(right, symbols);
        if (symbI != -1)
            right = symbols[symbI].m_var;
    }

    // Get output with function from 'core.h'
    output = run_instruction(tokens, left, right, symbols);
    
    // If not silent, then console output the final output
    if (!silent)
        std::cout << output << std::endl;

    // DEBUG SHIT
    if (tokens[0] == "debug")
        return 0;
    
    if (DEBUG)
        std::cout << "OP: " << tokens[0];
    if (DEBUG)
        std::cout << " A1: " << left;
    if (DEBUG)
        std::cout << " A2: " << right;
    if (DEBUG)
        std::cout << " OUT: " << output << std::endl << std::endl;

    // Return the output
    return output;
}

/**
 * Split a string of Scheme code into tokens.
 *
 * If it finds nested call expressions,
 * it will recursively evaluate and get the result.
 * (Except when it's defining a function)
 *
 * @param input String of Scheme code to tokenize.
 * @param symbols Vector of Symbols.
 * @param literal Boolean to deactivate token evalutation.
 * @param debug Boolean to switch debug printing.
 * @return Vector of string tokens.
 */
inline static std::vector<std::string> tokenize(std::string input, std::vector<Symbol>& symbols, bool literal, bool DEBUG)
{
    const char *s = input.c_str(); // Convert input to C string to iterate through it
    std::vector<std::string> tokens; // Vector to store tokens
    std::string token; // String to store current token

    s++;

    while (*s)
    {
        // If it encounters a whitespace, add token to tokens & start looking for new one
        while (*s == ' ')
        {
            if (token != "")
                tokens.push_back(token);
            token = "";
            s++;
        }

        // Add to token unless it finds a paranthesis or whitespace
        if (*s != '(')
        {
            if (*s != ')' || *s == ' ')
                token += *s;
        }
        // Left side paranthesis found, read until closing paranthesis and evaluate
        // HACK ALERT: If it (badly) detects a function, it will not evaluate the code, it will add it as is
        else
        {
            std::string temp = "(";
            int parans = 0;

            s++;

            // Iterate through input until it finds closing paranthesis.
            // Uses parans to handle nested paranthesis.
            while (*s != ')' || parans > 0)
            {
                if (*s == '(')
                    parans++;
                if (*s == ')')
                    parans--;
                temp += *s;
                s++;
            }

            temp += ')'; // Closing paranthesis for nice parsing with recursive tokenize call

            // If first token is 'defined' & only one token has been found, then we can assume we are dealing with a function.
            // If the above holds true, or we have already found out, then dont evaluate 'temp' and just push it to tokens.
            if (tokens[0] == "define" && tokens.size() < 2 || literal)
            {
                token = temp;
                literal = true; // Activate literal mode
            }
            else
                token = execute(tokenize(temp, symbols, false, DEBUG), symbols, true, DEBUG); // Tokenize 'temp' & evaluate it with 'execute(tokens, symbols, DEBUG)'

            tokens.push_back(token);

            token = "";
        }

        s++;
    }

    // Push back the last token if its not empty
    if (token != "")
        tokens.push_back(token);

    // DEBUG SHIT
    if (DEBUG)
        std::cout << std::endl;

    if (DEBUG)
    {
    for (int i = 0; i < tokens.size(); i++)
    {
        std::cout << ">" << tokens[i] << std::endl;
    }
    }

    return tokens;
}

#endif
