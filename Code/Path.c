#include "Utils.h"
#include "Maze.h"
#include <math.h>

void generateMouseTree(Maze* maze, int mouseIndex)
{
    int i=0,j,k,test;
    Coords wall,parent;
    Node node;
    Mouse* mouse = maze->mouses[mouseIndex];

    // On part de la position initiale de la souris
    node.x = mouse->coords.x;
    node.y = mouse->coords.y;
    node.test = 0;
    mouse->nodes[0] = node;
    mouse->numNodes = 1;

    if(mouse->coords.x%2==0||mouse->coords.y%2==0)//si les souris ne sont pas initialement dans les nodes
    {
        i++;
        parent.x = node.x;
        parent.y = node.y;
        node.parent = parent;
        if(mouse->coords.x%2==0&&mouse->coords.y%2==0)
        {
            node.x=node.x-1;
            node.y=node.y-1;
        }
        if(mouse->coords.x%2==0&&mouse->coords.y%2==1)
        {
            node.x=node.x-1;
            node.y=node.y;
        }
        if(mouse->coords.x%2==1&&mouse->coords.y%2==0)
        {
            node.x=node.x;
            node.y=node.y-1;
        }
        mouse->nodes[mouse->numNodes]=node;
        mouse->numNodes++;
    }



    // On crée le labyrinthe
    do
    {
        // On définit le parent
        parent.x = mouse->nodes[i].x;
        parent.y = mouse->nodes[i].y;
        for (j = 0; j < 4; j++)
        {
            // On crée la node enfant
            node.parent = parent;
            node.x = parent.x;
            node.y = parent.y;
            if (j == North)
            {
                node.y -= 2;
            }
            if (j == West)
            {
                node.x -= 2;
            }
            if (j == South)
            {
                node.y += 2;
            }
            if (j == East)
            {
                node.x += 2;
            }
            //on teste si elle est dans le labyrinth
            if(node.y>=0 && node.y<=17 && node.x>=0 && node.x<=23)
            {
                // On teste si elle existe deja
                test = 0; // Non contenu
                for (k = 0; k < mouse->numNodes; k++)
                {
                    if (mouse->nodes[k].x == node.x && mouse->nodes[k].y == node.y)
                    {
                        test = 1; // Contenu -> Donc on ajoutera pas
                    }
                }
                // On teste si on a un mur sur le chemin
                wall.x = parent.x;
                wall.y = parent.y;
                if (j == North)
                {
                    wall.y--;
                }
                if (j == West)
                {
                    wall.x--;
                }
                if (j == South)
                {
                    wall.y++;
                }
                if (j == East)
                {
                    wall.x++;
                }


                if (test == 0 && getMazeId(maze,wall.x,wall.y) < Mur) // Non contenu et pas mur
                {
                    // Si c'est bon on ajoute dans la liste des noeuds
                    mouse->nodes[mouse->numNodes] = node;
                    mouse->nodes[mouse->numNodes].test=0;
                    /*printf("\n\n %d %d\n",mouse->nodes[i+1].x,mouse->nodes[i+1].y);*/
                    mouse->numNodes++;
                }
            }

        }
        i++;
    }
    while(i<=mouse->numNodes);

    findTarget(maze,mouse);
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


void moveToMouse(Maze* maze,Cat* cat)
{
    int moved = 0;

    // Descendre
    if (cat->coords.x == cat->dest.x && cat->coords.y < cat->dest.y && getMazeId(maze,cat->coords.x,cat->coords.y + 1) < Mur)
    {
        SetCatPosition(cat,cat->coords.x,cat->coords.y + 1);
        moved = 1;
    }
    // Monter
    if (cat->coords.x == cat->dest.x && cat->coords.y > cat->dest.y && getMazeId(maze,cat->coords.x,cat->coords.y - 1) < Mur)
    {
        SetCatPosition(cat,cat->coords.x,cat->coords.y - 1);
        moved = 1;
    }
    // Droite
    if (cat->coords.x < cat->dest.x && cat->coords.y == cat->dest.y && getMazeId(maze,cat->coords.x + 1,cat->coords.y) < Mur)
    {
        SetCatPosition(cat,cat->coords.x + 1,cat->coords.y);
        moved = 1;
    }
    // Gauche
    if (cat->coords.x > cat->dest.x && cat->coords.y == cat->dest.y && getMazeId(maze,cat->coords.x - 1,cat->coords.y) < Mur)
    {
        SetCatPosition(cat,cat->coords.x - 1,cat->coords.y);
        moved = 1;
    }

    // La souris est en diagonal
    if (moved == 0)
    {
        // Souris en HautGauche
        if (cat->coords.x > cat->dest.x && cat->coords.y > cat->dest.y && moved == 0)
        {
            if (getMazeId(maze,cat->coords.x-1,cat->coords.y) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x-1,cat->coords.y);
                moved = 1;
            }
            if (getMazeId(maze,cat->coords.x,cat->coords.y-1) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x,cat->coords.y-1);
                moved = 1;
            }
        }
        // Souris en HautDroite
        if (cat->coords.x < cat->dest.x && cat->coords.y > cat->dest.y && moved == 0)
        {
            if (getMazeId(maze,cat->coords.x+1,cat->coords.y) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x+1,cat->coords.y);
                moved = 1;
            }
            if (getMazeId(maze,cat->coords.x,cat->coords.y-1) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x,cat->coords.y-1);
                moved = 1;
            }
        }
        // Souris en BasGauche
        if (cat->coords.x > cat->dest.x && cat->coords.y < cat->dest.y && moved == 0)
        {
            if (getMazeId(maze,cat->coords.x-1,cat->coords.y) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x-1,cat->coords.y);
                moved = 1;
            }
            if (getMazeId(maze,cat->coords.x,cat->coords.y+1) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x,cat->coords.y+1);
                moved = 1;
            }
        }
        // Souris en BasDroite
        if (cat->coords.x < cat->dest.x && cat->coords.y < cat->dest.y && moved == 0)
        {
            if (getMazeId(maze,cat->coords.x+1,cat->coords.y) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x+1,cat->coords.y);
                moved = 1;
            }
            if (getMazeId(maze,cat->coords.x,cat->coords.y+1) < Mur && moved == 0)
            {
                SetCatPosition(cat,cat->coords.x,cat->coords.y+1);
                moved = 1;
            }
        }
    }

}

