#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Utils.h"

int MENU_create(SDL_Renderer* renderer);
void MENU_destroy();
void MENU_handleEvent(SDL_Event event, SDL_Context* context);
void MENU_update();
void MENU_render(SDL_Renderer* renderer);

#endif // MENU_H_INCLUDED
