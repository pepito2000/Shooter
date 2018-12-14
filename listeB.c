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



ListeB incrementer_balles(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int v, int xCamera, int yCamera, int *nbTues, SDL_Texture **sprites)
{
  if(LB == NULL){
    return LB;
  }

  incrementer_balle(&LB->data, v);

  SDL_Rect ballePos;
  ballePos.w = 1;
  ballePos.h = 1;
  if(LB->data.angle >= -45 && LB->data.angle < 45){
    ballePos.x = LB->data.ballePos.x + 50;
    ballePos.y = LB->data.ballePos.y + 15;
  } else if(LB->data.angle >= 45 && LB->data.angle < 135){
    ballePos.x = LB->data.ballePos.x + 30;
    ballePos.y = LB->data.ballePos.y + 30;
  } else if(LB->data.angle >= -135 && LB->data.angle < -45){
    ballePos.x = LB->data.ballePos.x + 35;
    ballePos.y = LB->data.ballePos.y;
  } else {
    ballePos.x = LB->data.ballePos.x + 15;
    ballePos.y = LB->data.ballePos.y;
  }

  if(ballePos.x < 0 || ballePos.x >= 1000 || ballePos.y <= 0 || ballePos.y >= 700
     || detecter_collision_murs(LR, ballePos, xCamera, yCamera)){
    LB = LB->next;
    return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, nbTues, sprites);
  }

  ballePos.w = 2;
  ballePos.h = 2;
  ballePos.x = LB->data.ballePos.x;
  ballePos.y = LB->data.ballePos.y;

  if(detecter_collision_perso(LP, LE, ballePos, LB->data.angle, LB->data.degats, xCamera, yCamera, nbTues, sprites)) {
    LB = LB->next;
    return incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, nbTues, sprites);
  }

  LB->next = incrementer_balles(LB->next, LP, LR, LE, v, xCamera, yCamera, nbTues, sprites);
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

ListeB tir_update(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int time, int v, int xCamera, int yCamera, int *nbTues, SDL_Texture **sprites, Mix_Chunk **sons){
  s_ListeP *tmp = LP;
  while(tmp != NULL){
    if(tmp->data.tir && tmp->data.ennemi == false){
      int arme;
      arme = tmp->data.arme;
      switch(arme){
      case 0:
        if(time > tmp->data.tempsTirPrecedent + 300){
          cons_listeB(&LB, nouvelle_balle(sprites[7], tmp->data.angle, 25, tmp->data.pos));
          Mix_PlayChannel(1, sons[0], 0);
          tmp->data.tempsTirPrecedent = time;
        }
        break;
      case 1:
        if(time > tmp->data.tempsTirPrecedent + 1500){
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle - 1.5, 100, tmp->data.pos));
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle + 1.5, 100, tmp->data.pos));
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle - 3, 100, tmp->data.pos));
          cons_listeB(&LB, nouvelle_balle(sprites[8], tmp->data.angle + 3, 100, tmp->data.pos));
          Mix_PlayChannel(1, sons[1], 0);
          tmp->data.tempsTirPrecedent = time;
        }
        break;
      case 2:
        if(time > tmp->data.tempsTirPrecedent + 80){
          cons_listeB(&LB, nouvelle_balle(sprites[9], tmp->data.angle, 25, tmp->data.pos));
          Mix_PlayChannel(1, sons[2], 0);
          tmp->data.tempsTirPrecedent = time;
        }
        break;
      }
    }
    tmp = tmp->next;
  }

  LB = incrementer_balles(LB, LP, LR, LE, v, xCamera, yCamera, nbTues, sprites);

  return LB;
}

