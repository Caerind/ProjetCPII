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
    Coords pos;
    SDL_Rect rect;
};
typedef struct Sprite Sprite;

struct Maze
{
    int** tab;
    Coords size;
};
typedef struct Maze Maze;

#endif // SPRITE_H_INCLUDED
