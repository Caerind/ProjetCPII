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

#endif // STATES_H_INCLUDED
