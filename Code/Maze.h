#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <SDL2/SDL.h>
#include "Structs.h"

Maze* createMaze(int size);
void destroyMaze(Maze* maze);
void renderMaze(SDL_Renderer* renderer, Maze* maze);
void fillMaze(Maze* maze, int id);

Maze* loadMazeFromFile(const char* filename);
Maze* generateMaze(int size);

#endif // MAZE_H_INCLUDED
