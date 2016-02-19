#include "Utils.h"

Maze* mAlgo2Maze = NULL;
int mAlgo2Step = 0;

int ALGO2_create(SDL_Renderer* renderer)
{
    mAlgo2Maze = createMaze(TILE_WIDTH,TILE_HEIGHT);

    // Dessiner un black screen
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
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED && event.button.button == SDL_BUTTON_LEFT)
    {
        mAlgo2Step++;
        switch (mAlgo2Step)
        {
            case 1: generationStep1(mAlgo2Maze); break;
            case 2: generationStep2(mAlgo2Maze); break;
            case 3: generationStep3(mAlgo2Maze); break;
            case 4: generationStep4(mAlgo2Maze); break;
            case 5: generationStep5(mAlgo2Maze); break;
            case 6: generationStep6(mAlgo2Maze); break;
            case 7: generationStep7(mAlgo2Maze); break;
            default: break;
        }
    }
}

void ALGO2_update()
{

}

void ALGO2_render(SDL_Renderer* renderer)
{
    renderMaze(renderer, mAlgo2Maze);
}
