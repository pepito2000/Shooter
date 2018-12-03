#include <SDL2/SDL.h>
#include "clavier.h"


/* FICHIER A RENOMMER */


ListeB tir_update(ListeB LB, ListeP LP, int time, SDL_Texture *balleLongueJaune, int v){
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
  LB = incrementer_balles(LB, v);
  return LB;
}

void animer_persos(ListeP L){
  s_ListeP *tmp = L;
  tmp = tmp->next;
  animer_perso(&tmp->data);
  return;
}
