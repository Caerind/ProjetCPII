#include <time.h>
#include "Defines.h"
#include "Utils.h"
#include "States.h"

// Notre structure Context
static SDL_Context* mContext = NULL;

int init(const char* title, int width, int height)
{
    // Initialisation du générateur de nombre aléatoire
    srand(time(NULL));

    // Initialisation de la SDL (Module Vidéo)
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        errorSDL("Init");
        return -1;
    }

    // Initialisation du Context
    mContext = SDL_CreateContext(title,width,height);
    if (mContext == NULL)
    {
        error("Context");
        return -1;
    }

    // Chargement du menu
    STATES_switch(STATE_MENU,mContext);

    return 1;
}

void quit()
{
    // On detruit le dernier state
    STATES_switch(-1,mContext);

    // Suppresion du Context
    SDL_DestroyContext(mContext);

    // On quitte SDL
    SDL_Quit();
}

void handleEvents()
{
    SDL_Event event;

    // On traite les évènements
    while (SDL_PollEvent(&event) != 0)
    {
        // On indique qu'on souhaite fermer la fenêtre si l'on souhaite quitter le programme
        if (event.type == SDL_QUIT)
        {
            mContext->isOpen = 0;
        }

        // On délègue l'évènement au state actuel
        STATES_handleEvent(event,mContext);
    }
}

void update()
{
    // On met à jour le state actuel
    STATES_update();
}

void render()
{
    // Position de la souris
    SDL_Point m = SDL_GetMousePosition();

    // On efface le contenu de la fenêtre
	SDL_RenderClear(mContext->renderer);

    // On dessine le state actuel
	STATES_render(mContext->renderer);

    // On dessine le curseur
	if (mContext->cursor != NULL)
    {
        mContext->cursor->pos.x = m.x;
        mContext->cursor->pos.y = m.y;
        SDL_RenderSprite(mContext->renderer,mContext->cursor);
    }
    else
    {
        SDL_ShowCursor(1);
    }

    // On affiche le renderer sur la fenêtre
	SDL_RenderPresent(mContext->renderer);
}

void run()
{
    // On boucle tant qu'on a pas demander de quitter
    while (mContext->isOpen)
    {
        // Gestion des évènements
        handleEvents();

        // Mise à jour
        update();

        // Rendu
        render();

        // On attend un peu avant de commencer la prochaine boucle
        SDL_Delay(20); // 20ms ~= 60 FPS
    }
}
