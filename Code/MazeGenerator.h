#ifndef MAZEGENERATOR_H_INCLUDED
#define MAZEGENERATOR_H_INCLUDED

#include "Structs.h"

// Permet de tester si une coordonnée est une base de mur
int isWallNode(SDL_Point p);

// Permet de tester si une case est un bord
int isBorder(int x, int y);

// Permet de prendre une case au hasard dans le tableau de node
int randomNodeInTab(Maze* maze);

// Permet d'obtenir la valeur d'une node avec une position donnée
int getTabId(int x, int y);

// Permet de savoir combien de lien vers un mur une node a
int getNumLinks(Maze* maze, int x, int y);

// Permet de savoir combien de lien une node de mur peut créer
int getDirPossibleN(int x, int y);

// Permet de savoir si le labyrinthe est terminé
int isFinished();

// Préparation de la génération
void generationPrep(Maze* maze);

// Initialisation de la génération
void generationInit(Maze* maze);

// Faire avancé d'une étape la génération
void generationStep(Maze* maze);

// Texturisation du labyrinthe
void generationFinish(Maze* maze);


// Générer le labyrinthe
void generation(Maze* maze);

#endif // MAZEGENERATOR_H_INCLUDED
