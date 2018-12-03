#include <SDL2/SDL.h>
#include <stdbool.h>
#include "image.h"

typedef enum AnimationType Anim;
enum AnimationType
{
    IDLE, MOUVEMENT, TIR, CUT, MORT
};

typedef struct s_Personnage Perso;
struct s_Personnage
{
  SDL_Rect pos;
  SDL_Rect srcrect;
  SDL_Texture *image;
  float angle;
  int tempsTirPrecedent;
  int vie;
  int vitesse;
  int animFlip;
  bool tir;
  bool ennemi;
  Anim anim;
};


Perso nouveau_joueur(SDL_Renderer *renderer, SDL_Texture **sprites);
Perso nouvel_ennemi_1(SDL_Renderer *renderer, SDL_Texture **sprites);
void afficher_perso(SDL_Renderer *renderer, Perso p);
void deplacement_joueur(Perso *p, SDL_Rect *tabMur);
void angle_joueur(Perso *p, float mouseX, float mouseY);
void animer_perso(Perso *p);
