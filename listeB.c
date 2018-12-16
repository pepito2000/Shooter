#include "listeB.h"


void cons_listeB(ListeB *L, balle data){
  ListeB tmp = malloc(sizeof(s_ListeB));
  tmp->data = data;
  tmp->next = *L;
  *L = tmp;
  return;
}

bool est_vide_listeB(ListeB L) {
  return (L == NULL);
}



ListeB incrementer_balles(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int v, int xCamera, int yCamera, int dxCamera, int dyCamera, int *nbTues, SDL_Texture **sprites, Perso *joueur)
{
  if(LB == NULL){
    return LB;
  }

  SDL_Rect ballePos;
  ballePos.w = 1;
  ballePos.h = 1;

  if(LB->data.ennemi == false){
    incrementer_balle(&LB->data, v, dxCamera, dyCamera);
    if(LB->data.angle >= -45 && LB->data.angle < 45){
      ballePos.x = LB->data.ballePos.x + 50;
      ballePos.y = LB->data.ballePos.y + 15;
    } else if(LB->data.angle >= 45 && LB->data.angle < 135){
      ballePos.x = LB->data.ballePos.x + 30;
      ballePos.y = LB->data.ballePos.y + 30;
    } else if(LB->data.angle >= -135 && LB->data.angle < -45){
      ballePos.x = LB->data.ballePos.x + 35;
      ballePos.y = LB->data.ballePos.y;
    } else {
      ballePos.x = LB->data.ballePos.x + 15;
      ballePos.y = LB->data.ballePos.y;
    }

    if(ballePos.x < 0 || ballePos.x >= 1000 || ballePos.y <= 0 || ballePos.y >= 700
    || detecter_collision_murs(LR, ballePos, xCamera, yCamera)){
      LB = LB->next;
      return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, dxCamera, dyCamera, nbTues, sprites, joueur);
    }

    ballePos.w = 2;
    ballePos.h = 2;
    ballePos.x = LB->data.ballePos.x;
    ballePos.y = LB->data.ballePos.y;

    if(detecter_collision_perso(LP, LE, ballePos, LB->data.angle, LB->data.degats, xCamera, yCamera, nbTues, sprites)) {
      LB = LB->next;
      return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, dxCamera, dyCamera, nbTues, sprites, joueur);
    }
  } else {
    incrementer_balle(&LB->data, 4, dxCamera, dyCamera);
    if(detecter_collision_murs(LR, LB->data.ballePos, xCamera, yCamera)){
      LB = LB->next;
      return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, dxCamera, dyCamera, nbTues, sprites, joueur);
    }
    if(detecter_collision_balle_avec_joueur(LB->data.ballePos, LB->data.degats, joueur)){
      LB = LB->next;
      return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, dxCamera, dyCamera, nbTues, sprites, joueur);
    }
  }

  LB->next = incrementer_balles(LB->next, LP, LR, LE, v, xCamera, yCamera, dxCamera, dyCamera, nbTues, sprites, joueur);
  return LB;
}

void afficher_listeB(SDL_Renderer *renderer, ListeB L) {
  ListeB tmp = L;
  while(tmp != NULL) {
    afficher_balle(renderer, tmp->data);
    tmp = tmp->next;
  }
}

