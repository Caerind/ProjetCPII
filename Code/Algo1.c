#include "Utils.h"

int ALGO1_create(SDL_Renderer* renderer)
{

}

void ALGO1_destroy()
{

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

}
