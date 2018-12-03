#include "personnage.h"
#include <stdbool.h>

typedef struct s_ListeP *ListeP, s_ListeP;
struct s_ListeP
{
    ListeP next;
    Perso data;
};

ListeP nouvelle_listeP(Perso data);
ListeP cons_listeP(ListeP L, Perso data);
bool est_vide_listeP(ListeP L);
void afficher_listeP(SDL_Renderer *renderer, ListeP L);
Perso* joueur(ListeP L);


