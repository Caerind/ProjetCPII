#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "Structs.h"

// Cr�er le labyrinthe dans la m�moire de la souris
void generateMouseTree(Maze* maze, int mouseIndex);

// D�place la soruis vers sa destination
void moveToTarget(Mouse* mouse);

// D�place le chat dans la direction de la souris qu'il cible
void moveToMouse(Cat* cat);

// Permet � la souris de trouver sa prochaine destination
void findTarget(Maze* maze, Mouse* mouse);

// D�place une souris
void nextMoveMouse(Maze* maze, int mouseIndex);

// D�place un chat
void nextMoveCat(Maze* maze, int catIndex);

#endif // PATH_H_INCLUDED
