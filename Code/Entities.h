#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "Structs.h"

void setCheesePosition(Cheese* cheese, int x, int y);
SDL_Point getCheesePosition(Cheese* cheese);
Cheese* createCheese(int x, int y, SDL_Renderer* renderer);
void destroyCheese(Cheese* cheese);
void renderCheese(SDL_Renderer* renderer, Cheese* cheese);

void setMousePosition(Mouse* mouse, int x, int y);
SDL_Point getMousePosition(Mouse* mouse);
Mouse* createMouse(int x, int y, SDL_Renderer* renderer);
void destroyMouse(Mouse* mouse);
void renderMouse(SDL_Renderer* renderer, Mouse* mouse);

void setCatPosition(Cat* cat, int x, int y);
SDL_Point getCatPosition(Cat* cat);
Cat* createCat(int x, int y, SDL_Renderer* renderer);
void destroyCat(Cat* cat);
void renderCat(SDL_Renderer* renderer, Cat* cat);

#endif // ENTITIES_H_INCLUDED
