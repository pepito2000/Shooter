#include "listeP.h"
#include <stdio.h>
#include "projectile.h"



typedef struct s_ListeB *ListeB, s_ListeB;
struct s_ListeB
{
    ListeB next;
    balle data;
};


void cons_listeB(ListeB *L, balle data);
bool est_vide_listeB(ListeB L);
ListeB incrementer_balles(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int v, int xCamera, int yCamera, int *nbTues, SDL_Texture **sprites);
void afficher_listeB(SDL_Renderer *renderer, ListeB L);
ListeB tir_update(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int time, int v, int xCamera, int yCamera, int *nbTues, SDL_Texture **sprites, Mix_Chunk **sons);


