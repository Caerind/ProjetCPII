#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utils.h"

SDL_Window* mWindow = NULL;
SDL_Renderer* mRenderer = NULL;
SDL_Texture* mBackground = NULL;
int mWindowOpen = 0; // boolean

int init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        logSDLError("Échec de l'initialisation de la SDL");
        return -1;
    }

    mWindow = SDL_CreateWindow("Labyrinthe",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
        logSDLError("Erreur de création de la fenêtre");
        return -2;
    }
    else
    {
        mWindowOpen = 1; // true
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == NULL)
    {
        logSDLError("Impossible de créer le renderer");
        return -3;
    }

    mBackground = loadTexture("fond.bmp",mRenderer);

    return 1;
}

void quit()
{
    SDL_DestroyTexture(mBackground);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    mWindowOpen = 0; // false

    SDL_Quit();
}

void handleInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        // Handle quit
        if(event.type == SDL_QUIT)
        {
            mWindowOpen = 0; // false
        }

        // Handle Mouse Click
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // Handle Mouse Click Left
            if (event.button.button == SDL_BUTTON_LEFT)
            {
            }

            // Handle Mouse Click Right
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
            }

            // Handle Mouse Click Middle
            if (event.button.button == SDL_BUTTON_MIDDLE)
            {
            }
        }
    }
}

void update()
{

}

void render()
{
    //First clear the renderer
	SDL_RenderClear(mRenderer);

	//Draw the texture
	renderTexture(mBackground, mRenderer, 0, 0, NULL);

	//Update the screen
	SDL_RenderPresent(mRenderer);

	//Take a quick break after all that hard work
	SDL_Delay(16); // 60FPS
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

