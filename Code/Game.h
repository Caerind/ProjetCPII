#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Utils.h"

int GAME_create(SDL_Renderer* renderer);
void GAME_destroy();
void GAME_handleEvent(SDL_Event event, SDL_Context* context);
void GAME_update();
void GAME_render(SDL_Renderer* renderer);

#endif // GAME_H_INCLUDED
