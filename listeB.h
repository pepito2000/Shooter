#include <stdio.h>
#include "projectile.h"
#include "listeP.h"

typedef struct s_ListeB *ListeB, s_ListeB;
struct s_ListeB
{
    ListeB next;
    balle data;
};

ListeB nouvelle_listeB(balle data);
ListeB cons_listeB(ListeB L, balle data);
bool est_vide_listeB(ListeB L);
ListeB incrementer_balles(ListeB LB, ListeP LP, ListeR LR, int v, int xCamera, int yCamera);
void afficher_listeB(SDL_Renderer *renderer, ListeB L);
ListeB tir_update(ListeB LB, ListeP LP, ListeR LR, int time, SDL_Texture *balleLongueJaune, int v, int xCamera, int yCamera);
