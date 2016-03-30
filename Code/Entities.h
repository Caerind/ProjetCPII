#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "Structs.h"

void SetCheesePosition(Cheese* cheese, int x, int y);
SDL_Point GetCheesePosition(Cheese* cheese);
Cheese* createCheese(int x, int y, SDL_Renderer* renderer);
void destroyCheese(Cheese* cheese);
void renderCheese(SDL_Renderer* renderer, Cheese* cheese);

void SetMousePosition(Mouse* mouse, int x, int y);
SDL_Point GetMousePosition(Mouse* mouse);
Mouse* createMouse(int x, int y, SDL_Renderer* renderer);
void destroyMouse(Mouse* mouse);
void renderMouse(SDL_Renderer* renderer, Mouse* mouse);

void SetCatPosition(Cat* cat, int x, int y);
SDL_Point GetCatPosition(Cat* cat);
Cat* createCat(int x, int y, SDL_Renderer* renderer);
void destroyCat(Cat* cat);
void renderCat(SDL_Renderer* renderer, Cat* cat);

#endif // ENTITIES_H_INCLUDED
