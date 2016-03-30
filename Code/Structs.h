#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

// Noeud pour l'intelligence des souris
struct Node
{
    int x;
    int y;
    SDL_Point parent;
    int test; // test = 0, la node n'est pas encore priss
};
typedef struct Node Node;

// Sprite pour l'affichage simplifié
struct SDL_Sprite
{
    SDL_Texture* texture;
    SDL_Point pos;
    SDL_Rect rect;
};
typedef struct SDL_Sprite SDL_Sprite;

// Permet de gérer les structures SDL
struct SDL_Context
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* icon;
    Mix_Music* music;
    SDL_Sprite* cursor;
    int isOpen;
};
typedef struct SDL_Context SDL_Context;

// Fromage
struct Cheese
{
    SDL_Point coords;
    SDL_Sprite* sprite;
};
typedef struct Cheese Cheese;

// Souris
struct Mouse
{
    SDL_Point coords;
    SDL_Sprite* sprite;

    Node nodes[400];
    int numNodes;

    Node dest;
    Node start;
};
typedef struct Mouse Mouse;

// Chat
struct Cat
{
    SDL_Point coords;
    SDL_Sprite* sprite;

    Mouse *mouse;

    Node dest;
};
typedef struct Cat Cat;

// Labyrinthe
struct Maze
{
    int** tab;
    SDL_Point size;

    Cheese* cheeses[100];
    int numCheeses;

    Mouse* mouses[100];
    int numMouses;

    Cat* cats[100];
    int numCats;
};
typedef struct Maze Maze;

#endif // SPRITE_H_INCLUDED
