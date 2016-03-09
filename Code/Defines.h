#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

// Permet de donner une taille à la fenetre
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 608

// Permet de donner une taille aux tiles
#define TILE_SIZE 32

// Nombre de tiles rentrant dans la fenetre
#define TILE_WIDTH 25
#define TILE_HEIGHT 19

// Enum pour lister les différents states
enum States
{
    STATE_MENU = 0,
    STATE_GAME = 1,
    STATE_ALGO_1 = 2,
    STATE_ALGO_2 = 3,
};

enum Direction
{
    North = 0,
    West = 1,
    South = 2,
    East = 3,
    DirCount = 4,
};

enum Blocks
{
    Vide = 0,
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    Mur = 5,
    MurA = 6,
    MurB = 7,
    MurC = 8,
    MurD = 9,
    MurE = 10,
    MurF = 11,
};

#endif // DEFINES_H_INCLUDED
