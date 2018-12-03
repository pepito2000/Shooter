#include "projectile.h"
#include <stdbool.h>

typedef struct s_ListeB *ListeB, s_ListeB;
struct s_ListeB
{
    ListeB next;
    balle data;
};

ListeB nouvelle_listeB(balle data);
ListeB cons_listeB(ListeB L, balle data);
bool est_vide_listeB(ListeB L);
ListeB incrementer_balles(ListeB L, int v);
void afficher_listeB(SDL_Renderer *renderer, ListeB L);