void findTarget(Maze* maze,Mouse* mouse)//trouver la prochaine node
{
    int i,j;
    Cheese* cheese = maze->cheeses[0];
    Node tab[4];
    int numNodesPossibilities = 0;
    // On actualise notre position de départ (node actual)
    for (i = 0; i < mouse->numNodes; i++)
    {
        if (mouse->nodes[i].x == mouse->coords.x && mouse->nodes[i].y == mouse->coords.y)
        {
            mouse->start = mouse->nodes[i];
        }
    }

    // on trouve les enfants de cette node
    for(j = 0; j < mouse->numNodes; j++)
    {
        if (mouse->nodes[j].parent.x == mouse->start.x&&mouse->nodes[j].parent.y==mouse->start.y&&mouse->nodes[j].test==0)
        {
            tab[numNodesPossibilities] = mouse->nodes[j];
            numNodesPossibilities++;
        }
    }

    // On va choisir la node de destination maintenant
    if (numNodesPossibilities > 0)
    {
        mouse->dest = tab[0];
        //on le 'ferme'
        for(j = 0; j < mouse->numNodes; j++)
        {
            if (mouse->nodes[j].x == mouse->dest.x&&mouse->nodes[j].y==mouse->dest.y)
            {
                mouse->nodes[j].test= 1;
            }
        }
    }


    if(numNodesPossibilities==0)// c'est un chemin mort, pour retourner, on prend son parent
    {
        for(j = 0; j < mouse->numNodes; j++)
        {
            if (mouse->nodes[j].x == mouse->start.parent.x&&mouse->nodes[j].y==mouse->start.parent.y)
            {
                mouse->dest=mouse->nodes[j];
            }
        }
    }


    printf("p : %d\n",numNodesPossibilities);
}


