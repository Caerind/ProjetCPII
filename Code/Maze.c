#include <SDL2/SDL.h>
#include <stdio.h>
#include "Structs.h"
#include "Utils.h"
#include "Defines.h"

Maze* createMaze(int sizeX, int sizeY)
{
    int i;
    Maze* maze = NULL;

    // Allocation mémoire
    maze = malloc(sizeof(Maze));
    if (maze == NULL)
    {
        logError("Mauvaise alloc");
        return NULL;
    }

    // Taille
    maze->size.x = sizeX;
    maze->size.y = sizeY;

    // Allocation dynamique tableau
    maze->tab = malloc(maze->size.x * sizeof(int*));
    for (i = 0; i < maze->size.x; i++)
    {
        maze->tab[i] = malloc(maze->size.y * sizeof(int));
    }

    return maze;
}

void destroyMaze(Maze* maze)
{
    int i;
    for (i = 0; i < maze->size.x; i++)
    {
        free(maze->tab[i]);
    }
    free(maze->tab);
    free(maze);
}

void renderMaze(SDL_Renderer* renderer, Maze* maze)
{
    Coords c;
    Sprite* sprite = NULL;
    if (maze != NULL)
    {
        sprite = loadSprite("Assets/tileset.bmp",renderer);
        if (sprite != NULL)
        {
            sprite->rect.y = 0;
            sprite->rect.w = TILE_SIZE;
            sprite->rect.h = TILE_SIZE;
            for (c.y = 0; c.y < maze->size.y; c.y++)
            {
                for (c.x = 0; c.x < maze->size.x; c.x++)
                {
                    sprite->pos.x = c.x * TILE_SIZE;
                    sprite->pos.y = c.y * TILE_SIZE;
                    sprite->rect.x = maze->tab[c.x][c.y] * TILE_SIZE;
                    renderSprite(renderer,sprite);
                }
            }
        }
    }
}

void fillMaze(Maze* maze, int id)
{
    Coords c;
    if (maze != NULL)
    {
        for (c.x = 0; c.x < maze->size.x; c.x++)
        {
            for(c.y = 0; c.y < maze->size.y; c.y++)
            {
                maze->tab[c.x][c.y] = id;
            }
        }
    }
}

int getMazeId(Maze* maze, int x, int y)
{
    if (maze != NULL)
    {
        if (x >= 0 && x < maze->size.x && y >= 0 && y < maze->size.y)
        {
            return maze->tab[x][y];
        }
    }
    return -1;
}

void setMazeId(Maze* maze, int x, int y, int id)
{
    if (maze != NULL)
    {
        if (x >= 0 && x < maze->size.x && y >= 0 && y < maze->size.y)
        {
            maze->tab[x][y] = id;
        }
    }
}

Maze* loadMazeFromFile(const char* filename)
{
    FILE* file = NULL;
    Maze* maze = NULL;
    Coords c;

    // Open file
    file = fopen(filename,"r");
    if (file == NULL)
    {
        logError("Impossible d'ouvrir ce labyrinthe");
        return NULL;
    }

    // Get size
    fscanf(file,"%d %d",&c.x,&c.y);

    // Make the maze with the size
    maze = createMaze(c.x,c.y);

    // Load it
    for (c.y = 0; c.y < maze->size.y; c.y++)
    {
        for (c.x = 0; c.x < maze->size.x; c.x++)
        {
            fscanf(file,"%d",&maze->tab[c.x][c.y]);
        }
    }

    fclose(file);
    return maze;
}
