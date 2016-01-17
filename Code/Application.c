#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

SDL_Window* mWindow = NULL;
int mWindowOpen = 0; // boolean

int init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    mWindow = SDL_CreateWindow("Labyrinthe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return -2;
    }
    else
    {
        mWindowOpen = 1; // true
    }

    return 1;
}

void quit()
{
    if (mWindow != NULL)
    {
        SDL_DestroyWindow(mWindow);
        mWindowOpen = 0; // false
    }

    SDL_Quit();
}

void handleInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            mWindowOpen = 0; // false
        }
    }
}

void update()
{

}

void render()
{

}

void run()
{
    while (mWindowOpen)
    {
        handleInput();

        update();

        render();
    }
}

