#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include "projectile.h"


#define PI 3.14159265359


balle nouvelle_balle(SDL_Texture *image, float angle, SDL_Rect persoPos)
{
  balle b;
  b.angle = angle;
  b.collision = false;
  b.image = image;
  b.ballePos = persoPos;
  return b;
}

//v = vitesse de la balle (provisoire)
void incrementer_balle(balle *b, int v)
{
  b->ballePos.x += (int)(cos(b->angle * PI / 180) * v);
  b->ballePos.y += (int)(sin(b->angle * PI / 180) * v);
}



void afficher_balle(SDL_Renderer *renderer, balle b)
{
  SDL_RenderCopyEx(renderer, b.image, NULL, &b.ballePos, b.angle, NULL, SDL_FLIP_NONE);
}



