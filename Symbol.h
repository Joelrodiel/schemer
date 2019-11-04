#ifndef _SYMBOL_
#define _SYMBOL_

#include <vector>
#include <string>

class Symbol
{
    public:
        Symbol(std::string n, std::string v) : name(n), var(v) {}

        std::string name;
        std::string var;
};

class Function
{
    public:
        Function(std::string param, std::string c);

        std::string name;
        std::string code;
        std::vector<std::string> parameters;
};

#endif
