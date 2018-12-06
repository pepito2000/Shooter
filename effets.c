#include "effets.h"

Effet nouvel_effet_bloodHit(SDL_Texture **sprites, SDL_Rect pos, int angle){
  Effet e;
  e.pos = pos;
  e.srcrect.x = 0;
  e.srcrect.y = 0;
  e.srcrect.w = 128;
  e.srcrect.h = 128;
  e.image = sprites[2];
  e.angle = angle - 90;
  e.xMax = 1920;
  return e;
}



void afficher_effet(SDL_Renderer *renderer, Effet e){
  SDL_RenderCopyEx(renderer, e.image, &e.srcrect, &e.pos, e.angle, NULL, SDL_FLIP_NONE);
}
