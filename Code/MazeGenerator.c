#include "Utils.h"
#include "Maze.h"

static SDL_Point gen_tab[100];
static int gen_numPoints;
static int gen_lastStep;

int isWallNode(int x, int y)
{
    return (x%2==0 && y%2==0) ? 1 : 0;
}

int isBorder(int x, int y)
{
    return (x == 0 || y == 0 || x == TILE_WIDTH-1 || y == TILE_HEIGHT-1) ? 1 : 0;
}

int randomNodeInTab(Maze* maze)
{
    SDL_Point p;
    int o = 0;
    int i, ok = 0;
    do
    {
        i = randomInt(0,gen_numPoints);
        p = gen_tab[i];
        o++;
        if (o >= 100)
        {
            ok = 1;
        }
        if (getNumLinks(maze,p.x,p.y) == 1 && getDirPossibleN(p.x,p.y) > 0)
        {
            ok = 1;
        }
    } while (ok == 0);

    if (o >= 1000)
    {
        return -1;
    }

    return i;
}

int getTabId(int x, int y)
{
    int i;
    for (i = 0; i < gen_numPoints; i++)
    {
        if (gen_tab[i].x == x && gen_tab[i].y == y)
        {
            return i;
        }
    }
    return -1;
}

int getNumLinks(Maze* maze, int x, int y)
{
    int nbl = 0;
    if (getMazeId(maze,x,y-1) >= Mur)
    {
        nbl++;
    }
    if (getMazeId(maze,x-1,y) >= Mur)
    {
        nbl++;
    }
    if (getMazeId(maze,x,y+1) >= Mur)
    {
        nbl++;
    }
    if (getMazeId(maze,x+1,y) >= Mur)
    {
        nbl++;
    }
    return nbl;
}

int getDirPossibleN(int x, int y)
{
    int dirPossibleN = 0;
    if (getTabId(x,y-2) == -1 && !isBorder(x,y-2))
    {
        dirPossibleN++;
    }
    if (getTabId(x-2,y) == -1 && !isBorder(x-2,y))
    {
        dirPossibleN++;
    }
    if (getTabId(x,y+2) == -1 && !isBorder(x,y+2))
    {
        dirPossibleN++;
    }
    if (getTabId(x+2,y) == -1 && !isBorder(x+2,y))
    {
        dirPossibleN++;
    }
    return dirPossibleN;
}

int isFinished()
{
    return (gen_numPoints >= 88) ? 1 : 0;
}

void generationPrep(Maze* maze)
{
    int i;
    SDL_Point p;
    if (!maze)
    {
        return;
    }

    // Remove last init
    for (i = 0; i < 100; i++)
    {
        gen_tab[i].x = 0;
        gen_tab[i].y = 0;
    }
    gen_numPoints = 0;
    gen_lastStep = 0;

    // Init
    for (p.x = 0; p.x < maze->size.x; p.x++)
    {
        for (p.y = 0; p.y < maze->size.y; p.y++)
        {
            // Si bords ou mur
            if (p.x == 0 || p.y == 0 || p.x == maze->size.x-1 || p.y == maze->size.y-1 || isWallNode(p.x,p.y))
            {
                setMazeId(maze,p.x,p.y,Mur);
            }
            else // Sinon
            {
                setMazeId(maze,p.x,p.y,Vide);
            }
        }
    }

    gen_numPoints = 0;
}

void generationInit(Maze* maze)
{
    SDL_Point px1,px2,py1,py2;

    if (!maze)
    {
        return;
    }

    // Take a random node on the top axe
    px1.y = 2;
    do
    {
        px1.x = randomInt(3,maze->size.x - 5);
    } while (!isWallNode(px1.x,px1.y));
    setMazeId(maze,px1.x,px1.y,MurC);
    setMazeId(maze,px1.x,px1.y-1,Mur);

    // Take a random node on the bottom axe
    px2.y = maze->size.y - 3;
    do
    {
        px2.x = randomInt(3,maze->size.x - 5);
    } while (!isWallNode(px2.x,px2.y));
    setMazeId(maze,px2.x,px2.y,MurC);
    setMazeId(maze,px2.x,px2.y+1,Mur);

    // Take a random node on the left axe
    py1.x = 2;
    do
    {
        py1.y = randomInt(1,maze->size.y - 3);
    } while (!isWallNode(py1.x,py1.y));
    setMazeId(maze,py1.x,py1.y,MurC);
    setMazeId(maze,py1.x-1,py1.y,Mur);

    // Take a random node on the right axe
    py2.x = maze->size.x - 3;
    do
    {
        py2.y = randomInt(1,maze->size.y - 3);
    } while (!isWallNode(py2.x,py2.y));
    setMazeId(maze,py2.x,py2.y,MurC);
    setMazeId(maze,py2.x+1,py2.y,Mur);

    // Add the node to the tab
    gen_tab[0] = px1;
    gen_tab[1] = px2;
    gen_tab[2] = py1;
    gen_tab[3] = py2;
    gen_numPoints = 4;
}

