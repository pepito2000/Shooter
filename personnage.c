#include <time.h>
#include <stdlib.h>
#include "personnage.h"
#include <math.h>

#define PI 3.14159265359

Perso nouveau_joueur(SDL_Renderer *renderer, SDL_Texture **sprites){
  Perso p;
  p.tempsTirPrecedent = 0;
  p.image = sprites[0];
  p.pos.x = 300;
  p.pos.y = 300;
  p.pos.w = 60;
  p.pos.h = 60;
  p.srcrect.x = 0;
  p.srcrect.y = 0;
  p.srcrect.w = 258;
  p.srcrect.h = 220;
  p.angle = 0;
  p.vie = 100;
  p.vitesse = 3;
  p.tir = false;
  p.ennemi = false;
  p.anim = IDLE;
  p.animFlip = 1;
  return p;
}

Perso nouvel_ennemi_1(SDL_Renderer *renderer, SDL_Texture **sprites){
  Perso p;
  p.tempsTirPrecedent = 0;
  p.image = sprites[2];
  //génère des coordonnées de spawn aléatoires(provisoire)
  p.pos.x = rand()%900 + 100;
  p.pos.y = rand()%600 + 100;
  p.pos.w = 60;
  p.pos.h = 60;
  p.srcrect.x = 0;
  p.srcrect.y = 0;
  p.srcrect.w = 258;
  p.srcrect.h = 220;
  p.angle = 0;
  p.vie = 100;
  p.vitesse = 3;
  p.tir = false;
  p.ennemi = true;
  p.anim = IDLE;
  p.animFlip = 1;
  return p;
}

void afficher_perso(SDL_Renderer *renderer, Perso p)
{
  SDL_RenderCopyEx(renderer, p.image, &p.srcrect, &p.pos, p.angle, NULL, SDL_FLIP_NONE);
}

void deplacement_joueur(Perso *p)
{
  int dX = 0;
  int dY = 0;

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  if(state[SDL_GetScancodeFromKey(SDLK_z)]){
    dY -= 1;
  }

  if(state[SDL_GetScancodeFromKey(SDLK_s)]){
    dY += 1;
  }

  if(state[SDL_GetScancodeFromKey(SDLK_q)]){
    dX -= 1;
  }

  if(state[SDL_GetScancodeFromKey(SDLK_d)]){
    dX += 1;
  }

  if(dX == 2 || dX == -2){
    dX = dX/4;
  }

  if(dY == 2 || dY == -2){
    dY = dY/4;
  }

  p->pos.x += dX * p->vitesse;
  p->pos.y += dY * p->vitesse;

}

void angle_joueur(Perso *p, float mouseX, float mouseY){
  float angle;
  //float dSourisPerso;
  angle = atan2(mouseY - (p->pos.y + 30), mouseX - (p->pos.x + 30));
  //dSourisPerso = sqrt(pow(mouseX - (p->pos.x + 30), 2) + pow(mouseY - (p->pos.y + 30), 2));
  //angle -= atan(15./dSourisPerso);
  angle = (angle * 180.0000)/PI;
  p->angle = angle;

  return;
}

void animer_perso(Perso *p){
  p->srcrect.y += 216 * p->animFlip;
  if(p->srcrect.y > 4104|| p->srcrect.y < 0){
    p->animFlip = -p->animFlip;
    p->srcrect.y += 216 * p->animFlip;
  }
  return;
}

