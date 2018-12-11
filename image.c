#include "image.h"


SDL_Texture* charger_image(const char* cheminFichier, SDL_Renderer* renderer, int r, int g, int b){

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
  int tabVal;

  //affichage routes & murs
  for(int j = 0; j < 60; j++){
    for(int i = 0; i < 60; i++){
      destrect.x = i * 50 - xCamera;
      destrect.y = j * 50 - yCamera;
      destrect.h = 50;
      destrect.w = 50;
      tabVal = tab[60*j+i];
      if(tabVal != '.' && tabVal != 'A' && tabVal != 'P'){
        SDL_RenderCopy(renderer, spriteMap[0], NULL, &destrect);
      }
      switch(tabVal){
      case '0':
        SDL_RenderCopy(renderer, spriteMap[0], NULL, &destrect);
        break;
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
      case 'R':
        destrect.w = 200;
        destrect.h = 200;
        SDL_RenderCopy(renderer, spriteMap[10], NULL, &destrect);
        break;
      case 'S':
        destrect.w = 200;
        destrect.h = 200;
        SDL_RenderCopy(renderer, spriteMap[9], NULL, &destrect);
        break;
      case 'E':
        SDL_RenderCopy(renderer, spriteMap[13], NULL, &destrect);
        break;
      case 'H':
        SDL_RenderCopy(renderer, spriteMap[17], NULL, &destrect);
        break;
      case 'M':
        destrect.w = 550;
        destrect.h = 400;
        SDL_RenderCopy(renderer, spriteMap[15], NULL, &destrect);
        break;
      case 'N':
        destrect.w = 500;
        destrect.h = 600;
        SDL_RenderCopy(renderer, spriteMap[16], NULL, &destrect);
        break;
      case 'L':
        destrect.w = 800;
        destrect.h = 600;
        SDL_RenderCopy(renderer, spriteMap[18], NULL, &destrect);
        break;

      default:
        break;
      }
    }
  }

  //voitures
  for(int j = 0; j < 60; j++){
    for(int i = 0; i < 60; i++){
      destrect.x = i * 50 - xCamera;
      destrect.y = j * 50 - yCamera;
      destrect.h = 50;
      destrect.w = 50;
    switch(tab[60*j+i]){
      case 'P':
        destrect.w = 200;
        destrect.h = 100;
        SDL_RenderCopy(renderer, spriteMap[11], NULL, &destrect);
        break;
      case 'A':
        destrect.w = 100;
        destrect.h = 200;
        SDL_RenderCopy(renderer, spriteMap[12], NULL, &destrect);
        break;
      case 'C' :
        destrect.w = 150;
        destrect.h = 250;
        SDL_RenderCopy(renderer, spriteMap[14], NULL, &destrect);
        break;
      case 'F':
        destrect.w = 300;
        destrect.h = 300;
        SDL_RenderCopy(renderer, spriteMap[19], NULL, &destrect);
        break;

      default :
        break;
    }
    }
  }



  return;
}