void generationStep(Maze* maze)
{
    if (isFinished())
    {
        return;
    }

    // On efface les points mis en valeur lors de la dernière action
    int i = 0;
    for (i = 0; i < gen_numPoints; i++)
    {
        setMazeId(maze,gen_tab[i].x,gen_tab[i].y,Mur);
    }

    if (gen_lastStep == 0)
    {
        // Séléction d'une case non utilisée
        int id = randomNodeInTab(maze);

        if (id >= 0) // Si on a une id valide
        {
            SDL_Point p = gen_tab[id];
            setMazeId(maze,p.x,p.y,MurB);

            // On obtient le nombre de node non connectée accessible depuis ce point
            int dirPossibleT[4];
            for (i = 0; i < 4; i++)
            {
                dirPossibleT[i] = 0;
            }
            if (getTabId(p.x,p.y-2) == -1 && !isBorder(p.x,p.y-2))
            {
                dirPossibleT[North] = 1;
            }
            if (getTabId(p.x-2,p.y) == -1 && !isBorder(p.x-2,p.y))
            {
                dirPossibleT[West] = 1;
            }
            if (getTabId(p.x,p.y+2) == -1 && !isBorder(p.x,p.y+2))
            {
                dirPossibleT[South] = 1;
            }
            if (getTabId(p.x+2,p.y) == -1 && !isBorder(p.x+2,p.y))
            {
                dirPossibleT[East] = 1;
            }

            // On détermine un nombre de direction a creer
            int nbc = randomInt(0,getDirPossibleN(p.x,p.y));

            // On les cree
            for (i = 0; i < nbc; i++)
            {
                int r = randomInt(North,East);
                if (dirPossibleT[r] == 1)
                {
                    if (r == North)
                    {
                        setMazeId(maze,p.x,p.y-1,Mur);
                        setMazeId(maze,p.x,p.y-2,MurA);
                        gen_tab[gen_numPoints].x = p.x;
                        gen_tab[gen_numPoints].y = p.y-2;
                    }
                    if (r == West)
                    {
                        setMazeId(maze,p.x-1,p.y,Mur);
                        setMazeId(maze,p.x-2,p.y,MurA);
                        gen_tab[gen_numPoints].x = p.x-2;
                        gen_tab[gen_numPoints].y = p.y;
                    }
                    if (r == South)
                    {
                        setMazeId(maze,p.x,p.y+1,Mur);
                        setMazeId(maze,p.x,p.y+2,MurA);
                        gen_tab[gen_numPoints].x = p.x;
                        gen_tab[gen_numPoints].y = p.y+2;
                    }
                    if (r == East)
                    {
                        setMazeId(maze,p.x+1,p.y,Mur);
                        setMazeId(maze,p.x+2,p.y,MurA);
                        gen_tab[gen_numPoints].x = p.x+2;
                        gen_tab[gen_numPoints].y = p.y;
                    }
                    dirPossibleT[r] = 0;
                    gen_numPoints++;
                }
            }
        }
        else // s'il ne reste plus de case possible
        {
            printf("error : maze generation");
        }
    }
}

void generationFinish(Maze* maze)
{
    int i,j;
    for (i = 0; i < maze->size.x; i++)
    {
        for (j = 0; j < maze->size.y; j++)
        {
            if (getMazeId(maze,i,j) >= Mur)
            {
                setMazeId(maze,i,j,randomInt(MurA,MurF));
            }
            else
            {
                setMazeId(maze,i,j,randomInt(A,D));
            }
        }
    }
}

void generation(Maze* maze)
{
    generationPrep(maze);
    generationInit(maze);
    while (!isFinished())
    {
        generationStep(maze);
    }
    generationFinish(maze);
}
