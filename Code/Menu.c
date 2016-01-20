#include "Utils.h"

SDL_Sprite* mBackgroundMenu = NULL;
SDL_Sprite* mButtonGame = NULL;
SDL_Sprite* mButtonAlgo1 = NULL;
SDL_Sprite* mButtonAlgo2 = NULL;
SDL_Sprite* mButtonQuit = NULL;

int MENU_create(SDL_Renderer* renderer)
{
    mBackgroundMenu = SDL_CreateSprite("Assets/fond.bmp",renderer);
    if (mBackgroundMenu == NULL)
    {
        error("BackgroundMenu");
        return 0;
    }

    mButtonGame = SDL_CreateSprite("Assets/boutons.bmp",renderer);
    if (mButtonGame == NULL)
    {
        error("ButtonGameMenu");
        return 0;
    }
    mButtonGame->pos.x = SCREEN_WIDTH / 2 - 160;
    mButtonGame->pos.y = 150;
    mButtonGame->rect.x = 0;
    mButtonGame->rect.y = 92 * 0;
    mButtonGame->rect.w = 320;
    mButtonGame->rect.h = 92;

    mButtonAlgo1 = SDL_CreateSprite("Assets/boutons.bmp",renderer);
    if (mButtonAlgo1 == NULL)
    {
        error("ButtonAlgo1Menu");
        return 0;
    }
    mButtonAlgo1->pos.x = SCREEN_WIDTH / 2 - 160;
    mButtonAlgo1->pos.y = 250;
    mButtonAlgo1->rect.x = 0;
    mButtonAlgo1->rect.y = 92 * 1;
    mButtonAlgo1->rect.w = 320;
    mButtonAlgo1->rect.h = 92;

    mButtonAlgo2 = SDL_CreateSprite("Assets/boutons.bmp",renderer);
    if (mButtonAlgo2 == NULL)
    {
        error("ButtonAlgo2Menu");
        return 0;
    }
    mButtonAlgo2->pos.x = SCREEN_WIDTH / 2 - 160;
    mButtonAlgo2->pos.y = 350;
    mButtonAlgo2->rect.x = 0;
    mButtonAlgo2->rect.y = 92 * 2;
    mButtonAlgo2->rect.w = 320;
    mButtonAlgo2->rect.h = 92;

    mButtonQuit = SDL_CreateSprite("Assets/boutons.bmp",renderer);
    if (mButtonQuit == NULL)
    {
        error("ButtonQuitMenu");
        return 0;
    }
    mButtonQuit->pos.x = SCREEN_WIDTH / 2 - 160;
    mButtonQuit->pos.y = 450;
    mButtonQuit->rect.x = 0;
    mButtonQuit->rect.y = 92 * 3;
    mButtonQuit->rect.w = 320;
    mButtonQuit->rect.h = 92;

    return 1;
}

void MENU_destroy()
{
    SDL_DestroySprite(mBackgroundMenu);
}

void MENU_handleEvent(SDL_Event event, SDL_Context* context)
{
    SDL_Point p;
    SDL_Rect r;
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED)
    {
        p = SDL_GetMousePosition();
        r = SDL_GetSpriteRect(mButtonGame);
        if (SDL_PointInRect(&p,&r))
        {
            STATES_switch(STATE_GAME,context);
        }

        r = SDL_GetSpriteRect(mButtonAlgo1);
        if (SDL_PointInRect(&p,&r))
        {
            STATES_switch(STATE_ALGO_1,context);
        }

        r = SDL_GetSpriteRect(mButtonAlgo2);
        if (SDL_PointInRect(&p,&r))
        {
            STATES_switch(STATE_ALGO_2,context);
        }

        r = SDL_GetSpriteRect(mButtonQuit);
        if (SDL_PointInRect(&p,&r))
        {
            STATES_switch(-1,context);
        }
    }
}

void MENU_update()
{
    SDL_Point p;
    SDL_Rect r;

    p = SDL_GetMousePosition();
    r = SDL_GetSpriteRect(mButtonGame);

    if (SDL_PointInRect(&p,&r))
    {
        mButtonGame->rect.x = 320;
    }
    else
    {
        mButtonGame->rect.x = 0;
    }

    r = SDL_GetSpriteRect(mButtonAlgo1);
    if (SDL_PointInRect(&p,&r))
    {
        mButtonAlgo1->rect.x = 320;
    }
    else
    {
        mButtonAlgo1->rect.x = 0;
    }

    r = SDL_GetSpriteRect(mButtonAlgo2);
    if (SDL_PointInRect(&p,&r))
    {
        mButtonAlgo2->rect.x = 320;
    }
    else
    {
        mButtonAlgo2->rect.x = 0;
    }

    r = SDL_GetSpriteRect(mButtonQuit);
    if (SDL_PointInRect(&p,&r))
    {
        mButtonQuit->rect.x = 320;
    }
    else
    {
        mButtonQuit->rect.x = 0;
    }
}

void MENU_render(SDL_Renderer* renderer)
{
    SDL_RenderSprite(renderer,mBackgroundMenu);
    SDL_RenderSprite(renderer,mButtonGame);
    SDL_RenderSprite(renderer,mButtonAlgo1);
    SDL_RenderSprite(renderer,mButtonAlgo2);
    SDL_RenderSprite(renderer,mButtonQuit);
}
