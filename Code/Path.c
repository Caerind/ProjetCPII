#include "Utils.h"
#include "Maze.h"

void nextMoveMouse(Maze* maze, int mouseIndex)
{
    Mouse* mouse = maze->mouses[mouseIndex];
    Cheese* cheese = maze->cheeses[0]; // TODO : Get Nearest Cheese
    int dx = cheese->coords.x - mouse->coords.x;
    int dy = cheese->coords.y - mouse->coords.y;

    // Descendre
    if (mouse->coords.x == mouse->target.x && mouse->coords.y < mouse->target.y)
    {
        SetMousePosition(mouse,mouse->coords.x,mouse->coords.y+1);
    }
    // Monter
    if (mouse->coords.x == mouse->target.x && mouse->coords.y > mouse->target.y)
    {
        SetMousePosition(mouse,mouse->coords.x,mouse->coords.y-1);
    }
    // Droite
    if (mouse->coords.x < mouse->target.x && mouse->coords.y == mouse->target.y)
    {
        SetMousePosition(mouse,mouse->coords.x + 1,mouse->coords.y);
    }
    // Gauche
    if (mouse->coords.x > mouse->target.x && mouse->coords.y == mouse->target.y)
    {
        SetMousePosition(mouse,mouse->coords.x - 1,mouse->coords.y);
    }


    // Calcul mouvement prochain
    if (mouse->coords.x == mouse->target.x && mouse->coords.y == mouse->target.y)
    {
        int dirP[4];
        int nDirP = 0;
        int i;
        for (i = North; i < DirCount; i++)
        {
            if ((i == North && getMazeId(maze,mouse->coords.x,mouse->coords.y-1) == 0)
                    || (i == West && getMazeId(maze,mouse->coords.x-1,mouse->coords.y) == 0)
                    || (i == South && getMazeId(maze,mouse->coords.x,mouse->coords.y+1) == 0)
                    || (i == East && getMazeId(maze,mouse->coords.x+1,mouse->coords.y) == 0))
            {
                dirP[nDirP] = i;
                nDirP++;
            }
        }

        int directionChoisie = 4;

        if (nDirP == 1)
        {
            directionChoisie = dirP[0];
        }
        else // cas plusieurs directions possible
        {
            // choisir une direction
        }

        Coords n;
        n.x = mouse->coords.x;
        n.y = mouse->coords.y;
        switch (directionChoisie)
        {
            case North :
                n.y -= 2;
                break;
            case West:
                n.x -= 2;
                break;
            case South:
                n.y += 2;
                break;
            case East:
                n.x += 2;
                break;
            default:
                break;
        }

        for (i = 0; i < mouse->numNodes;i++)
        {
            if (mouse->nodes[i].x == n.x && mouses->nodes[i].y == n.y)
            {
                mouse->target = mouse->nodes[i];
            }
        }
    }
}
