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
ListeB incrementer_balles(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int v, int xCamera, int yCamera, int dxCamera, int dyCamera, int *nbTues, SDL_Texture **sprites, Perso *joueur);
void afficher_listeB(SDL_Renderer *renderer, ListeB L);
ListeB tir_update(ListeB LB, ListeP LP, ListeR LR, ListeE *LE, int time, int v, int xCamera, int yCamera, int dxCamera, int dyCamera, int *nbTues, SDL_Texture **sprites, Mix_Chunk **sons, Perso *joueur);
void animer_balles(ListeB LB);
void animer_ennemi_1(Perso *p, Perso *joueur, SDL_Texture **sprites);
void animer_ennemi_2(ListeB LB, Perso *p, SDL_Texture **sprites);
void animer_persos(ListeP L, ListeB LB, SDL_Texture **sprites, Perso *joueur);

