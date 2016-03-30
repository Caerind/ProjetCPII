#include <stdlib.h>
#include <stdio.h>

#include "Code/Application.h"
#include "Code/Defines.h"

int main(int argc, char** argv)
{
    if (init("The maze of Tom and Jerry",SCREEN_WIDTH,SCREEN_HEIGHT))
    {
        run();
    }
    quit();
    return EXIT_SUCCESS;
}
