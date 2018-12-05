#include "personnage.h"
#include <stdio.h>


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
ListeP deplacement_ennemis(ListeP L, int xCamera, int yCamera, int dxCamera, int dyCamera);
bool detecter_collision_perso(ListeP L, SDL_Rect rect, int xCamera, int yCamera);
void animer_persos(ListeP L);
void animer_persos2(ListeP L);
