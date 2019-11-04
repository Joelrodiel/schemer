#ifndef __HELPERS__
#define __HELPERS__

#include <string>
#include <vector>

#include "Symbol.h"

inline static bool isSymbol(std::string s)
{
    if (s == "#t" || s == "#f")
        return false;

    char* p;
    strtol(s.c_str(), &p, 10);
    return *p != 0;
}

inline static int findSymbol(std::string name, const std::vector<Symbol>& symbols)
{
    for (int i = symbols.size(); i > 0; i--)
    {
        if (symbols[i - 1].name == name)
            return i - 1;
    }
    return -1;
}

#endif
