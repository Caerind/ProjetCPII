#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SDL2/SDL.h>

struct Coords
{
    int x;
    int y;
};
typedef struct Coords Coords;

struct Sprite
{
    SDL_Texture* texture;
    int x;
    int y;
    SDL_Rect rect;
};
typedef struct Sprite Sprite;

#endif // SPRITE_H_INCLUDED
