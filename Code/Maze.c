#include <SDL2/SDL.h>
#include <stdio.h>
#include "Structs.h"
#include "Utils.h"
#include "Defines.h"

Maze* createMaze(int size)
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
    maze->size = size;

    // Allocation dynamique tableau
    maze->tab = malloc(maze->size * sizeof(int*));
    for (i = 0; i < maze->size; i++)
    {
        maze->tab[i] = malloc(maze->size * sizeof(int));
    }

    // Fill it with -1
    fillMaze(maze,-1);

    return maze;
}

void destroyMaze(Maze* maze)
{
    int i;
    for (i = 0; i < maze->size; i++)
    {
        free(maze->tab[i]);
    }
    free(maze->tab);
    free(maze);
}

void renderMaze(SDL_Renderer* renderer, Maze* maze)
{
    int i, j;
    Sprite* sprite = NULL;
    if (maze != NULL)
    {
        sprite = loadSprite("Assets/tileset.bmp",renderer);
        if (sprite != NULL)
        {
            sprite->rect.y = 0;
            sprite->rect.w = TILE_SIZE;
            sprite->rect.h = TILE_SIZE;
            for (j = 0; j < maze->size; j++)
            {
                for (i = 0; i < maze->size; i++)
                {
                    sprite->pos.x = i * TILE_SIZE;
                    sprite->pos.y = j * TILE_SIZE;
                    sprite->rect.x = maze->tab[i][j] * TILE_SIZE;
                    renderSprite(renderer,sprite);
                }
            }
        }
    }
}

void fillMaze(Maze* maze, int id)
{
    int i, j;
    if (maze != NULL)
    {
        for (i = 0; i < maze->size; i++)
        {
            for(j = 0; j < maze->size; j++)
            {
                maze->tab[i][j] = id;
            }
        }
    }
}

Maze* loadMazeFromFile(const char* filename)
{
    FILE* file = NULL;
    Maze* maze = NULL;
    int size = 0;
    int i, j;

    // Open file
    file = fopen(filename,"r");
    if (file == NULL)
    {
        logError("Impossible d'ouvrir ce labyrinthe");
        return NULL;
    }

    // Get size
    fscanf(file,"%d",&size);
    printf("size : %d\n",size);

    // Make the maze with the size
    maze = createMaze(size);

    // Load it
    for (j = 0; j < maze->size; j++)
    {
        for (i = 0; i < maze->size; i++)
        {
            fscanf(file,"%d",&size);
            printf("id : %d\n",size);
            maze->tab[i][j] = size;
        }
    }

    fclose(file);
    return maze;
}

Maze* generateMaze(int size)
{
    Maze* maze = NULL;
    maze = createMaze(size);

    // GEN

    return maze;
}
