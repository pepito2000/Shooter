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

         for(int j = 0; j < 33; j++){

            for(int i = 0; i < 31; i++){
                if(j < 31){

                if(i==0){
                    //caractereActuel = fgetc(fichier);
                    caractereActuel = fgetc(fichier);
                    char tmp = caractereActuel;
                       //                 caractereActuel = fgetc(fichier);
                    caractereActuel = tmp;


                    tab[30*j+i] = caractereActuel;
                    printf("%c", tab[30*j+i]);
                }

                else{
                    caractereActuel = fgetc(fichier);
                    tab[30*j+i] = caractereActuel;
                    printf("%c", tab[30*j+i]);
                }
                }
            }

         }

        fclose(fichier);
  }

  //Remplir la liste de murs
  SDL_Rect rect;
  for(int j = 0; j < 30; j++){
    for(int i = 0; i < 30; i++){
      switch(tab[30*j+i]){
      case 'S':

        break;
      case 'H':
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 25;
        rect.w = 50;
        cons_listeR(L, rect);
        //tab[30*j+i] = 1;
        break;
      case 'V':
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 25;
        cons_listeR(L, rect);
        //tab[30*j+i] = 3;
        break;
      /**
      case '2':
        rect.x = i * 50;
        rect.y = j * 50 + 25;
        rect.h = 25;
        rect.w = 50;
        L = cons_listeR(L, rect);
        break;
      case '3':
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 25;
        L = cons_listeR(L, rect);
        break;
      case '4':
        rect.x = i * 50 + 25;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 25;
        L = cons_listeR(L, rect);
        break;

      case '5':
      case '6':
      case '7':
      case '8':
        rect.x = i * 50;
        rect.y = j * 50;
        rect.h = 50;
        rect.w = 50;
        L = cons_listeR(L, rect);
        break;
      case '0':

        break;
       */
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
