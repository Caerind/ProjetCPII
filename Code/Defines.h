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

#endif // DEFINES_H_INCLUDED
