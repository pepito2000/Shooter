#include "listeP.h"


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

void deplacement_ennemi(Perso *p, Perso *joueur, int xCamera, int yCamera, int dxCamera, int dyCamera){

  int dX = 0;
  int dY = 0;

  if(p != NULL){
    if(p->ennemi){
      //Màj de la direction du perso
      angle_ennemi(p);
      //Compensation du décalage de la caméra + ajout du déplacement
      dX = p->pos.x + round(-dxCamera + cos(p->angle) * p->vitesse);
      dY = p->pos.y + round(-dyCamera + sin(p->angle) * p->vitesse);
      //if(!detecter_collision_avec_joueur(p, joueur)){
        detecter_collision_avec_joueur(p, joueur);
        p->pos.x = dX;
        p->pos.y = dY;
    //  }

      p->angle = (p->angle * 180.0000)/PI;
    }
  }
  return;
}

void deplacement_ennemis(ListeP L, int xCamera, int yCamera, int dxCamera, int dyCamera){
  Perso *joueur_ptr = joueur(L);
  while(L != NULL){
    if(L->data.vie <= 0 && L->data.ennemi){
      *L = *L->next;
      L = L->next;
    } else {
      deplacement_ennemi(&L->data, joueur_ptr, xCamera, yCamera, dxCamera, dyCamera);

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
    bx1 = L->data.pos.x - 0.3 * L->data.pos.w;
    bx2 = L->data.pos.x + 0.6 * L->data.pos.w;
    ay1 = rect.y;
    ay2 = rect.y;
    by1 = L->data.pos.y - 0.3 * L->data.pos.h;
    by2 = L->data.pos.y + 0.6 * L->data.pos.h;

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

void detecter_collision_avec_joueur(Perso *p, Perso *joueur){

  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;

  ax1 = p->pos.x;
  ax2 = p->pos.x + p->pos.w ;
  bx1 = joueur->pos.x + 0.3 * joueur->pos.w;
  bx2 = joueur->pos.x + 0.7 * joueur->pos.w;
  ay1 = p->pos.y;
  ay2 = p->pos.y + p->pos.h;
  by1 = joueur->pos.y + 0.3 * joueur->pos.h;
  by2 = joueur->pos.y + 0.7 * joueur->pos.h;

  if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1){
    p->tir = true;
    p->vitesse = 1;
  }

  return;
}


void animer_persos(ListeP L, SDL_Texture **sprites, Perso *joueur){

 while(L != NULL){
  if(L->data.ennemi){
    animer_perso(&L->data, joueur, sprites);
  }
  L = L->next;
  }
  return;
}


