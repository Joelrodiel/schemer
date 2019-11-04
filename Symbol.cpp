#include <string>
#include <vector>

#include "Symbol.h"
#include "interpreter.h"

Function::Function(std::string param, std::string c) : Symbol("", "")
{
    m_type = "function";

    std::vector<std::string> param_tokens = tokenize(param, m_local_symbols, true, false);

    m_name = param_tokens[0];

    for (int i = 1; i < param_tokens.size(); i++)
        m_parameters.push_back(param_tokens[i]);

    m_code = c;
}

void Function::execute(std::vector<Symbol*>& global_symbols, std::string code)
{
}
