#ifndef ALGO2_H_INCLUDED
#define ALGO2_H_INCLUDED

#include "Utils.h"

int ALGO2_create(SDL_Renderer* renderer);
void ALGO2_destroy();
void ALGO2_handleEvent(SDL_Event event, SDL_Context* context);
void ALGO2_update();
void ALGO2_render(SDL_Renderer* renderer);

#endif // ALGO2_H_INCLUDED
