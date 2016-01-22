#include "Utils.h"

int ALGO2_create(SDL_Renderer* renderer)
{

}

void ALGO2_destroy()
{

}

void ALGO2_handleEvent(SDL_Event event, SDL_Context* context)
{
    // Retourner au menu
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        STATES_switch(STATE_MENU,context);
    }
}

void ALGO2_update()
{

}

void ALGO2_render(SDL_Renderer* renderer)
{

}
