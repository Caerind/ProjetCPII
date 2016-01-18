#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "Structs.h"

void logError(const char* msg)
{
    printf("Error : %s\n",msg);
}

void logSDLError(const char* msg)
{
    printf("Error : %s : %s\n",msg,SDL_GetError());
}

SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* loadedImage = SDL_LoadBMP(file);
	if (loadedImage != NULL)
    {
		texture = SDL_CreateTextureFromSurface(renderer,loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == NULL)
        {
			logSDLError("CreateTextureFromSurface");
		}
	}
	else
	{
		logSDLError("LoadBMP");
	}
	return texture;
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, SDL_Rect* clip)
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

Sprite* loadSprite(const char* file, SDL_Renderer* renderer)
{
    Sprite* sprite = NULL;

    sprite = malloc(sizeof(Sprite)); // Allocation de la mémoire
    if (sprite == NULL)
    {
        logError("Mauvais alloc");
        return NULL;
    }

    sprite->texture = loadTexture(file,renderer);
    sprite->x = 0;
    sprite->y = 0;
    sprite->rect.x = 0;
    sprite->rect.y = 0;
    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->rect.w, &sprite->rect.h);

    return sprite;
}

void destroySprite(Sprite* sprite)
{
    SDL_DestroyTexture(sprite->texture);
    free(sprite);
}

void renderSprite(SDL_Renderer* renderer, Sprite* sprite)
{
    if (sprite != NULL)
    {
        renderTexture(renderer,sprite->texture,sprite->x,sprite->y, &sprite->rect);
    }
}
