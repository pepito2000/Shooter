#include "listeP.h"


void cons_listeP(ListeP *L, Perso data){
  ListeP tmp = malloc(sizeof(s_ListeP));
  tmp->data = data;
  tmp->next = *L;
  *L = tmp;
  return;
}



bool vague_terminee(ListeP L){
  ListeP tmp = L;
  while(tmp != NULL){
    if(tmp->data.ennemi){
      return false;
    }
    tmp = tmp->next;
  }
  return true;
}

void afficher_listeP(SDL_Renderer *renderer, ListeP L){

  ListeP tmp = L;
  while(tmp != NULL) {
    afficher_perso(renderer, tmp->data);
    tmp = tmp->next;
  }
}

Perso* joueur(ListeP L){

  while(L != NULL){
    if(L->data.ennemi == false){
      return &L->data;
    }
    L = L->next;
  }
  return NULL;
}

void deplacement_ennemi(Perso *p, ListeR LR, Perso *joueur, int xCamera, int yCamera, int dxCamera, int dyCamera){

  if(p != NULL){
    if(p->ennemi){
      angle_ennemi(p);
      if(p->collision == 0){
        detecter_collision_murs_ennemis(LR, p, xCamera, yCamera);
        p->pos.x = p->pos.x + round(-dxCamera + cos(p->angle) * p->vitesse);
        p->pos.y = p->pos.y + round(-dyCamera + sin(p->angle) * p->vitesse);
      } if(p->collision == 1){
        if(joueur->pos.y - p->pos.y < 0){
          p->pos.y -= p->vitesse;
        } else{
          p->pos.y += p->vitesse;
        }
        p->pos.x -= dxCamera;
        p->pos.y -= dyCamera;
        if(!detecter_collision_murs(LR, p->pos, xCamera, yCamera)){
          p->collision = 0;
        }
      } if(p->collision == 2){
        if(joueur->pos.x - p->pos.x < 0){
          p->pos.x -= p->vitesse;
        } else{
          p->pos.x += p->vitesse;
        }
        p->pos.x -= dxCamera;
        p->pos.y -= dyCamera;
        if(!detecter_collision_murs(LR, p->pos, xCamera, yCamera)){
          p->collision = 0;
        }
      }
      detecter_collision_avec_joueur(p, joueur);
      p->angle = (p->angle * 180.0000)/PI;
    }
  }
  return;

}

void deplacement_ennemis(ListeP LP, ListeR LR, ListeE *LE, SDL_Texture **sprites, int xCamera, int yCamera, int dxCamera, int dyCamera){
  Perso *joueur_ptr = joueur(LP);
  while(LP != NULL){
    deplacement_ennemi(&LP->data, LR, joueur_ptr, xCamera, yCamera, dxCamera, dyCamera);
    LP = LP->next;
  }
  return;
}

bool detecter_collision_perso(ListeP L, ListeE *LE, SDL_Rect rect, int angle, int degats, int xCamera, int yCamera, int *nbTues, SDL_Texture **sprites){
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  Effet e;
  while(L != NULL){
    ax1 = rect.x;
    ax2 = rect.x + rect.w;
    bx1 = L->data.pos.x ;
    bx2 = L->data.pos.x + L->data.pos.w;
    ay1 = rect.y;
    ay2 = rect.y + rect.h;
    by1 = L->data.pos.y;
    by2 = L->data.pos.y + L->data.pos.h;
    //correction hitbox
    if(angle >= -45 && angle < 45){
      by1 -= 0.4 * L->data.pos.h;
      by2 -= 0.4 * L->data.pos.h;
      bx1 -= 0.8 * L->data.pos.w;
    } else if(angle >= 45 && angle < 135){
      bx1 -= 0.4 * L->data.pos.w;
      bx2 -= 0.6 * L->data.pos.w;
      by1 -= 0.5 * L->data.pos.h;
    } else if(angle >= -135 && angle < -45){
      bx1 -= 0.7 * L->data.pos.w;
      bx2 -= 0.9 * L->data.pos.w;
    } else {
      by1 -= 0.1 * L->data.pos.h;
      by2 -= 0.3 * L->data.pos.h;
      bx2 -= 0.5 * L->data.pos.w;
      bx1 -= 0.5 * L->data.pos.w;
    }

    if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1 && L->data.ennemi){
      L->data.vie -= degats;
      e = nouvel_effet_bloodHit(sprites, L->data.pos, L->data.angle);
      cons_listeE(LE, e);

      if(L->data.vie <= 0){
        e = nouvel_effet_bloodSplatter(sprites, L->data.pos, L->data.angle);
        cons_listeE(LE, e);
        *nbTues += 1;
        *L = *L->next;
      }
      return true;
    }
    L = L->next;
  }
  return false;

}

void detecter_collision_avec_joueur(Perso *p, Perso *joueur){
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  ax1 = p->pos.x;
  ax2 = p->pos.x + p->pos.w ;
  bx1 = joueur->pos.x + round(0.24 * joueur->pos.w);
  bx2 = joueur->pos.x + round(0.75 * joueur->pos.w);
  ay1 = p->pos.y;
  ay2 = p->pos.y + p->pos.h;
  by1 = joueur->pos.y;
  by2 = joueur->pos.y + joueur->pos.h;

  if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1){
    p->tir = true;
    p->vitesse = 1;
  }

  return;
}


void charger_vague_ennemis(SDL_Renderer *renderer, bool *b, int *vaguesEnnemis, int vagueNum, int xCamera, int yCamera, ListeP *LP, ListeR LR,SDL_Texture **sprites){
    if(vaguesEnnemis[vagueNum] > 0){
      cons_listeP(LP, nouvel_ennemi_1(renderer, LR, sprites, xCamera, yCamera));
      int nb = rand()%4 + 1;
      if(nb == 1){
        cons_listeP(LP, nouvel_ennemi_2(renderer, LR, sprites, xCamera, yCamera));
      }
      vaguesEnnemis[vagueNum] -= 1;
  } else {
    *b = true;
  }
  return;
}

bool detecter_collision_balle_avec_joueur(SDL_Rect pos, int degats, Perso *joueur){
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  ax1 = pos.x;
  ax2 = pos.x + pos.w ;
  bx1 = joueur->pos.x + round(0.24 * joueur->pos.w);
  bx2 = joueur->pos.x + round(0.75 * joueur->pos.w);
  ay1 = pos.y;
  ay2 = pos.y + pos.h;
  by1 = joueur->pos.y;
  by2 = joueur->pos.y + joueur->pos.h;

  if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1){
    joueur->vie -= degats;
    return true;
  }
  return false;
}



