#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "Structs.h"

// Créer le labyrinthe dans la mémoire de la souris
void generateMouseTree(Maze* maze, int mouseIndex);

// Déplace la soruis vers sa destination
void moveToTarget(Mouse* mouse);

// Déplace le chat dans la direction de la souris qu'il cible
void moveToMouse(Cat* cat);

// Permet à la souris de trouver sa prochaine destination
void findTarget(Maze* maze, Mouse* mouse);

// Déplace une souris
void nextMoveMouse(Maze* maze, int mouseIndex);

// Déplace un chat
void nextMoveCat(Maze* maze, int catIndex);

#endif // PATH_H_INCLUDED
