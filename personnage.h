#include <time.h>
#include <stdio.h>
#include <math.h>
#include "image.h"
#include "listeR.h"

#define PI 3.14159265359



typedef struct s_Personnage Perso;
struct s_Personnage
{
  SDL_Rect pos;
  SDL_Rect srcrect;
  SDL_Texture *image;
  float angle;
  int tempsTirPrecedent;
  int vie;
  int degats;
  int vitesse;
  int animFlip;
  int yMax;
  bool tir;
  bool ennemi;
};


Perso nouveau_joueur(SDL_Renderer *renderer, SDL_Texture **sprites);
Perso nouvel_ennemi_1(SDL_Renderer *renderer, SDL_Texture **sprites, int xCamera, int yCamera);
void afficher_perso(SDL_Renderer *renderer, Perso p);
void charger_vagues_ennemis(int *tab);
void deplacement_joueur(Perso *p, ListeR L, int *xCamera, int *yCamera, int *dxCamera, int *dyCamera);
void angle_ennemi(Perso *p);
void angle_joueur(Perso *p, float mouseX, float mouseY);
void animer_perso(Perso *p, Perso *joueur, SDL_Texture **sprites);

