#include "Utils.h"


void SetCheesePosition(Cheese* cheese,int x, int y)
{
    cheese->coords.x=x;
    cheese->coords.y=y;
    cheese->sprite->pos.x=x*TILE_SIZE;
    cheese->sprite->pos.y=y*TILE_SIZE;
}

Coords GetCheesePosition(Cheese* cheese)
{
   return cheese->coords;
}



Cheese* createCheese(int x, int y,SDL_Renderer* renderer)
{
     Cheese* cheese = NULL;

    // Allocation m¨¦moire
    cheese = malloc(sizeof(Cheese));
    if (cheese == NULL)
    {
        error("Mauvaise alloc-Cheese");
        return NULL;
    }

    cheese->sprite=SDL_CreateSprite("Assets/fromage.bmp",renderer);

    SetCheesePosition(cheese,x,y);

    return cheese;
}


void destroyCheese(Cheese* cheese)
{
    SDL_DestroySprite(cheese->sprite);
    free(cheese);
}


void renderCheese(SDL_Renderer* renderer, Cheese* cheese)
{
    SDL_RenderSprite(renderer,cheese->sprite);
}


