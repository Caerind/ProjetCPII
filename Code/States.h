#ifndef STATES_H_INCLUDED
#define STATES_H_INCLUDED

#include "Structs.h"

// Fonction pour connaitre le state actuel
int STATES_getState();

// Fonction pour gérer les évènements en fonction du state actuel
void STATES_handleEvent(SDL_Event event, SDL_Context* context);

// Fonction pour mettre à jour en fonction du state actuel
void STATES_update();

// Fonction pour  dessiner en fonction du state actuel
void STATES_render(SDL_Renderer* renderer);

// Fonction pour aller d'un state à l'autre
void STATES_switch(int newState, SDL_Context* context);

// Fonctions pour gérer les évènements en fonction du state
//void GAME_handleEvent(SDL_Event event, SDL_Context* context);
//void ALGO1_handleEvent(SDL_Event event, SDL_Context* context);
//void ALGO2_handleEvent(SDL_Event event, SDL_Context* context);

// Fonctions pour mettre à jour en fonction du state
//void GAME_update();
//void ALGO1_update();
//void ALGO2_update();

// Fonctions pour dessiner en fonction du state
//void GAME_render(SDL_Renderer* renderer);
//void ALGO1_render(SDL_Renderer* renderer);
//void ALGO2_render(SDL_Renderer* renderer);

// Fonctions pour charger un state
//int GAME_create(SDL_Renderer* renderer);
//int ALGO1_create(SDL_Renderer* renderer);
//int ALGO2_create(SDL_Renderer* renderer);

// Fonctions pour libérer un state
//void GAME_destroy();
//void ALGO1_destroy();
//void ALGO2_destroy();

#endif // STATES_H_INCLUDED
