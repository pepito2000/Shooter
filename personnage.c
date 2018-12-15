#include "personnage.h"


Perso nouveau_joueur(SDL_Renderer *renderer, SDL_Texture **sprites){
  Perso p;
  p.tempsTirPrecedent = 0;
  p.image = sprites[0];
  p.pos.x = 465;
  p.pos.y = 335;
  p.pos.w = 70;
  p.pos.h = 30;
  p.srcrect.x = 0;
  p.srcrect.y = 0;
  p.srcrect.w = 395;
  p.srcrect.h = 151;
  p.angle = 0;
  p.vie = 100;
  p.vitesse = 4;
  p.yMax = 0;
  p.arme = 0;
  p.tir = false;
  p.ennemi = false;
  p.collision = 0;
  p.animFlip = 1;
  return p;
}

Perso nouvel_ennemi_1(SDL_Renderer *renderer, ListeR LR, SDL_Texture **sprites, int xCamera, int yCamera){
  Perso p;
  p.tempsTirPrecedent = 0;
  p.image = sprites[1];
  p.pos.w = 50;
  p.pos.h = 50;
  int x, y;
  do {
    do {
      x = (rand()%2950 + 0) - xCamera;
    } while(x > 0 && x < 1000);
    do {
      y = (rand()%2950 + 26) - yCamera;
    } while(y > 0 && y < 700);
    p.pos.x = x;
    p.pos.y = y;
  } while(detecter_collision_murs(LR, p.pos, xCamera, yCamera));

  p.srcrect.x = 0;
  p.srcrect.y = 0;
  p.srcrect.w = 229;
  p.srcrect.h = 259;
  p.angle = 0;
  p.vie = 100;
  p.degats = 5;
  p.vitesse = 3;
  p.yMax = 4403;
  p.arme = -1;
  p.tir = false;
  p.ennemi = true;
  p.collision = 0;
  p.animFlip = 1;
  return p;
}

Perso nouvel_ennemi_2(SDL_Renderer *renderer, ListeR LR, SDL_Texture **sprites, int xCamera, int yCamera){
  Perso p;
  p = nouvel_ennemi_1(renderer, LR, sprites, xCamera, yCamera);
  p.vie = 50;
  p.vitesse = 3;
  p.image = sprites[12];
  p.arme = 10;
  return p;
}

void afficher_perso(SDL_Renderer *renderer, Perso p) {
  SDL_RenderCopyEx(renderer, p.image, &p.srcrect, &p.pos, p.angle, NULL, SDL_FLIP_NONE);
  return;
}


void charger_vagues_ennemis(int *tab){
  int n = 1;
  for(int j = 1; j < 101; j++){
    if(j%4 == 0 ){
      n += 1;
    }
    tab[j-1] = j * n;
    printf("%d  %d\n",j-1,j*n);
  }

  return;
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

  SDL_Rect pos = p->pos;
  pos.x += 15;
  pos.w -= 30;
  pos.y -= 3;
  pos.h += 10;
  if(detecter_collision_murs(L, pos, *xCamera, *yCamera)){
    *xCamera -= dX;
    *dxCamera = 0;
    if(detecter_collision_murs(L, pos, *xCamera, *yCamera)){
      *xCamera += dX;
      *dxCamera = dX;
      *yCamera -= dY;
      *dyCamera = 0;
      if(detecter_collision_murs(L, pos, *xCamera, *yCamera)){
        *xCamera -= dX;
        *dxCamera = 0;
      }
    }
  }

  return;
}


void angle_joueur(Perso *p, float mouseX, float mouseY){
  float angle;
  angle = atan2(mouseY - (p->pos.y + p->pos.h/2), mouseX - (p->pos.x + p->pos.w/2));
  angle = (angle * 180.0000)/PI;
  angle -= 2;
  p->angle = angle;
  return;
}

void angle_ennemi(Perso *p){
  float angle;
  angle = atan2(350 - (p->pos.y + 25), 500 - (p->pos.x + 25));
  p->angle = angle;
  return;
}


void detecter_collision_murs_ennemis(ListeR L, Perso *p, int xCamera, int yCamera){
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  while(L != NULL){
    ax1 = p->pos.x + xCamera;
    ax2 = p->pos.x + p->pos.w + xCamera;
    bx1 = L->data.x;
    bx2 = L->data.x + L->data.w;
    ay1 = p->pos.y + yCamera;
    ay2 = p->pos.y + p->pos.h + yCamera;
    by1 = L->data.y;
    by2 = L->data.y + L->data.h;

    if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1){
      if((ax1 + p->vitesse) >= bx2 || (ax2 - p->vitesse) <= bx1){
        p->collision = 1;
      } else if((ay1 + p->vitesse) >= by2 || (ay2 - p->vitesse) <= by1){
        p->collision = 2;
      }
      return;
    }
    L = L->next;
  }
  p->collision = 0;
  return;
}


void changer_arme_joueur(Perso *p, int arme, SDL_Texture **sprites){
  switch(arme){
  case 0:
    p->image = sprites[0];
    p->tempsTirPrecedent = 0;
    break;
  case 1:
    p->image = sprites[10];
    p->tempsTirPrecedent = 0;
    break;
  case 2:
    p->image = sprites[11];
    p->tempsTirPrecedent = 0;
    break;
  }
  return;
}
