#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

void logError(const char* msg)
{
    fprintf(stderr,"Error : %s\n",msg);
}

void logSDLError(const char* msg)
{
    fprintf(stderr,"Error : %s : %s\n",msg,SDL_GetError());
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

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect* clip)
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
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	SDL_RenderCopy(ren, tex, clip, &dst);
}
