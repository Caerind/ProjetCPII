#include "Utils.h"
#include "Maze.h"

void generateMouseTree(Maze* maze, int mouseIndex)
{
    int i,j,k,test;
    Coords wall;
    Node node,parent;
    Mouse* mouse = maze->mouses[mouseIndex];

    // On part de la position initiale de la souris
    // TODO : Actually we assume that the mouse in on a node
    node.x = mouse->coords.x;
    node.y = mouse->coords.y;
    node.parent = NULL;
    mouse->nodes[0] = node;
    mouse->numNodes = 1;

    // On crée le labyrinthe
    for (i = 0; i < mouse->numNodes; i++)
    {
        parent = mouse->nodes[i]; // On définit le parent
        for (j = 0; j < 4; j++)
        {
            // On crée la node enfant
            node.parent = &parent;
            node.x = parent.x;
            node.y = parent.y;
            if (j == North){node.y -= 2;}
            if (j == West){node.x -= 2;}
            if (j == South){node.y += 2;}
            if (j == East){node.x += 2;}

            // On teste si elle existe deja
            test = 0; // Non contenu
            for (k = 0; k < mouse->numNodes;k++)
            {
                if (mouse->nodes[k].x == node.x && mouse->nodes[k].y == node.y)
                {
                    test = 1; // Contenu -> Donc on ajoutera pas
                }
            }

            // On teste si on a un mur sur le chemin
            wall.x = parent.x;
            wall.y = parent.y;
            if (j == North){wall.y--;}
            if (j == West){wall.x--;}
            if (j == South){wall.y++;}
            if (j == East){wall.x++;}

            if (test == 0 && getMazeId(maze,wall.x,wall.y) < Mur) // Non contenu et pas mur
            {
                // Si c'est bon on ajoute dans la liste des noeuds
                mouse->nodes[i] = node;
                mouse->numNodes++;
            }
        }
    }
findDest(maze,mouse);

    printf("mouse pos : %d %d\n",mouse->coords.x,mouse->coords.y);
    printf("start : %d %d\n",mouse->start.x,mouse->start.y);
    printf("dest : %d %d\n",mouse->dest.x, mouse->dest.y);

}

void moveToTarget(Mouse* mouse)
{
    // Descendre
    if (mouse->coords.x == mouse->dest.x && mouse->coords.y < mouse->dest.y)
    {
        SetMousePosition(mouse,mouse->coords.x,mouse->coords.y + 1);
    }
    // Monter
    if (mouse->coords.x == mouse->dest.x && mouse->coords.y > mouse->dest.y)
    {
        SetMousePosition(mouse,mouse->coords.x,mouse->coords.y - 1);
    }
    // Droite
    if (mouse->coords.x < mouse->dest.x && mouse->coords.y == mouse->dest.y)
    {
        SetMousePosition(mouse,mouse->coords.x + 1,mouse->coords.y);
    }
    // Gauche
    if (mouse->coords.x > mouse->dest.x && mouse->coords.y == mouse->dest.y)
    {
        SetMousePosition(mouse,mouse->coords.x - 1,mouse->coords.y);
    }
}


void findDest(Maze* maze, Mouse* mouse)
{

    int i,j;
    Cheese* cheese = maze->cheeses[0]; // TODO : Get Nearest Cheese
    int dx = cheese->coords.x - mouse->coords.x;
    int dy = cheese->coords.y - mouse->coords.y;
    Coords coords,wall;
    Node tab[4];
    int numNodesPossibilities = 0;

    // On actualise notre position de départ
    for (i = 0; i < mouse->numNodes; i++)
    {
        if (mouse->nodes[i].x == mouse->coords.x && mouse->nodes[i].y == mouse->coords.y)
        {
            mouse->start = mouse->nodes[i];
        }
    }
// On liste les nodes possibles depuis cette position
    for (i = 0; i < 4; i++)
    {
        // On teste si on a un mur sur le chemin
        wall.x = mouse->start.x;
        wall.y = mouse->start.y;
        if (j == North){wall.y--;}
        if (j == West){wall.x--;}
        if (j == South){wall.y++;}
        if (j == East){wall.x++;}

        if (getMazeId(maze,wall.x,wall.y) < Mur) // pas mur
        {
            // On paramètre la destination possible
            coords.x = mouse->start.x;
            coords.y = mouse->start.y;
            if (i == North){coords.y -= 2;}
            if (i == West){coords.x -= 2;}
            if (i == South){coords.y += 2;}
            if (i == East){coords.x += 2;}

            // On l'ajoute à la liste
            for (j = 0; j < mouse->numNodes; j++)
            {
                if (mouse->nodes[j].x == coords.x && mouse->nodes[j].y == coords.y)
                {
                    tab[numNodesPossibilities] = mouse->nodes[j];
                    numNodesPossibilities++;
                }
            }
        }
    }


    // On va choisir la node de destination maintenant
    if (numNodesPossibilities == 1)
    {
        mouse->dest = tab[0];
    }
    if (numNodesPossibilities == 2)
    {


    }
    printf("p : %d\n",numNodesPossibilities);
}

void findTarget(Maze* maze,Mouse* mouse)//trouve la prochaine node
{
    int i,j;
    Cheese* cheese = maze->cheeses[0]; // TODO : Get Nearest Cheese
    int dx = cheese->coords.x - mouse->coords.x;
    int dy = cheese->coords.y - mouse->coords.y;
    Node tab[4];
    int numNodesPossibilities = 0;
    // On actualise notre position de départ
    for (i = 0; i < mouse->numNodes; i++)
    {
        if (mouse->nodes[i].x == mouse->coords.x && mouse->nodes[i].y == mouse->coords.y)
        {
            mouse->start = mouse->nodes[i];
        }
    }

    //*on trouve les enfants de cette node
    for(j = 0; j < mouse->numNodes; j++)
    {
        if (mouse->nodes[j].parent->x == mouse->start.x && mouse->nodes[j].parent->y == mouse->start.y)
                {
                    tab[numNodesPossibilities] = mouse->nodes[j];
                    numNodesPossibilities++;
                }
    }

    // On va choisir la node de destination maintenant
    if (numNodesPossibilities == 1)
    {
        mouse->dest = tab[0];
    }
    if (numNodesPossibilities == 2)
    {


    }
    printf("p : %d\n",numNodesPossibilities);



}


void nextMoveMouse(Maze* maze, int mouseIndex)
{
    Mouse* mouse = maze->mouses[mouseIndex];

    moveToTarget(mouse); // La node de destination a été fixé et donc on y va

    if (mouse->coords.x == mouse->dest.x && mouse->coords.y == mouse->dest.y) // Si on est sur la node de destination
    {
        // On doit trouver la prochaine node
        findTarget(maze,mouse);




        /*
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
            if (mouse->nodes[i].x == n.x && mouse->nodes[i].y == n.y)
            {
                mouse->target = mouse->nodes[i];
            }
        }
        */
    }
}

void nextMoveCat(Maze* maze, int catIndex)
{

}
