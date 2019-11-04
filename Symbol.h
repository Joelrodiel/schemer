#ifndef _SYMBOL_
#define _SYMBOL_

#include <vector>
#include <string>

/**
 * Symbol class that stores symbol name & variable.
 */
class Symbol
{
    public:
        Symbol(std::string n, std::string v) : name(n), var(v) {}

        std::string name;
        std::string var;
};

/**
 * Function class that stores function name, code & local symbols.
 */
class Function
{
    public:
        Function(std::string param, std::string c);

        std::string name;
        std::string code;
        std::vector<std::string> parameters;
        std::vector<Symbol> local_symbols;
};

#endif
