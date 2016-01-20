#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "Structs.h"

// Fonction pour créer un labyrinthe vide de dimension (sizeX,sizeY)
Maze* createMaze(int sizeX,int sizeY);

// Fonction pour détruire un labyrinthe
void destroyMaze(Maze* maze);

// Fonction pour dessiner un labyrinthe
void renderMaze(SDL_Renderer* renderer, Maze* maze);

// Fonction pour remplir un labyrinthe avec un type de case
void fillMaze(Maze* maze, int id);

// Fonction pour récupérer la valeur d'une case d'un labyrinthe
int getMazeId(Maze* maze, int x, int y);

// Fonction pour modifier la valeur d'une case d'un labyrinthe
void setMazeId(Maze* maze, int x, int y, int id);

// Fonction pour charger un labyrinthe depuis un fichier
Maze* loadMazeFromFile(const char* filename);

#endif // MAZE_H_INCLUDED
