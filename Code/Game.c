#include "Utils.h"
#include "Maze.h"
#include "MazeGenerator.h"

Maze* mMaze = NULL;
Cheese* mCheeses[100] = NULL;
int numCheeses = 0;
Mouse* mMouses[100] = NULL;
int numMouses = 0;

int GAME_create(SDL_Renderer* renderer)
{
    mMaze = loadMazeFromFile("Assets/maze.xmaze");
    if (mMaze == NULL)
    {
        error("Maze");
        return 0;
    }

    mCheeses[numCheeses] = createCheese(1,1,renderer);
    if (mChesses[numCheeses] != NULL)
    {
        numCheeses++;
    }
    else
    {
        error("Tab chesse");
        return 0;
    }

    mMouses[numMouses] = createMouse(23,17,renderer);
    if (mMouses[numMouses] != NULL)
    {
        numMouses++;
    }
    else
    {
        error("Tab mouse");
        return 0;
    }

    return 1;
}

void GAME_destroy()
{
    int i = 0;
    destroyMaze(mMaze);
    for (i = 0; i < numChesses; i++)
    {
        destroyChesse(mCheeses[i]);
    }
    for (i = 0; i < numMouses; i++)
    {
        destroyMouse(mMouses[i]);
    }
}

void GAME_handleEvent(SDL_Event event, SDL_Context* context)
{
    SDL_Point m = SDL_GetMousePosition();

    // Retourner au menu
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        STATES_switch(STATE_MENU,context);
    }

    // Souris
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED)
    {
        // Left
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) != 1)
            {
                mMouses[numCheeses] = createMouse(m.x / TILE_SIZE,m.y / TILE_SIZE,renderer);
                if (mMouses[numMouses] != NULL)
                {
                    numMouses++;
                }
                else
                {
                    error("Tab mouse");
                }
            }
        }

        // Right
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) != 1)
            {
                mCheeses[numCheeses] = createCheese(m.x / TILE_SIZE,m.y / TILE_SIZE,renderer);
                if (mChesses[numCheeses] != NULL)
                {
                    numCheeses++;
                }
                else
                {
                    error("Tab chesse");
                }
            }
        }

        // Middle
        if (event.button.button == SDL_BUTTON_MIDDLE)
        {
            setMazeId(mMaze, m.x / TILE_SIZE, m.y / TILE_SIZE, 4);
        }
    }
}

void GAME_update()
{
}

void GAME_render(SDL_Renderer* renderer)
{
    int i = 0;
    renderMaze(renderer,mMaze);
    for (i = 0; i < numCheeses; i++)
    {
        renderCheese(renderer,mCheeses[i]);
    }
    for (i = 0; i < numMouses; i++)
    {
        renderMouse(renderer,mMouses[i]);
    }
}
