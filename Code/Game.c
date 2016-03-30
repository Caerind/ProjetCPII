#include "Utils.h"
#include "Maze.h"
#include "MazeGenerator.h"
#include "Entities.h"
#include "States.h"
#include "Path.h"

static Maze* mMaze = NULL;
static int mFrameMouseCount = 0;
static int mFrameCatCount = 0;
static int mFrameCheeseCount = 0;

int GAME_create(SDL_Renderer* renderer)
{
    mMaze = createMaze(TILE_WIDTH,TILE_HEIGHT);
    if (mMaze == NULL)
    {
        error("Maze");
        return 0;
    }

    generation(mMaze);

    addMazeCheese(mMaze,renderer,1,1);
    addMazeMouse(mMaze,renderer,23,17);

    return 1;
}

void GAME_destroy()
{
    destroyMaze(mMaze);
}

void GAME_handleEvent(SDL_Event event, SDL_Context* context)
{
    // Position de la souris
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
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) < 6)
            {
                addMazeMouse(mMaze,context->renderer,m.x / TILE_SIZE,m.y / TILE_SIZE);
            }
        }

        // Right
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) < 6)
            {
                addMazeCheese(mMaze,context->renderer,m.x / TILE_SIZE,m.y / TILE_SIZE);
            }
        }

        // Middle
        if (event.button.button == SDL_BUTTON_MIDDLE)
        {
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) < 6)
            {
                addMazeCat(mMaze,context->renderer,m.x / TILE_SIZE,m.y / TILE_SIZE);
            }
        }
    }
}

void GAME_update()
{
    int i = 0;

    mFrameMouseCount++;
    if (mFrameMouseCount >= 8) // On mets à jour les souris
    {
        for (i = 0; i < mMaze->numMouses; i++)
        {
            nextMoveMouse(mMaze,i);
        }
        mFrameMouseCount = 0;
    }

    mFrameCatCount++;
    if (mFrameCatCount >= 10) // On mets à jour les chats
    {
        for (i = 0; i < mMaze->numCats; i++)
        {
            nextMoveCat(mMaze,i);
        }
        mFrameCatCount = 0;
    }

    updateMaze(mMaze); // On supprime les entites qui doivent l'etre
}

void GAME_render(SDL_Renderer* renderer)
{
    renderMaze(renderer,mMaze);
}
