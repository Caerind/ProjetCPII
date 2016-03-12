#include "Utils.h"

Maze* mAlgo2Maze = NULL;
int mAlgo2Step = 0;
int mAlgo2FPS = 0;
int mAlgo2Play = 0;

int ALGO2_create(SDL_Renderer* renderer)
{
    mAlgo2Maze = createMaze(TILE_WIDTH,TILE_HEIGHT);

    generationPrep(mAlgo2Maze);

    mAlgo2Step = 0;
    mAlgo2FPS = 0;
    mAlgo2Play = 0;
}

void ALGO2_destroy()
{
    destroyMaze(mAlgo2Maze);
}

void ALGO2_handleEvent(SDL_Event event, SDL_Context* context)
{
    // Retourner au menu
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        STATES_switch(STATE_MENU,context);
    }
    // Generation pas à pas
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED && event.button.button == SDL_BUTTON_LEFT)
    {
        if (mAlgo2Step == 0)
        {
            generationInit(mAlgo2Maze);
            mAlgo2Play = 1;
            mAlgo2Step++;
        }
        else if (mAlgo2Step == 1)
        {
            generationStep(mAlgo2Maze);
            mAlgo2Step++;
        }
        else if (mAlgo2Step == 2)
        {
            mAlgo2Play = (mAlgo2Play == 0) ? 1 : 0;
        }
    }
}

void ALGO2_update()
{
    mAlgo2FPS++;
    if (mAlgo2FPS >= 0)
    {
        mAlgo2FPS = 0;

        if (mAlgo2Step == 2 && mAlgo2Play == 1)
        {
            generationStep(mAlgo2Maze);
            if (isFinished())
            {
                mAlgo2Step = 3;
                generationFinish(mAlgo2Maze);
            }
        }
    }
}

void ALGO2_render(SDL_Renderer* renderer)
{
    renderMaze(renderer, mAlgo2Maze);
}
