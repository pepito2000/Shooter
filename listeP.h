#include "personnage.h"
#include <stdio.h>
#include "listeE.h"



typedef struct s_ListeP *ListeP, s_ListeP;
struct s_ListeP
{
    ListeP next;
    Perso data;
};



ListeP nouvelle_listeP(Perso data);
void cons_listeP(ListeP *L, Perso data);
bool est_vide_listeP(ListeP L);
void afficher_listeP(SDL_Renderer *renderer, ListeP L);
Perso* joueur(ListeP L);
void supprimer_ennemi(ListeP L);
void deplacement_ennemis(ListeP L, int xCamera, int yCamera, int dxCamera, int dyCamera);
bool detecter_collision_perso(ListeP L, ListeE *LE, SDL_Rect rect, int degats, int xCamera, int yCamera, SDL_Texture **sprites);
void animer_persos(ListeP L);


