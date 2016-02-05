#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SDL2/SDL.h>

struct SDL_Context
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int isOpen;
};
typedef struct SDL_Context SDL_Context;

struct Coords
{
    int x;
    int y;
};
typedef struct Coords Coords;

struct SDL_Sprite
{
    SDL_Texture* texture;
    SDL_Point pos;
    SDL_Rect rect;
};
typedef struct SDL_Sprite SDL_Sprite;

struct Cheese
{
    Coords coords;
    SDL_Sprite* sprite;
};
typedef struct Cheese Cheese;

struct Mouse
{
    Coords coords;
    SDL_Sprite* sprite;
};
typedef struct Mouse Mouse;

struct Cat
{
    Coords coords;
    SDL_Sprite* sprite;
};
typedef struct Cat Cat;

struct Maze
{
    int** tab;
    Coords size;

    Cheese* cheeses[100];
    int numCheeses;

    Mouse* mouses[100];
    int numMouses;

    Cat* mCats[100];
    int numCats;
};
typedef struct Maze Maze;

struct Node
{
    int x;
    int y;
    struct Node* parent;
};
typedef struct Node Node;

#endif // SPRITE_H_INCLUDED
