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



ListeB incrementer_balles(ListeB LB, ListeP LP, ListeR LR, int v, int xCamera, int yCamera)
{
  if(LB == NULL){
    return LB;
  }

  incrementer_balle(&LB->data, v);

  SDL_Rect ballePos;
  ballePos.w = 1;
  ballePos.h = 1;
  ballePos.x = LB->data.ballePos.x + 20;
  ballePos.y = LB->data.ballePos.y + 20;

  if(ballePos.x < 0 || ballePos.x >= 1000 || ballePos.y <= 0 || ballePos.y >= 700
     || detecter_collision_murs(LR, ballePos, xCamera, yCamera)){
    LB = LB->next;
    return incrementer_balles(LB, LP, LR, v, xCamera, yCamera);
  }

  ballePos.w = 6;
  ballePos.h = 6;
  ballePos.x = LB->data.ballePos.x - 3;
  ballePos.y = LB->data.ballePos.y - 3;

  if(detecter_collision_perso(LP, ballePos, xCamera, yCamera)) {
    LB = LB->next;
    return incrementer_balles(LB, LP, LR, v, xCamera, yCamera);
  }


  LB->next = incrementer_balles(LB->next, LP, LR, v, xCamera, yCamera);
  return LB;


  return NULL;
}

void afficher_listeB(SDL_Renderer *renderer, ListeB L) {
  ListeB tmp = L;
  while(tmp != NULL) {
    afficher_balle(renderer, tmp->data);
    tmp = tmp->next;
  }
}

ListeB tir_update(ListeB LB, ListeP LP, ListeR LR, int time, SDL_Texture *balleLongueJaune, int v, int xCamera, int yCamera){
  //Si perso en train de tirer
  s_ListeP *tmp = LP;
  while(tmp != NULL){
    if(tmp->data.tir){
      //On fait pop une nouvelle balle toutes les X ms
      if(time > tmp->data.tempsTirPrecedent + 200) {
        LB = cons_listeB(LB, nouvelle_balle(balleLongueJaune, tmp->data.angle, tmp->data.pos));
        tmp->data.tempsTirPrecedent = time;
      }
    }
    tmp = tmp->next;
  }
  //On met a jour les coordonnées des balles déjà tirées, dépop si nécéssaire
  LB = incrementer_balles(LB, LP, LR, v, xCamera, yCamera);
  return LB;
}

