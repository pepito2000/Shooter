#include "listeP.h"



ListeP nouvelle_listeP(Perso data){
  ListeP L = malloc(sizeof(s_ListeP));
  L->data = data;
  L->next = NULL;
  return L;
}

ListeP cons_listeP(ListeP L, Perso data){
  ListeP tmp = nouvelle_listeP(data);
  tmp->next = L;
  return tmp;
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
  s_ListeP *tmp = L;
  while(tmp != NULL){
    if(tmp->data.ennemi == false){
      return &tmp->data;
    }
    tmp = tmp->next;
  }
  return NULL;
}



ListeP deplacement_ennemis(ListeP L, int xCamera, int yCamera, int dxCamera, int dyCamera){

  if(L == NULL){
    return L;
  }

  s_ListeP *tmp = L;
  while(tmp != NULL){
    deplacement_ennemi(&tmp->data, xCamera, yCamera, dxCamera, dyCamera);
    tmp = tmp->next;
  }

  return L;

}

bool detecter_collision_perso(ListeP L, SDL_Rect rect, int xCamera, int yCamera){
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  while(L != NULL){
    ax1 = rect.x;//+ xCamera;
    ax2 = rect.x + rect.w ;//+ xCamera;
    bx1 = L->data.pos.x;
    bx2 = L->data.pos.x + L->data.pos.w;
    ay1 = rect.y;// + yCamera;
    ay2 = rect.y;// + rect.h + yCamera;
    by1 = L->data.pos.y;
    by2 = L->data.pos.y + L->data.pos.h;
    if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1 && L->data.ennemi){
      return true;
    }
    L = L->next;
  }
  return false;

}

void animer_persos2(ListeP L){
 while(L != NULL){
    if(L->data.ennemi){
      animer_perso(&L->data);
    }
    L = L->next;
  }
}

void animer_persos(ListeP L){

  animer_persos2(L);
  return;
}

