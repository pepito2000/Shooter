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
  int arme;
  int collision;
  bool tir;
  bool ennemi;
};


Perso nouveau_joueur(SDL_Renderer *renderer, SDL_Texture **sprites);
Perso nouvel_ennemi_1(SDL_Renderer *renderer, ListeR LR, SDL_Texture **sprites, int xCamera, int yCamera);
Perso nouvel_ennemi_2(SDL_Renderer *renderer, ListeR LR, SDL_Texture **sprites, int xCamera, int yCamera);
void afficher_perso(SDL_Renderer *renderer, Perso p);
void charger_vagues_ennemis(int *tab);
void deplacement_joueur(Perso *p, ListeR L, int *xCamera, int *yCamera, int *dxCamera, int *dyCamera);
void angle_ennemi(Perso *p);
void angle_joueur(Perso *p, float mouseX, float mouseY);
void detecter_collision_murs_ennemis(ListeR L, Perso *p, int xCamera, int yCamera);
void changer_arme_joueur(Perso *p, int arme, SDL_Texture **sprites);
