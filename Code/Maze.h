#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <SDL2/SDL.h>
#include "Structs.h"

Maze* createMaze(int sizeX,int sizeY);
void destroyMaze(Maze* maze);
void renderMaze(SDL_Renderer* renderer, Maze* maze);
void fillMaze(Maze* maze, int id);
int getMazeId(Maze* maze, int x, int y);
void setMazeId(Maze* maze, int x, int y, int id);

Maze* loadMazeFromFile(const char* filename);

#endif // MAZE_H_INCLUDED
