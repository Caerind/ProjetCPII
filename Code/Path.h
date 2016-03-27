#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "Structs.h"

void generateMouseTree(Maze* maze, int mouseIndex);
void moveToTarget(Mouse* mouse);
void moveToMouse(Cat* cat);
void findTarget(Maze* maze,Mouse* mouse);//trouver la prochaine node
void nextMoveMouse(Maze* maze, int mouseIndex);
void nextMoveCat(Maze* maze, int catIndex);
void RemoveCheeseFromMaze(Maze* maze, int cheeseIndex);
void RemoveMouseFromMaze(Maze* maze, int mouseIndex);

#endif // PATH_H_INCLUDED
