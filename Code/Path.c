#include "Utils.h"
#include "Maze.h"

void generateMouseTree(Maze* maze, int mouseIndex)
{
    int i=0,j,k,test,h;
    Coords wall,parent;
    Node node;
    Mouse* mouse = maze->mouses[mouseIndex];

    // On part de la position initiale de la souris
    // TODO : Actually we assume that the mouse in on a node
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



/*void generateCatTree(Maze* maze, int catIndex)
{
    int i=0,j,k,test,h;

    Coords wall,parent;
    Node node;
    Cat* cat = maze->cats[catIndex];

    // On part de la position initiale du chat

    node.x = cat->coords.x;
    node.y = cat->coords.y;
    node.test = 0;
    cat->nodes[0] = node;
    cat->numNodes = 1;

    if(cat->coords.x%2==0||cat->coords.y%2==0)//si les souris ne sont pas initialement dans les nodes
    {
        i++;
        parent.x = node.x;
        parent.y = node.y;
        node.parent = parent;
        if(cat->coords.x%2==0&&cat->coords.y%2==0)
        {
            node.x=node.x-1;
            node.y=node.y-1;
        }
        if(cat->coords.x%2==0&&cat->coords.y%2==1)
        {
            node.x=node.x-1;
            node.y=node.y;
        }
        if(cat->coords.x%2==1&&cat->coords.y%2==0)
        {
            node.x=node.x;
            node.y=node.y-1;
        }
        cat->nodes[cat->numNodes]=node;
        cat->numNodes++;
    }



    // On crée le labyrinthe
    do
    {
        // On définit le parent
        parent.x = cat->nodes[i].x;
        parent.y = cat->nodes[i].y;
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
                for (k = 0; k < cat->numNodes; k++)
                {
                    if (cat->nodes[k].x == node.x && cat->nodes[k].y == node.y)
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
                    cat->nodes[cat->numNodes] = node;
                    cat->nodes[cat->numNodes].test=0;
                    cat->numNodes++;
                }
            }

        }
        i++;
    }
    while(i<=cat->numNodes);

}*/




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
    // Descendre
    if (cat->coords.x == cat->dest.x && cat->coords.y < cat->dest.y)
    {
        if(getMazeId(maze,cat->coords.x,cat->coords.y + 1)< Mur)
        {
            SetCatPosition(cat,cat->coords.x,cat->coords.y + 1);
        }
    }
    // Monter
    if (cat->coords.x == cat->dest.x && cat->coords.y > cat->dest.y)
    {
        if(getMazeId(maze,cat->coords.x,cat->coords.y - 1)< Mur)
        {
            SetCatPosition(cat,cat->coords.x,cat->coords.y - 1);
        }
    }
    // Droite
    if (cat->coords.x < cat->dest.x && cat->coords.y == cat->dest.y)
    {
        if(getMazeId(maze,cat->coords.x + 1,cat->coords.y)< Mur)
        {
            SetCatPosition(cat,cat->coords.x + 1,cat->coords.y);
        }
    }
    // Gauche
    if (cat->coords.x > cat->dest.x && cat->coords.y == cat->dest.y)
    {
        if(getMazeId(maze,cat->coords.x - 1,cat->coords.y)< Mur)
        {
            SetCatPosition(cat,cat->coords.x - 1,cat->coords.y);
        }
    }

}


/*void findDest(Maze* maze, Mouse* mouse)
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

        if (getMazeId(maze,wall.x,wall.y) < Mur) // pas mur
        {
            // On paramètre la destination possible
            coords.x = mouse->start.x;
            coords.y = mouse->start.y;
            if (i == North)
            {
                coords.y -= 2;
            }
            if (i == West)
            {
                coords.x -= 2;
            }
            if (i == South)
            {
                coords.y += 2;
            }
            if (i == East)
            {
                coords.x += 2;
            }

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
}*/


//|dx|>=|dy|->0, 反之->1
int comparer_dx_dy(int dx,int dy)
{
    int x,y;
    if(dx>=0)
        x=dx;
    else
        x=-dx;
    if(dy>=0)
        y=dy;
    else
        y=-dy;
    if(x>=y)
        return 0;
    else
        return 1;
}

