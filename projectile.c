#include "projectile.h"


balle nouvelle_balle(SDL_Texture *image, float angle, int degats, SDL_Rect persoPos)
{
  balle b;
  b.angle = angle;
  b.collision = false;
  b.image = image;
  b.ballePos = persoPos;
  b.degats = degats;
  return b;
}


void incrementer_balle(balle *b, int v)
{
  b->ballePos.x += round(cos(b->angle * PI / 180) * v);
  b->ballePos.y += round(sin(b->angle * PI / 180) * v);
}



void afficher_balle(SDL_Renderer *renderer, balle b)
{
  SDL_RenderCopyEx(renderer, b.image, NULL, &b.ballePos, b.angle, NULL, SDL_FLIP_NONE);
}