ListeB tir_update(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int time, int v, int xCamera, int yCamera, int dxCamera, int dyCamera, int *nbTues, SDL_Texture **sprites, Mix_Chunk **sons, Perso *joueur){
  s_ListeP *tmp = LP;
  while(tmp != NULL){
    if(tmp->data.tir){
      int arme;
      balle b;
      arme = tmp->data.arme;
      switch(arme){
      case 0:
        if(time > tmp->data.tempsTirPrecedent + 300){
          cons_listeB(&LB, nouvelle_balle(sprites[7], tmp->data.angle, 50, tmp->data.pos));
          Mix_PlayChannel(1, sons[0], 0);
          tmp->data.tempsTirPrecedent = time;
        }
        break;
      case 1:
        if(time > tmp->data.tempsTirPrecedent + 1500){
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle - 1.5, 100, tmp->data.pos));
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle + 1.5, 100, tmp->data.pos));
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle - 3, 100, tmp->data.pos));
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle + 3, 100, tmp->data.pos));
          Mix_PlayChannel(1, sons[1], 0);
          tmp->data.tempsTirPrecedent = time;
        }
        break;
      case 2:
        if(time > tmp->data.tempsTirPrecedent + 80){
          cons_listeB(&LB, nouvelle_balle(sprites[9], tmp->data.angle, 25, tmp->data.pos));
          Mix_PlayChannel(1, sons[2], 0);
          tmp->data.tempsTirPrecedent = time;
        }
        break;
      case -10:
        b = nouvelle_balle(sprites[14], tmp->data.angle, 10, tmp->data.pos);
        b.ennemi = true;
        b.ballePos.x += 10;
        b.ballePos.y += 10;
        b.ballePos.w = 30;
        b.ballePos.h = 30;
        b.srcrect.w = 250;
        b.srcrect.h = 251;
        cons_listeB(&LB, b);
        tmp->data.arme = 10;
        tmp->data.tir = false;
        tmp->data.image = sprites[12];
        tmp->data.pos.w = 50;
        tmp->data.pos.h = 50;
        tmp->data.srcrect.w = 229;
        tmp->data.srcrect.h = 259;
        tmp->data.srcrect.y = 0;
        tmp->data.yMax = 4403;
        tmp->data.animFlip = 1;
        tmp->data.vitesse = 2;
      default:
        break;
      }
    } else {
      if(time > tmp->data.tempsTirPrecedent + 2000 && tmp->data.arme == 10){
        if(tmp->data.collision == false && tmp->data.pos.x > 100 &&
          tmp->data.pos.x < 900 && tmp->data.pos.y > 100 && tmp->data.pos.y < 600){
          tmp->data.tir = true;
          tmp->data.arme = 100;
          tmp->data.vitesse = 0;
          tmp->data.tempsTirPrecedent = time;
        }
      }
    }
    tmp = tmp->next;
  }
  LB = incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, dxCamera, dyCamera, nbTues, sprites, joueur);
  return LB;
}

void animer_balles(ListeB LB){
  while(LB != NULL){
    if(LB->data.ennemi){
      LB->data.srcrect.y += LB->data.srcrect.h;
      if(LB->data.srcrect.y > 7 * LB->data.srcrect.h){
        LB->data.srcrect.y = 0;
      }
    }
    LB = LB->next;
  }
  return;
}

void animer_ennemi_2(ListeB LB, Perso *p, SDL_Texture **sprites){

  if(!p->tir){
    p->srcrect.y += p->srcrect.h * p->animFlip;
    if((p->srcrect.y >= p->yMax || p->srcrect.y < 0) && !p->tir){
      p->animFlip = -p->animFlip;
      p->srcrect.y += p->srcrect.h * p->animFlip;
    }
  } else {
    if(p->arme == 100){
      p->image = sprites[13];
      p->pos.w = 60;
      p->pos.h = 60;
      p->srcrect.w = 318;
      p->srcrect.h = 294;
      p->srcrect.y = 0;
      p->yMax = 2646;
      p->animFlip = 1;
      p->arme = 101;
    } else if(p->arme == 101){
      p->srcrect.y += p->srcrect.h;
      if(p->srcrect.y >= p->yMax){
        p->arme = -10;
      }
    }
  }

  return;
}

void animer_ennemi_1(Perso *p, Perso *joueur, SDL_Texture **sprites){
  if(p->tir){
    if(p->arme == -1){
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
          p->vitesse = 3;
        }
      }
    }
  } else {
    p->srcrect.y += p->srcrect.h * p->animFlip;
    if((p->srcrect.y >= p->yMax || p->srcrect.y < 0) && !p->tir){
      p->animFlip = -p->animFlip;
      p->srcrect.y += p->srcrect.h * p->animFlip;
    }
  }
  return;
}

void animer_persos(ListeP L, ListeB LB, SDL_Texture **sprites, Perso *joueur){

 while(L != NULL){
  if(L->data.ennemi){
    if(L->data.arme == -1){
      animer_ennemi_1(&L->data, joueur, sprites);
    } else {
      animer_ennemi_2(LB, &L->data, sprites);
    }
  }
  L = L->next;
  }
  return;
}

