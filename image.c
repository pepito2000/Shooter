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


void afficher_niveau(char *tab, SDL_Renderer *renderer, SDL_Texture **spriteMap, int xCamera, int yCamera){
  SDL_Rect destrect;
  destrect.h = 50;
  destrect.w = 50;
  for(int j = 0; j < 60; j++){
    for(int i = 0; i < 60; i++){
      destrect.x = i * 50 - xCamera;
      destrect.y = j * 50 - yCamera;
      SDL_RenderCopy(renderer, spriteMap[0], NULL, &destrect);
      switch(tab[60*j+i]){
      case '1':
        SDL_RenderCopy(renderer, spriteMap[1], NULL, &destrect);
        break;
      case '2':
        SDL_RenderCopy(renderer, spriteMap[2], NULL, &destrect);
        break;
      case '3':
        SDL_RenderCopy(renderer, spriteMap[3], NULL, &destrect);
        break;
      case '4':
        SDL_RenderCopy(renderer, spriteMap[4], NULL, &destrect);
        break;
      case '5':
        SDL_RenderCopy(renderer, spriteMap[5], NULL, &destrect);
        break;
      case '6':
        SDL_RenderCopy(renderer, spriteMap[6], NULL, &destrect);
        break;
      case '7':
        SDL_RenderCopy(renderer, spriteMap[7], NULL, &destrect);
        break;
      case '8':
        SDL_RenderCopy(renderer, spriteMap[8], NULL, &destrect);
        break;
      }


    }
  }
  return;
}
