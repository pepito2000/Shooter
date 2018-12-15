#include "effets.h"

Effet nouvel_effet_bloodHit(SDL_Texture **sprites, SDL_Rect pos, int angle){
  Effet e;
  e.pos = pos;
  e.pos.x -= 8;
  e.pos.y -= 8;
  e.pos.w = 60;
  e.pos.h = 60;
  e.srcrect.x = 0;
  e.srcrect.y = 0;
  e.srcrect.w = 128;
  e.srcrect.h = 128;
  e.image = sprites[3];
  e.angle = angle - 90;
  e.yMax = 1920;
  e.id = 1;
  return e;
}

Effet nouvel_effet_bloodSplatter(SDL_Texture **sprites, SDL_Rect pos, int angle){
  Effet e;
  e.pos = pos;
  e.pos.x -= 20;
  e.pos.y -= 20;
  e.pos.w = 80;
  e.pos.h = 80;
  e.srcrect.x = 0;
  e.srcrect.y = 0;
  e.srcrect.w = 100;
  e.srcrect.h = 100;
  e.image = sprites[4];
  e.angle = angle - 90;
  e.yMax = 800;
  e.id = 2;
  return e;
}



void afficher_effet(SDL_Renderer *renderer, Effet e){
  SDL_RenderCopyEx(renderer, e.image, &e.srcrect, &e.pos, e.angle, NULL, SDL_FLIP_NONE);
}
