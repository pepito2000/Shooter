#include "listeR.h"
#include <stdio.h>


void cons_listeR(ListeR *L, SDL_Rect data){
  ListeR tmp = malloc(sizeof(s_ListeR));
  tmp->data = data;
  tmp->next = *L;
  *L = tmp;
  return;
}


void charger_niveau(char *tab, ListeR *L){

  FILE* fichier = NULL;
  fichier = fopen("map.txt", "r");
  int caractereActuel;
  if (fichier != NULL){

   for(int j = 0; j < 63; j++){
      for(int i = 0; i < 61; i++){
        if(j < 61){
          if(i==0){
            caractereActuel = fgetc(fichier);
            char tmp = caractereActuel;
            caractereActuel = tmp;
            tab[60*j+i] = caractereActuel;
            printf("%c", tab[60*j+i]);
          }
          else{
            caractereActuel = fgetc(fichier);
            tab[60*j+i] = caractereActuel;
            printf("%c", tab[60*j+i]);
          }
        }
      }

   }
    fclose(fichier);
  }

  //Remplir la liste de murs
  SDL_Rect rect;
  for(int j = 0; j < 60; j++){
    for(int i = 0; i < 60; i++){
      switch(tab[60*j+i]){
      case '0':
        break;
      case '1':
        //mur du haut
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 25;
        rect.w = 50;
        cons_listeR(L, rect);
        break;
        //mur du bas
      case '2':
        rect.x = i * 50;
        rect.y = j * 50 + 25;
        rect.h = 25;
        rect.w = 50;
        cons_listeR(L, rect);
        break;
      case '3':
        //mur de gauche
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 25;
        cons_listeR(L, rect);
        break;
      case '4':
        //mur de droite
        rect.x = i * 50 + 25;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 25;
        cons_listeR(L, rect);
        break;
      case '5':
        //coin haut gauche
      case '6':
        //coin haut droit
      case '7':
        //coin bas gauche
      case '8':
        //coin bas droit
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 50;
        cons_listeR(L, rect);
        break;
      case 'A':
        //ambulance
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 200;
        rect.w = 100;
        cons_listeR(L, rect);
        break;
      case 'P':
        //police
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 100;
        rect.w = 200;
        cons_listeR(L, rect);
        break;
      case 'E':
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 50;
        cons_listeR(L, rect);
        break;
      case 'C':
        rect.x = i * 50 ;
        rect.y = j * 50;
        rect.h = 250;
        rect.w = 150;
        cons_listeR(L, rect);
        break;
      case 'M':
        rect.x = i * 50 + 25;
        rect.y = j * 50 + 100;
        rect.h = 280;
        rect.w = 410;
        cons_listeR(L, rect);
        rect.x = i * 50 + 220;
        rect.y = j * 50 + 30;
        rect.h = 250;
        rect.w = 300;
        cons_listeR(L, rect);
        break;
      case 'N':
        rect.x = i * 50;
        rect.y = j * 50 + 38;
        rect.h = 325;
        rect.w = 500;
        cons_listeR(L, rect);
        rect.x = i * 50 ;
        rect.y = j * 50 + 325;
        rect.h = 260;
        rect.w = 380;
        cons_listeR(L, rect);
        break;
      case 'L':
        rect.x = i * 50 + 30;
        rect.y = j * 50 + 215;
        rect.h = 360;
        rect.w = 210;
        cons_listeR(L, rect);
        rect.x = i * 50 + 205 ;
        rect.y = j * 50 + 40;
        rect.h = 425;
        rect.w = 570;
        cons_listeR(L, rect);
        break;
      case 'F':
        rect.x = i * 50 + 25;
        rect.y = j * 50 + 25;
        rect.h = 245;
        rect.w = 245;
        cons_listeR(L, rect);
        break;
      }
    }
  }
  return ;
}


bool detecter_collision_murs(ListeR L, SDL_Rect rect, int xCamera, int yCamera){
  int ax1, ax2, bx1, bx2, ay1, ay2, by1, by2;
  while(L != NULL){
    ax1 = rect.x + xCamera;
    ax2 = rect.x + rect.w + xCamera;
    bx1 = L->data.x;
    bx2 = L->data.x + L->data.w;
    ay1 = rect.y + yCamera;
    ay2 = rect.y + rect.h + yCamera;
    by1 = L->data.y;
    by2 = L->data.y + L->data.h;

    if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1){
      return true;
    }
    L = L->next;
  }
  return false;
}

