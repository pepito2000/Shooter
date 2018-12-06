#include "effets.h"
#include <stdlib.h>


typedef struct s_ListeE *ListeE, s_ListeE;
struct s_ListeE
{
    ListeE next;
    Effet data;
};

void cons_listeE(ListeE *L, Effet e);
void afficher_listeE(SDL_Renderer *renderer, ListeE L, int dxCamera, int dyCamera);
void animer_effets(ListeE L);
