#ifndef __HELPERS__
#define __HELPERS__

#include <string>
#include <vector>

#include "Symbol.h"

/**
 * Check if string is a symbol (variable), or an integer.
 *
 * @param s String to check.
 * @return Boolean of if symbol or not.
 */
inline static bool isSymbol(std::string s)
{
    if (s == "#t" || s == "#f")
        return false;

    char* p;
    strtol(s.c_str(), &p, 10);
    return *p != 0;
}

/**
 * Finds symbol from a vector of Symbol objects by their name.
 *
 * Looks at symbols vector backwards because of previous implenentation.
 * Might change it to normal forward iteration if someone yells at me.
 *
 * @param name Name of symbol you want to find.
 * @param symbols Reference of vector of Symbol objects to look from.
 * @return Index of symbol in symbols, if does not exist return -1.
 */
inline static int findSymbol(std::string name, const std::vector<Symbol>& symbols)
{
    for (int i = symbols.size(); i > 0; i--)
    {
        if (symbols[i - 1].m_name == name)
            return i - 1;
    }
    return -1;
}

#endif
