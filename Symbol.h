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
        Symbol(std::string n, std::string v) : m_name(n), m_var(v) { m_type = "symbol"; }

        std::string m_type;
        std::string m_name;
        std::string m_var;
};

/**
 * Function class that stores function name, code & local symbols.
 */
class Function : public Symbol
{
    public:
        Function(std::string param, std::string c);

        void execute(std::vector<Symbol*>& global_symbols, std::string code);

        std::vector<std::string> m_parameters;
        std::vector<Symbol*> m_local_symbols;
};

#endif
