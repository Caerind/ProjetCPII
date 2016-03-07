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

    return 1;
}

void ALGO1_destroy()
{
    destroyMaze(mAlgo1Maze);
}

void ALGO1_handleEvent(SDL_Event event, SDL_Context* context)
{
    // Retourner au menu
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        STATES_switch(STATE_MENU,context);
    }
}

void ALGO1_update()
{
}

void ALGO1_render(SDL_Renderer* renderer)
{
    renderMaze(renderer,mAlgo1Maze);
}
