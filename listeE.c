#include "listeE.h"


void cons_listeE(ListeE *L, Effet data){
  ListeE tmp = malloc(sizeof(s_ListeE));
  tmp->data = data;
  tmp->next = *L;
  *L = tmp;
  return;
}

void animer_effets(ListeE L){
  ListeE tmp;
  while(L != NULL){
    L->data.srcrect.y += L->data.srcrect.h;
    if(L->data.srcrect.y >= L->data.yMax){
      if(L->next == NULL){
        tmp = NULL;
        L = tmp;
      } else {
        tmp = malloc(sizeof(s_ListeE));
        tmp->data = L->next->data;
        tmp->next = L->next->next;
        *L = *tmp;
      }
    } else {
      L = L->next;
    }
  }
  return;
}


void afficher_listeE(SDL_Renderer *renderer, ListeE L, int dxCamera, int dyCamera){
  ListeE tmp = L;
  while(tmp != NULL) {
    tmp->data.pos.x -= dxCamera;
    tmp->data.pos.y -= dyCamera;
    afficher_effet(renderer, tmp->data);
    tmp = tmp->next;
  }
}



