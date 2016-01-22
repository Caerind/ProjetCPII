#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "Structs.h"

void SetCheesePosition(Cheese* cheese,int x, int y);
Coords GetCheesePosition(Cheese* cheese);
Cheese* createCheese(int x, int y,SDL_Renderer* renderer);
void destroyCheese(Cheese* cheese);
void renderCheese(SDL_Renderer* renderer, Cheese* cheese);




#endif // ENTITIES_H_INCLUDED
