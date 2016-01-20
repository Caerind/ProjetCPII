#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "Defines.h"
#include "Structs.h"

/* Logging Functions */

// Report an error
void error(const char* msg);

// Report an SDL error
void errorSDL(const char* msg);



/* Context Function */

// Load a context
SDL_Context* SDL_CreateContext(const char* title, int sizeX, int sizeY);

// Free the context
void SDL_DestroyContext(SDL_Context* context);



/* Texture Function */

// Load a texture easily
SDL_Texture* SDL_CreateTextureFromFile(const char* file, SDL_Renderer* renderer);

// Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving the texture's width and height
void SDL_RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, SDL_Rect* clip);





/* Sprite Function */

// Load Sprite with texture
SDL_Sprite* SDL_CreateSprite(const char* file, SDL_Renderer* renderer);

// Destroy Sprite
void SDL_DestroySprite(SDL_Sprite* sprite);

// Draw a Sprite to an SDL_Renderer with Sprite properties
void SDL_RenderSprite(SDL_Renderer* renderer, SDL_Sprite* sprite);

// Get the rect in the window of a sprite
SDL_Rect SDL_GetSpriteRect(SDL_Sprite* sprite);



/* Get Mouse Position */
SDL_Point SDL_GetMousePosition();



/* Random Generator */

// Random Int
int randomInt(int min, int max);

// Random Coords
Coords randomCoords(int minX, int maxX, int minY, int maxY);

#endif // UTILS_H_INCLUDED
