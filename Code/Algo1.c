#include "Utils.h"
#include "MazeGenerator.h"

Maze* mAlgo1Maze = NULL;

int ALGO1_create(SDL_Renderer* renderer)
{
    mAlgo1Maze = createMaze(TILE_WIDTH,TILE_HEIGHT);
    if (mAlgo1Maze == NULL)
    {
        error("Algo1Maze");
        return 0;
    }

    generation(mAlgo1Maze);

    mAlgo1Maze->cheeses[mAlgo1Maze->numCheeses] = createCheese(1,1,renderer);
    mAlgo1Maze->numCheeses++;

    mAlgo1Maze->mouses[mAlgo1Maze->numMouses] = createMouse(23,17,renderer);
    generateMouseTree(mAlgo1Maze,mAlgo1Maze->numMouses);
    mAlgo1Maze->numMouses++;

    return 1;
}

void ALGO1_destroy()
{
    int i = 0;
    for (i = 0; i < mAlgo1Maze->numCheeses; i++)
    {
        destroyCheese(mAlgo1Maze->cheeses[i]);
    }
    for (i = 0; i < mAlgo1Maze->numMouses; i++)
    {
        destroyMouse(mAlgo1Maze->mouses[i]);
    }
    destroyMaze(mAlgo1Maze);
}

void ALGO1_handleEvent(SDL_Event event, SDL_Context* context)
{
    SDL_Point m = SDL_GetMousePosition();

    // Retourner au menu
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        STATES_switch(STATE_MENU,context);
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED)
    {
        // Left
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            nextMoveMouse(mAlgo1Maze,0);
        }
    }
}

void ALGO1_update()
{
}

void ALGO1_render(SDL_Renderer* renderer)
{
    int i;
    renderMaze(renderer,mAlgo1Maze);
    for (i = 0; i < mAlgo1Maze->numCheeses; i++)
    {
        renderCheese(renderer,mAlgo1Maze->cheeses[i]);
    }
    for (i = 0; i < mAlgo1Maze->numMouses; i++)
    {
        renderMouse(renderer,mAlgo1Maze->mouses[i]);
    }
}
