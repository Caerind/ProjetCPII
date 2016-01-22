#ifndef ALGO1_H_INCLUDED
#define ALGO1_H_INCLUDED

#include "Utils.h"

int ALGO1_create(SDL_Renderer* renderer);
void ALGO1_destroy();
void ALGO1_handleEvent(SDL_Event event, SDL_Context* context);
void ALGO1_update();
void ALGO1_render(SDL_Renderer* renderer);

#endif // ALGO1_H_INCLUDED
