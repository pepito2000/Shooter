#include "personnage.h"
#include <stdio.h>
#include "listeE.h"



typedef struct s_ListeP *ListeP, s_ListeP;
struct s_ListeP
{
    ListeP next;
    Perso data;
};



void cons_listeP(ListeP *L, Perso data);
bool vague_terminee(ListeP L);
void afficher_listeP(SDL_Renderer *renderer, ListeP L);
Perso* joueur(ListeP L);
void supprimer_ennemi(ListeP L);
void deplacement_ennemi(Perso *p, Perso *joueur, int xCamera, int yCamera, int dxCamera, int dyCamera);
void deplacement_ennemis(ListeP L, int xCamera, int yCamera, int dxCamera, int dyCamera);
bool detecter_collision_perso(ListeP L, ListeE *LE, SDL_Rect rect, int degats, int xCamera, int yCamera, SDL_Texture **sprites);
void detecter_collision_avec_joueur(Perso *p, Perso *joueur);
void animer_persos(ListeP L, SDL_Texture **sprites, Perso *joueur);
void charger_vague_ennemis(SDL_Renderer *renderer, bool *b, int *vaguesEnnemis, int vagueNum,int xCamera, int yCamera, ListeP *LP, SDL_Texture **sprites);

