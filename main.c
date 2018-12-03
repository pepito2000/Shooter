#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "image.h"
#include "clavier.h"


#define RAYON 30.9

int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool gameover = false;
    bool tir = false;
    SDL_Window *fenetre;
    SDL_Event evenements;
    SDL_Renderer *ecran;
    SDL_Texture *fond, *perso, *balleLongueJaune;
    SDL_Rect persoPos;
    float mouseX, mouseY;
    int vitesse = 25, tempsActuel = 0, tempsPrecedent = 0, tempsActuelTir = 0, tempsActuelAnim = 0, tempsPrecedentAnim = 0;
    ListeB ballesTirees;
    ListeP persosListe;
    Perso *joueur_ptr;
    SDL_Texture *sprites[3];
    

    //Initialisation SDL
    if(SDL_Init(SDL_INIT_VIDEO < 0))
    {
      printf("Erreur d'initialisation de la SDL %s", SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }

    IMG_Init(IMG_INIT_PNG);

    //Création fenêtre
    fenetre = SDL_CreateWindow("gameName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 720, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL)
    {
      printf("Erreur d'initialisation de la fenetre %s", SDL_GetError());
      return EXIT_FAILURE;
    }

    //Création renderer
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    //Chargement images
    balleLongueJaune = charger_image("sprites/projectiles/balle/balle_longue_jaune.png", ecran);
    fond = charger_image("sprites/fond.png", ecran);
    perso = charger_image("sprites/perso/handgun/idle/survivor_idle.png", ecran);
    sprites[0] = perso;
    perso = charger_image("sprites/perso/handgun/move/survivor_moving.png", ecran);
    sprites[1] = perso;
    perso = charger_image("sprites/perso/ennemi_1.png", ecran);
    sprites[2] = perso;

    Perso p = nouveau_joueur(ecran , sprites);
    persosListe = nouvelle_listeP(p);
    p = nouvel_ennemi_1(ecran, sprites);
    persosListe = cons_listeP(persosListe, p);

    //Pareil pour la balle + ses autres paramètres (voir projectile.h)
    balle b = nouvelle_balle(balleLongueJaune, 0, persoPos);
    ballesTirees = nouvelle_listeB(b);

    //Boucle de jeu
    while(!gameover)
    {
      //Petit timer pour pas dépasser 60 exécutions/sec (provisoire)
      tempsActuel = SDL_GetTicks();
      if (tempsActuel > tempsPrecedent + 16)
      {
        //Détection événements
        while(SDL_PollEvent(&evenements))
        {
          switch(evenements.type)
          {
            case SDL_QUIT:
              gameover = true;
              break;
            case SDL_MOUSEMOTION:
              mouseX = evenements.motion.x;
              mouseY = evenements.motion.y;
              break;
            case SDL_MOUSEBUTTONDOWN:
              switch(evenements.button.button)
              {
                case SDL_BUTTON_LEFT:
                  tir = true;
                  break;
              }
              break;
            case SDL_MOUSEBUTTONUP:
              switch(evenements.button.button)
              {
                case SDL_BUTTON_LEFT:
                  tir = false;
                  break;
              }
              break;

            case SDL_KEYDOWN:
              switch(evenements.key.keysym.sym)
              {
                case SDLK_ESCAPE:
                  gameover = true;
                  break;
              }
              break;

          }
        }


        joueur_ptr = joueur(persosListe);
        joueur_ptr->tir = tir;

        tempsActuelAnim = SDL_GetTicks();
        if(tempsActuelAnim > tempsPrecedentAnim + 70 ){
          animer_persos(persosListe);
          tempsPrecedentAnim = tempsActuelAnim;
        }



        //Gestion déplacement/angle de tir
        deplacement_joueur(joueur_ptr);
        angle_joueur((joueur_ptr), mouseX, mouseY);

        //Tir
        tempsActuelTir = SDL_GetTicks();
        ballesTirees = tir_update(ballesTirees, persosListe, tempsActuelTir, balleLongueJaune, vitesse);
	
	
        //Affichage
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, fond, NULL, NULL);
        afficher_listeP(ecran, persosListe);
        afficher_listeB(ecran, ballesTirees);
        SDL_RenderPresent(ecran);
        tempsPrecedent = tempsActuel;
      }
    }

    //Nettoyage
    SDL_DestroyWindow(fenetre);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(perso);
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
