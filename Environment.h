#ifndef __ENV__
#define __ENV__

#include <iostream>

#include "interpreter.h"

class Environment
{
    public:
        int run();

    private:
        std::vector<Symbol> global_symbols;

        bool DEBUG;
};

#endif
