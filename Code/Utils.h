#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

struct Coords
{
    int x;
    int y;
};

typedef struct Coords Coords;

// Report an error
void logError(const char* msg);

// Report an SDL error
void logSDLError(const char* msg);

// Load a texture easily
SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

// Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving the texture's width and height
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect* clip);

#endif // UTILS_H_INCLUDED
