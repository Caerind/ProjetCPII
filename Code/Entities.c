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




void SetMousePosition(Mouse* mouse,int x, int y)
{
    mouse->coords.x=x;
    mouse->coords.y=y;
    mouse->sprite->pos.x=x*TILE_SIZE;
    mouse->sprite->pos.y=y*TILE_SIZE;
}

Coords GetMousePosition(Mouse* mouse)
{
   return mouse->coords;
}


Mouse* createMouse()(int x, int y,SDL_Renderer* renderer)
{
     Mouse* mouse = NULL;

    // Allocation m¨¦moire
    mouse = malloc(sizeof(Mouse));
    if (mouse == NULL)
    {
        error("Mauvaise alloc-Mouse");
        return NULL;
    }

    mouse->sprite=SDL_CreateSprite("Assets/souris.bmp",renderer);

    SetMousePosition(mouse,x,y);

    return mouse;
}


void destroyMouse(Mouse* mouse)
{
    SDL_DestroySprite(mouse->sprite);
    free(mouse);
}


void renderMouse(SDL_Renderer* renderer, Mouse* mouse)
{
    SDL_RenderSprite(renderer,mouse->sprite);
}

