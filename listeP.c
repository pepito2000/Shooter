#include <stdio.h>
#include <stdlib.h>
#include "listeP.h"

ListeP nouvelle_listeP(Perso data){
  ListeP L = malloc(sizeof(s_ListeP));
  L->data = data;
  L->next = NULL;
  return L;

};

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
