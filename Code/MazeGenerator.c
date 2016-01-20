#include "Utils.h"
#include "Maze.h"

int isNode(Maze* maze, Coords c)
{
    if ((c.x+1) % 2 == 0 && (c.y+1) % 2 == 0)
    {
        return 1;
    }
    return 0;
}

int isNodeSide(Maze* maze, Coords c)
{
    if (maze != NULL)
    {
        if (isNode(maze,c) == 1)
        {
            if (c.x == 1 || c.x == maze->size.x-2 || c.y == 1 || c.y == maze->size.y-2)
            {
                return 1;
            }
        }
    }
    return 0;
}

int isNodeMiddle(Maze* maze, Coords c)
{
    if (maze != NULL)
    {
        if (isNode(maze,c) == 1)
        {
            if (isNodeSide(maze,c) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

void fillBorder(Maze* maze, int id)
{
    int i;
    if (maze != NULL)
    {
        for (i = 0; i < maze->size.x; i++)
        {
            setMazeId(maze,i,0,id);
            setMazeId(maze,i,maze->size.y-1,id);
        }
        for (i = 0; i < maze->size.y; i++)
        {
            setMazeId(maze,0,i,id);
            setMazeId(maze,maze->size.x-1,i,id);
        }
    }
}

void fillNodes(Maze* maze)
{
    Coords c;
    if (maze != NULL)
    {
        for (c.y = 0; c.y < maze->size.y; c.y++)
        {
            for (c.x = 0; c.x < maze->size.x; c.x++)
            {
                if (isNode(maze,c) && getMazeId(maze,c.x,c.y) != 1)
                {
                    setMazeId(maze,c.x,c.y,0);
                }
            }
        }
    }
}

int addLink(Maze* maze, Coords c)
{
    if (maze != NULL)
    {
        if (isNode(maze,c) == 0)
        {
            if (getMazeId(maze,c.x,c.y) == -1)
            {
                setMazeId(maze,c.x,c.y,0);
                return 1;
            }
        }
    }
    return 0;
}

int addLinkDir(Maze* maze, Coords c, int direction)
{
    switch (direction)
    {
        case 1: c.x++; break; // 0 rad
        case 2: c.y--; break; // pi/2 rad
        case 3: c.x--; break; // pi rad
        case 4: c.y++; break; // 3pi/2 rad
        default: break;
    }
    return addLink(maze,c);
}

int isLinked(Maze* maze, Coords c, int direction)
{
    if (maze != NULL)
    {
        if (isNode(maze,c) == 1)
        {
            switch (direction)
            {
                case 1: c.x++; break; // 0 rad
                case 2: c.y--; break; // pi/2 rad
                case 3: c.x--; break; // pi rad
                case 4: c.y++; break; // 3pi/2 rad
                default: break;
            }
            return (getMazeId(maze,c.x,c.y) == 0) ? 1 : 0;
        }
    }
    return 0;
}

int linkConnected(Maze* maze, Coords c)
{
    int links = 0;
    if (maze != NULL)
    {
        if (isNode(maze,c) == 1)
        {
            links += isLinked(maze,c,1);
            links += isLinked(maze,c,2);
            links += isLinked(maze,c,3);
            links += isLinked(maze,c,4);
        }
    }
    return links;
}

int isConnected(Maze* maze, Coords c)
{
    return (linkConnected(maze,c) > 0) ? 1 : 0;
}

void generationStep1(Maze* maze)
{
    if (maze != NULL)
    {
        fillMaze(maze,-1);
        fillBorder(maze,1);
        fillNodes(maze);
    }
}

void generationStep2(Maze* maze)
{
    Coords begin;
    if (maze != NULL)
    {
        do
        {
            begin = randomCoords(1,maze->size.x-2,1,maze->size.y-2);
        } while (isNodeMiddle(maze,begin) == 0);
        setMazeId(maze,begin.x,begin.y,2);
        addLinkDir(maze,begin,1);
        addLinkDir(maze,begin,2);
        addLinkDir(maze,begin,3);
        addLinkDir(maze,begin,4);
    }
}

void generationStep3(Maze* maze)
{
    Coords c;
    int links;
    if (maze != NULL)
    {
        for (c.x = 0; c.x < maze->size.x; c.x++)
        {
            for (c.y = 0; c.y < maze->size.y; c.y++)
            {
                if (isNodeMiddle(maze,c) == 1 && isConnected(maze,c) == 0)
                {
                    links = 0;
                    do
                    {
                        links += addLinkDir(maze,c,randomInt(1,4));
                    } while (links < 2);
                }
            }
        }
    }
}

void generationStep4(Maze* maze)
{
    Coords c;
    int links;
    if (maze != NULL)
    {
        for (c.x = 0; c.x < maze->size.x; c.x++)
        {
            for (c.y = 0; c.y < maze->size.y; c.y++)
            {
                if (isNodeSide(maze,c) == 1 && isConnected(maze,c) == 0)
                {
                    links = 0;
                    do
                    {
                        links += addLinkDir(maze,c,randomInt(1,4));
                    } while (links < 1);
                }
            }
        }
    }
}

void generationStep5(Maze* maze)
{
    if (maze != NULL)
    {

    }
}

void generationStep6(Maze* maze)
{
    if (maze != NULL)
    {

    }
}

void generationStep7(Maze* maze)
{
    Coords c;
    if (maze != NULL)
    {
        for (c.y = 0; c.y < maze->size.y; c.y++)
        {
            for (c.x = 0; c.x < maze->size.x; c.x++)
            {
                if (getMazeId(maze,c.x,c.y) == -1)
                {
                    setMazeId(maze,c.x,c.y,1);
                }
            }
        }
    }
}

void mazeGenerator(Maze* maze)
{
    generationStep1(maze);
    generationStep2(maze);
    generationStep3(maze);
    generationStep4(maze);
    generationStep5(maze);
    generationStep6(maze);
    generationStep7(maze);
}
