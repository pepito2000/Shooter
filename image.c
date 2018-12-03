#include "image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* charger_image(const char* cheminFichier, SDL_Renderer* renderer)
{
  SDL_Surface* surface = IMG_Load(cheminFichier);
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255 ));
  SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return image;
}

