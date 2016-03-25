#include <time.h>
#include "Defines.h"
#include "Utils.h"
#include "States.h"

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

// Notre structure Context
SDL_Context* mContext = NULL;
Mix_Music* mMusic = NULL;
SDL_Sprite* mCursor = NULL;

int init()
{
    // Initialisation du g�n�rateur de nombre al�atoire
    srand(time(NULL));

    // Initialisation de la SDL (Module Vid�o)
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        errorSDL("Init");
        return -1;
    }

    // Initialisation du Context
    mContext = SDL_CreateContext("Labyrinthe",SCREEN_WIDTH,SCREEN_HEIGHT);
    if (mContext == NULL)
    {
        error("Context");
        return -1;
    }

    mCursor = SDL_CreateSpriteTransparency("Assets/cursor.bmp",mContext->renderer,255,0,255);
    if (mCursor != NULL)
    {
        SDL_ShowCursor(0);
    }

    // Ouverture d'un canal
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return -1;
    }

    // On charge et on joue la musique
    mMusic = Mix_LoadMUS("Assets/theme.ogg");
    if (mMusic != NULL)
    {
        if (Mix_PlayMusic(mMusic,-1) == -1)
        {
            printf("Mix_PlayMusic: %s\n", Mix_GetError());
        }
    }
    else
    {
        printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }

    // Chargement du menu
    STATES_switch(STATE_MENU,mContext);

    return 1;
}

void quit()
{
    // On arrete la musique
    Mix_HaltMusic();

    // On detruit le dernier state
    STATES_switch(-1,mContext);

    // Suppresion du Context
    SDL_DestroyContext(mContext);

    Mix_FreeMusic(mMusic);

    // On quitte SDL
    SDL_Quit();
}

void handleEvents()
{
    SDL_Event event;

    // On traite les �v�nements
    while (SDL_PollEvent(&event) != 0)
    {
        // On indique qu'on souhaite fermer la fen�tre si l'on souhaite quitter le programme
        if (event.type == SDL_QUIT)
        {
            mContext->isOpen = 0;
        }

        // On d�l�gue l'�v�nement au state actuel
        STATES_handleEvent(event,mContext);
    }
}

void update()
{
    // On met � jour le state actuel
    STATES_update();
}

void render()
{
    SDL_Point m = SDL_GetMousePosition();

    // On efface le contenu de la fen�tre
	SDL_RenderClear(mContext->renderer);

    // On dessine le state actuel
	STATES_render(mContext->renderer);

	if (mCursor != NULL)
    {
        mCursor->pos.x = m.x;
        mCursor->pos.y = m.y;
        SDL_RenderSprite(mContext->renderer,mCursor);
    }
    else
    {
        SDL_ShowCursor(1);
    }

    // On affiche le renderer sur la fen�tre
	SDL_RenderPresent(mContext->renderer);
}

void run()
{
    // On boucle tant qu'on a pas demander de quitter
    while (mContext->isOpen)
    {
        // Gestion des �v�nements
        handleEvents();

        // Mise � jour
        update();

        // Rendu
        render();

        // On attend un peu avant de commencer la prochaine boucle
        SDL_Delay(20); // 20ms ~= 60 FPS
    }
}

