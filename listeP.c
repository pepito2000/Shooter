#include "listeP.h"



ListeP nouvelle_listeP(Perso data){
  ListeP L = malloc(sizeof(s_ListeP));
  L->data = data;
  L->next = NULL;
  return L;
}

void cons_listeP(ListeP *L, Perso data){
  ListeP tmp = malloc(sizeof(s_ListeP));
  tmp->data = data;
  tmp->next = *L;
  *L = tmp;
  return;
}



bool est_vide_listeP(ListeP L){
  return (L == NULL);
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


void deplacement_ennemis(ListeP L, int xCamera, int yCamera, int dxCamera, int dyCamera){
  while(L != NULL){
    if(L->data.vie <= 0){
      *L = *L->next;
      L = L->next;
    } else {
      deplacement_ennemi(&L->data, xCamera, yCamera, dxCamera, dyCamera);
      L = L->next;
    }
  }
  return;
}

bool detecter_collision_perso(ListeP L, ListeE *LE, SDL_Rect rect, int degats, int xCamera, int yCamera, SDL_Texture **sprites){
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  Effet e;
  while(L != NULL){
    ax1 = rect.x;
    ax2 = rect.x + rect.w ;
    bx1 = L->data.pos.x;
    bx2 = L->data.pos.x + L->data.pos.w;
    ay1 = rect.y;
    ay2 = rect.y;
    by1 = L->data.pos.y;
    by2 = L->data.pos.y + L->data.pos.h;

    if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1 && L->data.ennemi){
      L->data.vie -= degats;
      e = nouvel_effet_bloodHit(sprites, L->data.pos, L->data.angle);
      cons_listeE(LE, e);
      return true;
    }
    L = L->next;
  }
  return false;

}

void animer_persos(ListeP L){
 while(L != NULL){
    if(L->data.ennemi){
      animer_perso(&L->data);
    }
    L = L->next;
  }
  return;
}


