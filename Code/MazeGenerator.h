#ifndef MAZEGENERATOR_H_INCLUDED
#define MAZEGENERATOR_H_INCLUDED

#include "Structs.h"

int isNode(Maze* maze, Coords c);
int isNodeSide(Maze* maze, Coords c);
int isNodeMiddle(Maze* maze, Coords c);

void fillBorder(Maze* maze, int id);
void fillNodes(Maze* maze);

int addLink(Maze* maze, Coords c);
int addLinkDir(Maze* maze, Coords c, int direction);
int isLinked(Maze* maze, Coords c, int direction);
int linkConnected(Maze* maze, Coords c);
int isConnected(Maze* maze, Coords c);

void generationStep1(Maze* maze); // Prepare the maze
void generationStep2(Maze* maze); // Place the begin
void generationStep3(Maze* maze); // Place unconnected middle node
void generationStep4(Maze* maze); // Place unconnected side node
void generationStep5(Maze* maze); // Remove island
void generationStep6(Maze* maze); // Correction
void generationStep7(Maze* maze); // Finish

void mazeGenerator(Maze* maze); // Generate a full maze

#endif // MAZEGENERATOR_H_INCLUDED
