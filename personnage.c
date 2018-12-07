#include "personnage.h"


Perso nouveau_joueur(SDL_Renderer *renderer, SDL_Texture **sprites){
  Perso p;
  p.tempsTirPrecedent = 0;
  p.image = sprites[0];
  p.pos.x = 480;
  p.pos.y = 330;
  p.pos.w = 40;
  p.pos.h = 40;
  p.srcrect.x = 0;
  p.srcrect.y = 0;
  p.srcrect.w = 258;
  p.srcrect.h = 220;
  p.angle = 0;
  p.vie = 100;
  p.degats = 25;
  p.vitesse = 4;
  p.yMax = 0;
  p.tir = false;
  p.ennemi = false;
  p.animFlip = 1;
  return p;
}

Perso nouvel_ennemi_1(SDL_Renderer *renderer, SDL_Texture **sprites){
  Perso p;
  p.tempsTirPrecedent = 0;
  p.image = sprites[1];
  //génère des coordonnées de spawn aléatoires(provisoire)
  p.pos.x = rand()%100 + 0;
  p.pos.y = rand()%700 + 0;
  p.pos.w = 50;
  p.pos.h = 50;
  p.srcrect.x = 0;
  p.srcrect.y = 0;
  p.srcrect.w = 229;
  p.srcrect.h = 259;
  p.angle = 0;
  p.vie = 100;
  p.degats = 10;
  p.vitesse = 2;
  p.yMax = 4403;
  p.tir = false;
  p.ennemi = true;
  p.animFlip = 1;
  return p;
}

void afficher_perso(SDL_Renderer *renderer, Perso p)
{
  SDL_RenderCopyEx(renderer, p.image, &p.srcrect, &p.pos, p.angle, NULL, SDL_FLIP_NONE);
}

void deplacement_joueur(Perso *p, ListeR L, int *xCamera, int *yCamera, int *dxCamera, int *dyCamera)
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


  dX = dX * p->vitesse;
  dY = dY * p->vitesse;


  *xCamera += dX;
  *yCamera += dY;
  *dxCamera = dX;
  *dyCamera = dY;


  if(detecter_collision_murs(L, p->pos, *xCamera, *yCamera)){
    *xCamera -= dX;
    *dxCamera = 0;
    if(detecter_collision_murs(L, p->pos, *xCamera, *yCamera)){
      *xCamera += dX;
      *dxCamera = dX;
      *yCamera -= dY;
      *dyCamera = 0;
      if(detecter_collision_murs(L, p->pos, *xCamera, *yCamera)){
        *xCamera -= dX;
        *dxCamera = 0;
      }
    }
  }

  return;
}


void angle_joueur(Perso *p, float mouseX, float mouseY){
  float angle;
  angle = atan2(mouseY - (p->pos.y + 20), mouseX - (p->pos.x + 20));
  angle = (angle * 180.0000)/PI;
  p->angle = angle;
  return;
}

void angle_ennemi(Perso *p){
  float angle;
  angle = atan2(350 - (p->pos.y + 20), 500 - (p->pos.x + 20));
  p->angle = angle;
  return;
}

void animer_perso(Perso *p, Perso *joueur, SDL_Texture **sprites){
  if(p->tir){
    if(p->srcrect.w != 318){
      p->image = sprites[2];
      p->pos.w = 60;
      p->pos.h = 60;
      p->srcrect.w = 318;
      p->srcrect.h = 294;
      p->srcrect.y = 0;
      p->yMax = 2646;
      p->animFlip = 1;
    } else {
      p->srcrect.y += p->srcrect.h * p->animFlip;
      if(p->srcrect.y == p->srcrect.h * 6){
        if(joueur->vie < p->degats){
          joueur->vie = 0;
        }else {
          joueur->vie -= p->degats;
        }
      } else if(p->srcrect.y == p->yMax){
        p->image = sprites[1];
        p->pos.w = 50;
        p->pos.h = 50;
        p->srcrect.w = 229;
        p->srcrect.h = 259;
        p->srcrect.y = 0;
        p->yMax = 4403;
        p->animFlip = 1;
        p->tir = false;
        p->vitesse = 2;
      }
    }

  }

  else {
    p->srcrect.y += p->srcrect.h * p->animFlip;
    if((p->srcrect.y >= p->yMax || p->srcrect.y < 0) && !p->tir){
      p->animFlip = -p->animFlip;
      p->srcrect.y += p->srcrect.h * p->animFlip;
    }
  }
  return;
}


