#include "image.h"


SDL_Texture* charger_image(const char* cheminFichier, SDL_Renderer* renderer, int r, int g, int b)
{
  SDL_Surface* surface = IMG_Load(cheminFichier);
  if(r >= 0 && g >= 0 && b >= 0){
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b ));
  }
  SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return image;
}

void afficher_niveau(int *tab, SDL_Renderer *renderer, SDL_Texture **spriteMap, int xCamera, int yCamera){
  SDL_Rect destrect;
  destrect.h = 50;
  destrect.w = 50;
  for(int j = 0; j < 30; j++){
    for(int i = 0; i < 30; i++){
      destrect.x = i * 50 - xCamera;
      destrect.y = j * 50 - yCamera;
      SDL_RenderCopy(renderer, spriteMap[0], NULL, &destrect);
      for(int k = 1; k < 9; k++){
        if(tab[30*j+i] == k){
          SDL_RenderCopy(renderer, spriteMap[k], NULL, &destrect);
        }
      }
    }
  }
  return;
}
