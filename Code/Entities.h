#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "Structs.h"

void SetCheesePosition(Cheese* cheese,int x, int y);
Coords GetCheesePosition(Cheese* cheese);
Cheese* createCheese(int x, int y,SDL_Renderer* renderer);
void destroyCheese(Cheese* cheese);
void renderCheese(SDL_Renderer* renderer, Cheese* cheese);

void SetMousePosition(Mouse* mouse,int x, int y);
Coords GetMousePosition(Mouse* mouse);
Mouse* createMouse(int x, int y,SDL_Renderer* renderer);
void destroyMouse(Mouse* mosue);
void renderMouse(SDL_Renderer* renderer, Mouse* mouse);




#endif // ENTITIES_H_INCLUDED
