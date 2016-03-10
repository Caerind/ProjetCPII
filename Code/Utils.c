#include "Structs.h"
#include <stdlib.h>
#include <stdio.h>

void error(const char* msg)
{
    printf("Error : %s\n",msg);
}

void errorSDL(const char* msg)
{
    printf("Error : %s : %s\n",msg,SDL_GetError());
}

SDL_Context* SDL_CreateContext(const char* title, int sizeX, int sizeY)
{
    SDL_Context* context = NULL;
    context = malloc(sizeof(SDL_Context));
    if (context == NULL)
    {
        error("Mauvaise alloc");
        return NULL;
    }

    context->window = NULL;
    context->renderer = NULL;
    context->isOpen = 0;

    context->window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,sizeX,sizeY,SDL_WINDOW_SHOWN);
    if (context->window == NULL)
    {
        errorSDL("Window");
        return NULL;
    }
    else
    {
        context->isOpen = 1;
    }

    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (context->renderer == NULL)
    {
        errorSDL("Renderer");
        return NULL;
    }

    return context;
}

void SDL_DestroyContext(SDL_Context* context)
{
    if (context != NULL)
    {
        SDL_DestroyRenderer(context->renderer);
        SDL_DestroyWindow(context->window);
        context->isOpen = 0;
    }
    free(context);
}



SDL_Texture* SDL_CreateTextureFromFile(const char* file, SDL_Renderer* renderer)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* loadedImage = SDL_LoadBMP(file);
	if (loadedImage != NULL)
    {
		texture = SDL_CreateTextureFromSurface(renderer,loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == NULL)
        {
			errorSDL("CreateTextureFromSurface");
		}
	}
	else
	{
		errorSDL("LoadBMP");
	}
	return texture;
}

void SDL_RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, SDL_Rect* clip)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != NULL)
    {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	}
	SDL_RenderCopy(renderer, texture, clip, &dst);
}

SDL_Sprite* SDL_CreateSprite(const char* file, SDL_Renderer* renderer)
{
    SDL_Sprite* sprite = NULL;

    sprite = malloc(sizeof(SDL_Sprite)); // Allocation de la mémoire
    if (sprite == NULL)
    {
        error("Mauvaise alloc");
        return NULL;
    }

    sprite->texture = SDL_CreateTextureFromFile(file,renderer);
    sprite->pos.x = 0;
    sprite->pos.y = 0;
    sprite->rect.x = 0;
    sprite->rect.y = 0;
    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->rect.w, &sprite->rect.h);

    return sprite;
}

SDL_Sprite* SDL_CreateSpriteTransparency(const char* file, SDL_Renderer* renderer, int r, int g, int b)
{
    SDL_Sprite* sprite = NULL;

    sprite = malloc(sizeof(SDL_Sprite)); // Allocation de la mémoire
    if (sprite == NULL)
    {
        error("Mauvaise alloc");
        return NULL;
    }

	SDL_Surface* loadedImage = SDL_LoadBMP(file);
	if (loadedImage != NULL)
    {
        SDL_SetColorKey(loadedImage,SDL_TRUE,SDL_MapRGB(loadedImage->format,r,g,b));
		sprite->texture = SDL_CreateTextureFromSurface(renderer,loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
	{
		errorSDL("LoadBMP_Transparency");
	}

    sprite->pos.x = 0;
    sprite->pos.y = 0;
    sprite->rect.x = 0;
    sprite->rect.y = 0;
    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->rect.w, &sprite->rect.h);

    return sprite;
}

void SDL_DestroySprite(SDL_Sprite* sprite)
{
    SDL_DestroyTexture(sprite->texture);
    free(sprite);
}

void SDL_RenderSprite(SDL_Renderer* renderer, SDL_Sprite* sprite)
{
    if (sprite != NULL)
    {
        if (sprite->texture != NULL)
        {
            SDL_RenderTexture(renderer,sprite->texture,sprite->pos.x,sprite->pos.y, &sprite->rect);
        }
    }
}

SDL_Rect SDL_GetSpriteRect(SDL_Sprite* sprite)
{
    SDL_Rect r;
    if (sprite != NULL)
    {
        r.x = sprite->pos.x;
        r.y = sprite->pos.y;
        r.w = sprite->rect.w;
        r.h = sprite->rect.h;
    }
    return r;
}

SDL_Point SDL_GetMousePosition()
{
    SDL_Point p;
    SDL_GetMouseState(&p.x,&p.y);
    return p;
}

int randomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

Coords randomCoords(int minX, int maxX, int minY, int maxY)
{
    Coords c;
    c.x = randomInt(minX,maxX);
    c.y = randomInt(minY,maxY);
    return c;
}
