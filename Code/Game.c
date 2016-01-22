#include "Utils.h"
#include "Maze.h"
#include "MazeGenerator.h"

Maze* mMaze = NULL;
Cheese* mCheese=NULL;

int GAME_create(SDL_Renderer* renderer)
{
    mMaze = loadMazeFromFile("Assets/maze.xmaze");
    if (mMaze == NULL)
    {
        error("Maze");
        return 0;
    }

    mCheese=createCheese(1,1,renderer);

    return 1;
}

void GAME_destroy()
{
    destroyMaze(mMaze);
    destroyCheese(mCheese);
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
            setMazeId(mMaze, m.x / TILE_SIZE, m.y / TILE_SIZE, 2);
        }

        // Right
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            setMazeId(mMaze, m.x / TILE_SIZE, m.y / TILE_SIZE, 3);
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
    renderMaze(renderer,mMaze);
    renderCheese(renderer,mCheese);
}
