#include <stdio.h>
#include <stdlib.h>
#include "listeB.h"

ListeB nouvelle_listeB(balle data){
  ListeB L = malloc(sizeof(s_ListeB));
  L->data = data;
  L->next = NULL;
  return L;
}

ListeB cons_listeB(ListeB L, balle data){
  ListeB tmp;
  tmp = nouvelle_listeB(data);
  tmp->next = L;
  return tmp;
}

bool est_vide_listeB(ListeB L) {
  return (L == NULL);
}


ListeB incrementer_balles(ListeB L, int v)
{
  if(L == NULL){
    return L;
  }

  //L->data = incrementer_balle(L->data, v);
  incrementer_balle(&L->data, v);

  if(L->data.ballePos.x <= -60 || L->data.ballePos.x >= 1000 || L->data.ballePos.y <= -60 || L->data.ballePos.y >= 720){
    L = L->next;
    return incrementer_balles(L, v);
  } else {
    L->next = incrementer_balles(L->next, v);
    return L;
  }

  return NULL;
}

void afficher_listeB(SDL_Renderer *renderer, ListeB L) {
  ListeB tmp = L;
  while(tmp != NULL) {
    afficher_balle(renderer, tmp->data);
    tmp = tmp->next;
  }
}