void nextMoveMouse(Maze* maze, int mouseIndex)
{
    Mouse* mouse = maze->mouses[mouseIndex];
    int test = 0, chat = 0, moved = 0;
    int i,j,k;
    // La node de destination a été fixé et donc on y va

    /*
    //on test si le souris obtient le fromage
    for(i = 0; i < maze->numCheeses; i++)
    {
        if(mouse->coords.x == maze->cheeses[i]->coords.x && mouse->coords.y == maze->cheeses[i]->coords.y)
        {
            test = 1;
        }
    }
    */

    //on test si le souris ranvontre le chat
    for(i = 0; i < maze->numCats; i++)
    {
        if(mouse->coords.x == maze->cats[i]->coords.x && mouse->coords.y == maze->cats[i]->coords.y)
        {
            test = 1;
        }
    }


    if(test == 0) // si on n'a pas encore trouve le fromage
    {
        for(j = 0; j < maze->numCats; j++)//on determine s'il y a du chat autour des souris
        {
            if(mouse->dest.x > mouse->coords.x)
            {
                if(maze->cats[j]->coords.x == mouse->coords.x+2 && maze->cats[j]->coords.y == mouse->coords.y)
                {
                    chat=1;
                }
                if(maze->cats[j]->coords.x == mouse->coords.x+1 && mouse->coords.y == maze->cats[j]->coords.y)
                {
                    chat=1;
                }
                for(i = 0; i < maze->numCheeses; i++)
                {
                    if(maze->cheeses[i]->coords.x == mouse->coords.x+1&&maze->cheeses[i]->coords.y == mouse->coords.y)
                    {
                        chat=0;
                    }
                }
            }

            if(mouse->dest.y > mouse->coords.y)
            {
                if(maze->cats[j]->coords.x == mouse->coords.x && maze->cats[j]->coords.y == mouse->coords.y+2)
                {
                    chat=1;
                }
                if(maze->cats[j]->coords.x == mouse->coords.x && maze->cats[j]->coords.y == mouse->coords.y+1)
                {
                    chat=1;
                }
                for(i = 0; i < maze->numCheeses; i++)
                {
                    if(maze->cheeses[i]->coords.x == mouse->coords.x && maze->cheeses[i]->coords.y == mouse->coords.y+1)
                    {
                        chat=0;
                    }
                }
            }

            if(mouse->dest.x < mouse->coords.x)
            {
                if(maze->cats[j]->coords.x == mouse->coords.x-2 && mouse->coords.y == maze->cats[j]->coords.y)
                {
                    chat=1;
                }
                if(maze->cats[j]->coords.x==mouse->coords.x-1&&mouse->coords.y==maze->cats[j]->coords.y)
                {
                    chat=1;
                }
                for(i = 0; i < maze->numCheeses; i++)
                {
                    if(maze->cheeses[i]->coords.x == mouse->coords.x-1 && maze->cheeses[i]->coords.y == mouse->coords.y)
                    {
                        chat=0;
                    }
                }
            }

            if(mouse->dest.y < mouse->coords.y)
            {
                if(maze->cats[j]->coords.x == mouse->coords.x && maze->cats[j]->coords.y == mouse->coords.y-2)
                {
                    chat=1;
                }
                if(maze->cats[j]->coords.x == mouse->coords.x && maze->cats[j]->coords.y == mouse->coords.y-1)
                {
                    chat=1;
                }
                for(i = 0; i < maze->numCheeses; i++)
                {
                    if(maze->cheeses[i]->coords.x == mouse->coords.x && maze->cheeses[i]->coords.y == mouse->coords.y-1)
                    {
                        chat=0;
                    }
                }
            }
        }

        if(chat==1)//si le souris va renvontrer le chat, il retourne
        {
            for(k = 0; k < mouse->numNodes; k++)//on ouvre tous les chemins fermés sauf celui de node actuel
            {
                if(mouse->nodes[k].x != mouse->dest.x && mouse->nodes[k].y != mouse->dest.y)
                {
                    mouse->nodes[k].test = 0;
                }
            }

            //on trouve le parent de mouse->dest
            for(k = 0; k < mouse->numNodes; k++)
            {
                if (mouse->nodes[k].x == mouse->dest.parent.x && mouse->nodes[k].y == mouse->dest.parent.y)
                {
                    mouse->dest = mouse->nodes[k];
                }
            }
            chat=0;
        }
        else
        {
            //s'il y a le fromage juste a cote, on le mange
            for(i = 0; i < maze->numCheeses; i++)
            {
                if(mouse->coords.x+1 == maze->cheeses[i]->coords.x && mouse->coords.y == maze->cheeses[i]->coords.y)
                {
                    SetMousePosition(mouse,mouse->coords.x+1,mouse->coords.y);
                    moved=1;
                }
                if(mouse->coords.x-1 == maze->cheeses[i]->coords.x && mouse->coords.y == maze->cheeses[i]->coords.y)
                {
                    SetMousePosition(mouse,mouse->coords.x-1,mouse->coords.y);
                    moved=1;
                }
                if(mouse->coords.x == maze->cheeses[i]->coords.x && mouse->coords.y+1 == maze->cheeses[i]->coords.y)
                {
                    SetMousePosition(mouse,mouse->coords.x,mouse->coords.y+1);
                    moved=1;
                }
                if(mouse->coords.x == maze->cheeses[i]->coords.x && mouse->coords.y-1 == maze->cheeses[i]->coords.y)
                {
                    SetMousePosition(mouse,mouse->coords.x,mouse->coords.y-1);
                    moved=1;
                }

            }
            if(moved==0)
            {
                moveToTarget(mouse);
            }
        }


        if (mouse->coords.x == mouse->dest.x && mouse->coords.y == mouse->dest.y) // Si on est sur la node de destination
        {
            findTarget(maze,mouse);
        }
    }
}

