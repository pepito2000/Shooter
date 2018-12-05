#include "listeR.h"



ListeR nouvelle_listeR(SDL_Rect data){
  ListeR L = malloc(sizeof(s_ListeR));
  L->data = data;
  L->next = NULL;
  return L;
}

ListeR cons_listeR(ListeR L, SDL_Rect data){
  ListeR tmp = nouvelle_listeR(data);
  tmp->next = L;
  return tmp;
}


ListeR charger_niveau(int *tab, ListeR L){
  //on met toutes les case � 0 pour dire que tout est du sol (provisoire)
  for(int j = 0; j < 30; j++){
    for(int i = 0; i < 30; i++){
      tab[30*j+i] = 0;
    }
  }

  //ici lire fichier et remplacer les cases qu'il faut par 1-8 pour mettre des murs
  //je mets �a en attendant pour afficher des murs sur le bord de la map
  for(int j = 0; j < 30; j++){
    tab[30*j+0] = 3;
    tab[30*j+29] = 4;
    tab[30*0+j] = 1;
    tab[30*29+j] = 2;
  }
  tab[30*0+0] = 5;
  tab[30*0+29] = 6;
  tab[30*29+0] = 7;
  tab[30*29+29] = 8;

  //Remplir la liste de murs
  SDL_Rect rect;
  for(int j = 0; j < 30; j++){
    for(int i = 0; i < 30; i++){
      switch(tab[30*j+i]){
      case 0:
        break;
      case 1:
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 25;
        rect.w = 50;
        L = cons_listeR(L, rect);
        break;
      case 2:
        rect.x = i * 50;
        rect.y = j * 50 + 25;
        rect.h = 25;
        rect.w = 50;
        L = cons_listeR(L, rect);
        break;
      case 3:
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 25;
        L = cons_listeR(L, rect);
        break;
      case 4:
        rect.x = i * 50 + 25;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 25;
        L = cons_listeR(L, rect);
        break;

      case 5:
      case 6:
      case 7:
      case 8:
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 50;
        L = cons_listeR(L, rect);
        break;
      }
    }
  }
  return L;
}


bool detecter_collision_murs(ListeR L, SDL_Rect rect, int xCamera, int yCamera){
  s_ListeR *tmp = L;
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  while(tmp != NULL){
    ax1 = rect.x + xCamera;
    ax2 = rect.x + rect.w + xCamera;
    bx1 = tmp->data.x;
    bx2 = tmp->data.x + tmp->data.w;
    ay1 = rect.y + yCamera;
    ay2 = rect.y + rect.h + yCamera;
    by1 = tmp->data.y;
    by2 = tmp->data.y + tmp->data.h;
    if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1){
      return true;
    }
    tmp = tmp->next;
  }
  return false;
}
