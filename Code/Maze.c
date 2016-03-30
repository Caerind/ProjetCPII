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
        error("Mauvaise alloc - Maze");
        return NULL;
    }

    // Taille
    maze->size.x = sizeX;
    maze->size.y = sizeY;
    maze->numCheeses = 0;
    maze->numCats = 0;
    maze->numMouses = 0;

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
    int i;
    SDL_Point c;
    SDL_Sprite* sprite = NULL;
    if (maze != NULL)
    {
        // Dessiner le sol
        sprite = SDL_CreateSprite("Assets/tileset.bmp",renderer);
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
                    SDL_RenderSprite(renderer,sprite);
                }
            }
        }
        SDL_DestroySprite(sprite);

        // Dessiner les fromages
        for (i = 0; i < maze->numCheeses; i++)
        {
            renderCheese(renderer,maze->cheeses[i]);
        }

        // Dessiner les souris
        for (i = 0; i < maze->numMouses; i++)
        {
            renderMouse(renderer,maze->mouses[i]);
        }

        // Dessiner les chats
        for (i = 0; i < maze->numCats; i++)
        {
            renderCat(renderer,maze->cats[i]);
        }
    }
}

void updateMaze(Maze* maze)
{
    int i;

    // On supprime les souris mangées
    for (i = 0; i < maze->numMouses; i++)
    {
        removeMouseFromMaze(maze,i);
    }

    // On supprime les fromages mangés
    for (i = 0; i < maze->numCheeses; i++)
    {
        removeCheeseFromMaze(maze,i);
    }
}

void fillMaze(Maze* maze, int id)
{
    SDL_Point c;
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
    SDL_Point c;

    // Open file
    file = fopen(filename,"r");
    if (file == NULL)
    {
        error("Load Maze");
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

void saveMazeToFile(Maze* maze, const char* filename)
{
    FILE* file = NULL;
    SDL_Point p;
    if (maze != NULL)
    {
        // Open file
        file = fopen(filename,"w");
        if (file != NULL)
        {
            // Save size
            fprintf(file,"%d %d\n",maze->size.x,maze->size.y);

            // Save it
            for (p.y = 0; p.y < maze->size.y; p.y++)
            {
                for (p.x = 0; p.x < maze->size.x; p.x++)
                {
                    fprintf(file,"%d ",maze->tab[p.x][p.y]);
                }
                fprintf(file,"\n");
            }

            fclose(file);
        }
        else
        {
            error("Save Maze");
        }
    }
}

void addMazeMouse(Maze* maze, SDL_Renderer* renderer, int x, int y)
{
    if (maze != NULL)
    {
        maze->mouses[maze->numMouses] = createMouse(x,y,renderer);
        generateMouseTree(maze,maze->numMouses);
        maze->numMouses++;
    }
}

void addMazeCheese(Maze* maze, SDL_Renderer* renderer, int x, int y)
{
    if (maze != NULL)
    {
        maze->cheeses[maze->numCheeses] = createCheese(x,y,renderer);
        maze->numCheeses++;
    }
}

void addMazeCat(Maze* maze, SDL_Renderer* renderer, int x, int y)
{
    if (maze != NULL)
    {
        maze->cats[maze->numCats] = createCat(x,y,renderer);
        maze->cats[maze->numCats]->mouse=NULL;
        maze->numCats++;
    }
}

void removeCheeseFromMaze(Maze* maze,int cheeseIndex)
{
    Cheese* cheese = maze->cheeses[cheeseIndex];
    int i,j;
    for (i = 0; i < maze->numMouses; i++)
    {
        if (cheese->coords.x == maze->mouses[i]->coords.x && cheese->coords.y == maze->mouses[i]->coords.y)
        {
            for(j = cheeseIndex; j < maze->numCheeses-1; j++)
            {
                maze->cheeses[j]=maze->cheeses[j+1];
            }
            maze->cheeses[maze->numCheeses-1] = NULL;
            maze->numCheeses--;
        }
    }
}

void removeMouseFromMaze(Maze* maze, int mouseIndex)
{
    Mouse* mouse = maze->mouses[mouseIndex];
    int i,j;
    for (i = 0; i < maze->numCats; i++)
    {
        if (maze->cats[i]->coords.x == mouse->coords.x && maze->cats[i]->coords.y == mouse->coords.y)
        {
            for (j = mouseIndex; j < maze->numMouses-1; j++)
            {
                maze->mouses[j] = maze->mouses[j+1];
            }
            maze->mouses[maze->numMouses-1] = NULL;
            maze->numMouses--;
        }
    }
}