void nextMoveCat(Maze* maze, int catIndex)
{
    Cat* chat = maze->cats[catIndex];
    int i;

    // On teste s'il y a une souris a cote d'un chat
    for(i = 0; i < maze->numMouses; i++)
    {
        // D = 2
        if ((maze->mouses[i]->coords.x == chat->coords.x+2 && maze->mouses[i]->coords.y == chat->coords.y && getMazeId(maze,chat->coords.x+1,chat->coords.y)< Mur)
        || (maze->mouses[i]->coords.x == chat->coords.x-2 && maze->mouses[i]->coords.y == chat->coords.y && getMazeId(maze,chat->coords.x-1,chat->coords.y)< Mur)
        || (maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y+2 && getMazeId(maze,chat->coords.x,chat->coords.y+1)< Mur)
        || (maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y-2 && getMazeId(maze,chat->coords.x,chat->coords.y-1)< Mur))
        {
            chat->mouse=maze->mouses[i];
        }

        // D = diag
        if ((maze->mouses[i]->coords.x == chat->coords.x+1 && maze->mouses[i]->coords.y == chat->coords.y+1)
        || (maze->mouses[i]->coords.x == chat->coords.x-1 && maze->mouses[i]->coords.y == chat->coords.y-1)
        || (maze->mouses[i]->coords.x == chat->coords.x+1 && maze->mouses[i]->coords.y == chat->coords.y-1)
        || (maze->mouses[i]->coords.x == chat->coords.x-1 && maze->mouses[i]->coords.y == chat->coords.y+1))
        {
            chat->mouse=maze->mouses[i];
        }

        // D = 1
        if ((maze->mouses[i]->coords.x == chat->coords.x+1 && maze->mouses[i]->coords.y == chat->coords.y)
        || (maze->mouses[i]->coords.x == chat->coords.x-1 && maze->mouses[i]->coords.y == chat->coords.y)
        || (maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y-1)
        || (maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y+1))
        {
            chat->mouse=maze->mouses[i];
        }
    }

    // S'il y a une souris, le chat la suit
    if (chat->mouse != NULL)
    {
        i = abs(chat->mouse->coords.x - chat->coords.x) + abs(chat->mouse->coords.y - chat->coords.y);
        if (i > 4)
        {
            chat->mouse == NULL;
        }
        else
        {
            chat->dest.x = chat->mouse->coords.x;
            chat->dest.y = chat->mouse->coords.y;
            moveToMouse(maze,chat);
        }
    }
}


void RemoveCheeseFromMaze(Maze* maze,int cheeseIndex)
{
    Cheese* cheese = maze->cheeses[cheeseIndex];
    int i,j;
    for(i = 0; i < maze->numMouses; i++)
    {
        if(cheese->coords.x == maze->mouses[i]->coords.x && cheese->coords.y == maze->mouses[i]->coords.y)
        {
            for(j = cheeseIndex; j < maze->numCheeses; j++)
            {
                maze->cheeses[j]=maze->cheeses[j+1];
            }
            maze->cheeses[maze->numCheeses-1] = NULL;
            maze->numCheeses--;
        }
    }
}


void RemoveMouseFromMaze(Maze* maze, int mouseIndex)
{
    Mouse* mouse = maze->mouses[mouseIndex];
    int i,j;
    for(i = 0;i < maze->numCats;i++)
    {
        if(maze->cats[i]->coords.x == mouse->coords.x && maze->cats[i]->coords.y == mouse->coords.y)
        {
            for(j = mouseIndex; j < maze->numMouses; j++)
            {
                maze->mouses[j] = maze->mouses[j+1];
            }
            maze->mouses[maze->numMouses-1] = NULL;
            maze->numMouses--;
        }
    }
}
