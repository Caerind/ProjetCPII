#include "Defines.h"
#include "Structs.h"
#include "Utils.h"
#include "Menu.h"

int actualState = -1;

int STATES_getState()
{
    return actualState;
}

void STATES_handleEvent(SDL_Event event, SDL_Context* context)
{
    switch (actualState)
    {
        case STATE_MENU: MENU_handleEvent(event,context); break;
        //case STATE_GAME: GAME_handleEvent(event,context); break;
        //case STATE_ALGO_1: ALGO1_handleEvent(event,context); break;
        //case STATE_ALGO_2: ALGO2_handleEvent(event,context); break;
        default: break;
    }
}

void STATES_update()
{
    switch (actualState)
    {
        case STATE_MENU: MENU_update(); break;
        //case STATE_GAME: GAME_update(); break;
        //case STATE_ALGO_1: ALGO1_update(); break;
        //case STATE_ALGO_2: ALGO2_update(); break;
        default: break;
    }
}

void STATES_render(SDL_Renderer* renderer)
{
    switch (actualState)
    {
        case STATE_MENU: MENU_render(renderer); break;
        //case STATE_GAME: GAME_destroy(renderer); break;
        //case STATE_ALGO_1: ALGO1_destroy(renderer); break;
        //case STATE_ALGO_2: ALGO2_destroy(renderer); break;
        default: break;
    }
}

int STATES_switch(int newState, SDL_Context* context)
{
    int success = 1;

    switch (actualState)
    {
        case STATE_MENU: MENU_destroy(); break;
        //case STATE_GAME: GAME_destroy(); break;
        //case STATE_ALGO_1: ALGO1_destroy(); break;
        //case STATE_ALGO_2: ALGO2_destroy(); break;
        default: break;
    }

    switch (newState)
    {
        case STATE_MENU: success = MENU_create(context->renderer); break;
        //case STATE_GAME: success = GAME_create(context->renderer); break;
        //case STATE_ALGO_1: success = ALGO1_create(context->renderer); break;
        //case STATE_ALGO_2: success = ALGO2_create(context->renderer); break;
        default: success = 0; break;
    }

    if (success == 0)
    {
        context->isOpen = 0;
    }
    else
    {
        actualState = newState;
    }

    return success;
}
