#ifndef __INTERP__
#define __INTERP__

#include <iostream>
#include <vector>

#include "helpers.h"
#include "Symbol.h"

inline static std::vector<std::string> tokenize(std::string input, std::vector<Symbol>& symbols, bool DEBUG);

inline static std::string execute(std::vector<std::string> tokens, std::vector<Symbol>& symbols, bool silent, bool DEBUG)
{
    std::string left = (tokens.size() >= 2) ? tokens[1] : "0";
    std::string right = (tokens.size() >= 3) ? tokens[2] : "0";
    std::string output;

    if (isSymbol(left) && tokens[0] != "define")
    {
        int symbI = findSymbol(left, symbols);
        if (symbI != -1)
            left = symbols[symbI].var;
    }

    if (isSymbol(right) && tokens[0] != "define")
    {
        int symbI = findSymbol(right, symbols);
        if (symbI != -1)
            right = symbols[symbI].var;
    }

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
        if (!isSymbol(left))
        {
            std::cout << "Error:\n\tNon-symbol: " << left << std::endl;
            return "Error";
        }

        int symbolIndex = findSymbol(tokens[1], symbols);
        
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
        for (int i = 0; i < symbols.size(); i++)
        {
            if (symbols[i].name == tokens[0])
                output = symbols[i].var;
        }

        if (output.empty())
            output = tokens[0];
    }

    if (!silent)
        std::cout << output << std::endl;

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

    return output;
}

inline static std::vector<std::string> tokenize(std::string input, std::vector<Symbol>& symbols, bool DEBUG)
{
    const char *s = input.c_str();
    std::vector<std::string> tokens;
    std::string token;

    s++;

    while (*s)
    {
        while (*s == ' ')
        {
            if (token != "")
                tokens.push_back(token);
            token = "";
            s++;
        }

        if (*s != '(')
        {
            if (*s != ')' || *s == ' ')
                token += *s;
        }
        else
        {
            std::string temp = "(";
            int parans = 0;

            s++;

            while (*s != ')' || parans > 0)
            {
                if (*s == '(')
                    parans++;
                if (*s == ')')
                    parans--;
                temp += *s;
                s++;
            }

            temp += ')';

            token = execute(tokenize(temp, symbols, DEBUG), symbols, true, DEBUG);

            tokens.push_back(token);

            token = "";
        }

        s++;
    }

    if (token != "")
        tokens.push_back(token);

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
