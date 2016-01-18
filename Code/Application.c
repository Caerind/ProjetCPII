#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Utils.h"
#include "Defines.h"
#include "Maze.h"
#include "MazeGenerator.h"

SDL_Window* mWindow = NULL;
SDL_Renderer* mRenderer = NULL;
Sprite* mBackground = NULL;
int mWindowOpen = 0;

int mazeStep = 0;
int done = 0;
Maze* mMaze = NULL;

int init()
{
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        logSDLError("�chec de l'initialisation de la SDL");
        return -1;
    }

    mWindow = SDL_CreateWindow("Labyrinthe",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
        logSDLError("Erreur de cr�ation de la fen�tre");
        return -2;
    }
    else
    {
        mWindowOpen = 1; // true
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == NULL)
    {
        logSDLError("Impossible de cr�er le renderer");
        return -3;
    }

    mBackground = loadSprite("Assets/fond.bmp",mRenderer);
    if (mBackground == NULL)
    {
        logError("Impossible de cr�er la sprite");
        return -4;
    }

    //mMaze = loadMazeFromFile("Assets/test.xmaze");
    mMaze = createMaze(TILE_WIDTH,TILE_HEIGHT);
    if (mMaze == NULL)
    {
        logError("Erreur maze");
        return -5;
    }

    mazeGenerator(mMaze);

    return 1;
}

void quit()
{
    destroyMaze(mMaze);
    destroySprite(mBackground);

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
                mazeStep++;
                done = 0;
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
    if (done == 0)
    {
        switch (mazeStep)
        {
            case 1: generationStep1(mMaze) ; break;
            case 2: generationStep2(mMaze); break;
            case 3: generationStep3(mMaze); break;
            case 4: generationStep4(mMaze); break;
            case 5: generationStep5(mMaze); break;
            case 6: generationStep6(mMaze); break;
            case 7: generationStep7(mMaze); break;
            default: break;
        }
        done = 1;
    }
}

void render()
{
    //First clear the renderer
	SDL_RenderClear(mRenderer);

	//Draw the texture
	renderSprite(mRenderer, mBackground);
	renderMaze(mRenderer, mMaze);

	//Update the screen
	SDL_RenderPresent(mRenderer);
}

void run()
{
    while (mWindowOpen)
    {
        handleInput();

        update();

        render();

        //Take a quick break after all that hard work
        SDL_Delay(20); // ~60FPS
    }
}

