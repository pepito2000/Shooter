#include "projectile.h"



balle nouvelle_balle(SDL_Texture *image, float angle, int degats, SDL_Rect persoPos){
  balle b;
  b.angle = angle;
  b.collision = false;
  b.image = image;
  b.ballePos = persoPos;
  b.degats = degats;
  b.ennemi = false;
  b.srcrect.x = 0;
  b.srcrect.y = 0;
  b.srcrect.w = persoPos.w;
  b.srcrect.h = persoPos.h;
  return b;
}

void incrementer_balle(balle *b, int v, int dxCamera, int dyCamera){
  b->ballePos.x += round(cos(b->angle * PI / 180) * v);
  b->ballePos.y += round(sin(b->angle * PI / 180) * v);
  if(b->ennemi){
    b->ballePos.x -= dxCamera;
    b->ballePos.y -= dyCamera;
  }
  return;
}


void afficher_balle(SDL_Renderer *renderer, balle b){
  if(b.ennemi){
    SDL_RenderCopyEx(renderer, b.image, &b.srcrect, &b.ballePos, b.angle + 90, NULL, SDL_FLIP_NONE);
  } else {
    SDL_RenderCopyEx(renderer, b.image, &b.srcrect, &b.ballePos, b.angle, NULL, SDL_FLIP_NONE);
  }
}