void findTarget(Maze* maze,Mouse* mouse)//trouver la prochaine node
{
    int i,j;
    Cheese* cheese = maze->cheeses[0]; // TODO : Get Nearest Cheese
    int dx = cheese->coords.x - mouse->coords.x;
    int dy = cheese->coords.y - mouse->coords.y;
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

    //*on trouve les enfants de cette node
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

    /*if (numNodesPossibilities == 2)
    {
        //on choisit une direction
        if(dx>0&&tab[0].x>mouse->start.x)
        {
            mouse->dest=tab[0];

        }



        mouse->dest = tab[0];





        //on le 'ferme'
        for(j = 0; j < mouse->numNodes; j++)
        {
            if (mouse->nodes[j].x == mouse->dest.x&&mouse->nodes[j].y==mouse->dest.y)
            {
                mouse->nodes[j].test= 1;
            }
        }
    }*/

    /*if (numNodesPossibilities == 2)
    {
        //on enregitre ce node dans le tableau hesitation
        mouse->hesitation[mouse->numHesi]= mouse->start;
        mouse->numHesi++;
        //on prend le 1er direction possible
        // TODO : we choose the most efficase direction
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

    if(numNodesPossibilities==3)
    {
        //on enregitre ce node dans le tableau hesitation
        mouse->hesitation[mouse->numHesi]= mouse->start;
        mouse->numHesi++;
        //on prend le 1er direction possible
        // TODO : we choose the most efficase direction
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

     if(numNodesPossibilities==4)
    {
        //on enregitre ce node dans le tableau hesitation
        mouse->hesitation[mouse->numHesi]= mouse->start;
        mouse->numHesi++;
        //on prend le 1er direction possible
        // TODO : we choose the most efficase direction
        mouse->dest = tab[0];

        //on le 'ferme'
        for(j = 0; j < mouse->numNodes; j++)
        {
            if (mouse->nodes[j].x == mouse->dest.x&&mouse->nodes[j].y==mouse->dest.y)
            {
                mouse->nodes[j].test= 1;
            }
        }

    }*/

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
    int test = 0,chat = 0;
    int i,j,k;
    // La node de destination a été fixé et donc on y va

    //on test si le souris obtient le fromage
    for(i = 0; i < maze->numCheeses; i++)
    {
        if(mouse->coords.x == maze->cheeses[i]->coords.x && mouse->coords.y == maze->cheeses[i]->coords.y)
        {
            test = 1;
        }
    }
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

        if(chat==0)
        {
            moveToTarget(mouse);
        }


        if (mouse->coords.x == mouse->dest.x && mouse->coords.y == mouse->dest.y) // Si on est sur la node de destination
        {
            findTarget(maze,mouse);
        }
        // On doit trouver la prochaine node
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
    Cat *chat = maze->cats[catIndex];

    int i;

    //on test si il y a un souris a cote de chat
    for(i = 0; i < maze->numMouses; i++)
    {

        if(maze->mouses[i]->coords.x == chat->coords.x+2 && maze->mouses[i]->coords.y == chat->coords.y && getMazeId(maze,chat->coords.x+1,chat->coords.y)< Mur)
        {
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x-2 && maze->mouses[i]->coords.y == chat->coords.y && getMazeId(maze,chat->coords.x-1,chat->coords.y)< Mur)
        {
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y+2 && getMazeId(maze,chat->coords.x,chat->coords.y+1)< Mur)
        {
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y-2 && getMazeId(maze,chat->coords.x,chat->coords.y-1)< Mur)
        {
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x+2 && maze->mouses[i]->coords.y == chat->coords.y+1)
        {
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x-1 && maze->mouses[i]->coords.y == chat->coords.y-1)
        {
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x+1 && maze->mouses[i]->coords.y == chat->coords.y-1)
        {

            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x-1 && maze->mouses[i]->coords.y == chat->coords.y+1)
        {
            chat->mouse=maze->mouses[i];
        }


        /*if(maze->mouses[i]->coords.x == chat->coords.x+1 && maze->mouses[i]->coords.y == chat->coords.y )
        {
            souris = 1;
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x-1 && maze->mouses[i]->coords.y == chat->coords.y )
        {
            souris = 1;
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y+1 )
        {
            souris = 1;
            chat->mouse=maze->mouses[i];
        }
        if(maze->mouses[i]->coords.x == chat->coords.x && maze->mouses[i]->coords.y == chat->coords.y-1 )
        {
            souris = 1;
            chat->mouse=maze->mouses[i];
        }*/
    }

    //s'il y a le souris, le chat le suivre
    if(chat->mouse!=NULL)
    {
        chat->dest.x=chat->mouse->coords.x;
        chat->dest.y=chat->mouse->coords.y;
        moveToMouse(maze,chat);
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
                for(j=cheeseIndex; j < maze->numCheeses; j++)
                {
                    maze->cheeses[j]=maze->cheeses[j+1];
                }
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
                for(j=mouseIndex; j < maze->numMouses; j++)
                {
                    maze->mouses[j]=maze->cheeses[j+1];
                }
                maze->numMouses--;
            }
        }
    }



