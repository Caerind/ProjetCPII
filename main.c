#include <stdlib.h>
#include <stdio.h>

#include "Code/Application.h"

#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
    if (init())
    {
        run();
    }
    quit();
    return EXIT_SUCCESS;
}
