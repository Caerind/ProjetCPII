#include <stdlib.h>
#include <stdio.h>

#include "Code/Utils.h"
#include "Code/Chunk.h"

#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
    saveChunk();

    Coords souris;
    souris.x = 2;
    souris.y = 4;

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Cr�ation de la fen�tre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma premiere application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);

        if( pWindow )
        {
            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fen�tre */

            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de cr�ation de la fen�tre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();

    return 0;
}
