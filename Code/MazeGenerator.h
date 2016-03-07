#ifndef MAZEGENERATOR_H_INCLUDED
#define MAZEGENERATOR_H_INCLUDED

#include "Structs.h"

int isWallNode(SDL_Point p);
int isBorder(int x, int y);
int randomNodeInTab(Maze* maze);
int getTabId(int x, int y);
int getNumLinks(Maze* maze, int x, int y);
int getDirPossibleN(int x, int y);
int isFinished();

void generationPrep(Maze* maze); // Prepare the maze
void generationInit(Maze* maze); // Initialize the maze
void generationStep(Maze* maze); // Step++
void generationEnding(Maze* maze); // Ending
void generationFinish(Maze* maze); // Finish Cleaning

void generation(Maze* maze); // Full generation

#endif // MAZEGENERATOR_H_INCLUDED
