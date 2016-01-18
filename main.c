#include <stdlib.h>
#include <stdio.h>

#include "Code/Application.h"

int main(int argc, char** argv)
{
    if (init())
    {
        run();
    }
    quit();
    return EXIT_SUCCESS;
}
