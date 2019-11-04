#include <iostream>
#include <fstream>

#include "Environment.h"

int main(int argc, char *argv[])
{

    Environment main_env; // Create new environment

    main_env.run(); // Run it
    
    return 0; // Kill it
}
