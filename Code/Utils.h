#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "Structs.h"

/* Logging Functions */

// Report an error
void logError(const char* msg);

// Report an SDL error
void logSDLError(const char* msg);





/* Texture Function */

// Load a texture easily
SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

// Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving the texture's width and height
void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, SDL_Rect* clip);





/* Sprite Function */

// Load Sprite with texture
Sprite* loadSprite(const char* file, SDL_Renderer* renderer);

// Destroy Sprite
void destroySprite(Sprite* sprite);

// Draw a Sprite to an SDL_Renderer with Sprite properties
void renderSprite(SDL_Renderer* renderer, Sprite* sprite);

#endif // UTILS_H_INCLUDED
