#include "Utils.h"
#include "Maze.h"
#include "MazeGenerator.h"
#include "Entities.h"
#include "States.h"
#include "Path.h"

Maze* mMaze = NULL;
int mFrameMouseCount = 0;
int mFrameCatCount = 0;

int GAME_create(SDL_Renderer* renderer)
{
    mMaze = createMaze(TILE_WIDTH,TILE_HEIGHT);
    if (mMaze == NULL)
    {
        error("Maze");
        return 0;
    }

    generation(mMaze);

    mMaze->cheeses[mMaze->numCheeses] = createCheese(1,1,renderer);
    mMaze->numCheeses++;

    mMaze->mouses[mMaze->numMouses] = createMouse(23,17,renderer);
    generateMouseTree(mMaze,mMaze->numMouses);
    mMaze->numMouses++;
    return 1;
}

void GAME_destroy()
{
    int i = 0;
    for (i = 0; i < mMaze->numCheeses; i++)
    {
        destroyCheese(mMaze->cheeses[i]);
    }
    for (i = 0; i < mMaze->numMouses; i++)
    {
        destroyMouse(mMaze->mouses[i]);
    }
    for (i = 0; i < mMaze->numCats; i++)
    {
        destroyCat(mMaze->cats[i]);
    }
    destroyMaze(mMaze);
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
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) < 6)
            {
                mMaze->mouses[mMaze->numMouses] = createMouse(m.x / TILE_SIZE,m.y / TILE_SIZE,context->renderer);
                generateMouseTree(mMaze,mMaze->numMouses);
                mMaze->numMouses++;
            }
        }

        // Right
        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) < 6)
            {
                mMaze->cheeses[mMaze->numCheeses] = createCheese(m.x / TILE_SIZE,m.y / TILE_SIZE,context->renderer);
                mMaze->numCheeses++;
            }
        }

        // Middle
        if (event.button.button == SDL_BUTTON_MIDDLE)
        {
            if (getMazeId(mMaze,m.x / TILE_SIZE,m.y / TILE_SIZE) < 6)
            {
                mMaze->cats[mMaze->numCats] = createCat(m.x / TILE_SIZE,m.y / TILE_SIZE,context->renderer);
                mMaze->numCats++;
            }
        }
    }
}

void GAME_update()
{
    int i = 0;

    mFrameMouseCount++;
    if (mFrameMouseCount >= 8)
    {
        for (i = 0; i < mMaze->numMouses; i++)
        {
            nextMoveMouse(mMaze,i);
        }
        mFrameMouseCount = 0;
    }

    mFrameCatCount++;
    if (mFrameCatCount >= 14)
    {
        for (i = 0; i < mMaze->numCats; i++)
        {
            nextMoveCat(mMaze,i);
        }
        mFrameCatCount = 0;
    }
}

void GAME_render(SDL_Renderer* renderer)
{
    int i = 0;
    renderMaze(renderer,mMaze);
    for (i = 0; i < mMaze->numCheeses; i++)
    {
        renderCheese(renderer,mMaze->cheeses[i]);
    }
    for (i = 0; i < mMaze->numMouses; i++)
    {
        renderMouse(renderer,mMaze->mouses[i]);
    }
    for (i = 0; i < mMaze->numCats; i++)
    {
        renderCat(renderer,mMaze->cats[i]);
    }
}
