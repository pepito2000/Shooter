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



ListeB incrementer_balles(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int v, int xCamera, int yCamera, SDL_Texture **sprites)
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
    return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, sprites);
  }

  ballePos.w = 2;
  ballePos.h = 2;
  ballePos.x = LB->data.ballePos.x;
  ballePos.y = LB->data.ballePos.y;


  if(detecter_collision_perso(LP, LE, ballePos, LB->data.angle, LB->data.degats, xCamera, yCamera, sprites)) {
    LB = LB->next;
    return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, sprites);
  }


  LB->next = incrementer_balles(LB->next, LP, LR, LE, v, xCamera, yCamera, sprites);
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

ListeB tir_update(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int time, SDL_Texture *balleLongueJaune, int v, int xCamera, int yCamera, SDL_Texture **sprites, Mix_Chunk **sons){
  //Si perso en train de tirer
  s_ListeP *tmp = LP;
  while(tmp != NULL){
    if(tmp->data.tir && tmp->data.ennemi == false){
      //On fait pop une nouvelle balle toutes les X ms
      if(time > tmp->data.tempsTirPrecedent + 80) {
        cons_listeB(&LB, nouvelle_balle(balleLongueJaune, tmp->data.angle, tmp->data.degats, tmp->data.pos));
        Mix_PlayChannel(1, sons[0], 0);
        tmp->data.tempsTirPrecedent = time;
      }
    }
    tmp = tmp->next;
  }
  //On met a jour les coordonnées des balles déjà tirées, dépop si nécéssaire
  LB = incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, sprites);


  return LB;
}

