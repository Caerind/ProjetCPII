#include "Utils.h"
#include "Maze.h"
#include "MazeGenerator.h"

static Maze* mAlgo1Maze = NULL;

int ALGO1_create(SDL_Renderer* renderer)
{
    mAlgo1Maze = createMaze(TILE_WIDTH,TILE_HEIGHT);
    if (mAlgo1Maze == NULL)
    {
        error("Algo1Maze");
        return 0;
    }

    generation(mAlgo1Maze);

    addMazeCheese(mAlgo1Maze,renderer,1,1);
    addMazeMouse(mAlgo1Maze,renderer,23,17);

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

    // Déplace la souris d'une case
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN)
    {
        nextMoveMouse(mAlgo1Maze,0);
    }
}

void ALGO1_update()
{
}

void ALGO1_render(SDL_Renderer* renderer)
{
    renderMaze(renderer,mAlgo1Maze);
}
