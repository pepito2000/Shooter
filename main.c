#include "image.h"
#include "listeB.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool gameover, tir, exit;
    SDL_Window *fenetre;
    SDL_Event evenements;
    SDL_Renderer *ecran;
    SDL_Texture *tmp, *balleSprite, *sprites[4], *spritesMap[9];
    float mouseX, mouseY;
    int vitesse, tempsActuel, tempsPrecedent, tempsActuelTir, tempsActuelAnim, tempsPrecedentAnim,
        xCamera, yCamera, dxCamera, dyCamera, map[30][30]; ;
    ListeB ballesTirees;
    ListeP persosListe;
    ListeR mursListe;
    ListeE effetsListe;
    Perso p, *joueur_ptr;



    //Initialisation SDL
    if(SDL_Init(SDL_INIT_VIDEO < 0))
    {
      printf("Erreur d'initialisation de la SDL %s", SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }

    //Initialisation SDL_image (PNG)
    IMG_Init(IMG_INIT_PNG);

    //Création fenêtre
    fenetre = SDL_CreateWindow("gameName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL)
    {
      printf("Erreur d'initialisation de la fenetre %s", SDL_GetError());
      return EXIT_FAILURE;
    }

    //Création renderer
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    //Chargement images
    balleSprite = charger_image("sprites/projectiles/balle/balle_longue_jaune.png", ecran, 255, 255, 255);
    //Murs + Sols
    spritesMap[0] = charger_image("sprites/map/sol.png", ecran, 0, 0, -1);
    spritesMap[1] = charger_image("sprites/map/mur_h.png", ecran, 255, 255, 255);
    spritesMap[2] = charger_image("sprites/map/mur_b.png", ecran, 255, 255, 255);
    spritesMap[3] = charger_image("sprites/map/mur_g.png", ecran, 255, 255, 255);
    spritesMap[4] = charger_image("sprites/map/mur_d.png", ecran, 255, 255, 255);
    spritesMap[5] = charger_image("sprites/map/mur_hg.png", ecran, 255, 255, 255);
    spritesMap[6] = charger_image("sprites/map/mur_hd.png", ecran, 255, 255, 255);
    spritesMap[7] = charger_image("sprites/map/mur_bg.png", ecran, 255, 255, 255);
    spritesMap[8] = charger_image("sprites/map/mur_bd.png", ecran, 255, 255, 255);

    //Personnages + Effets
    tmp = charger_image("sprites/perso/handgun/idle/survivor_idle.png", ecran, 255, 255, 255);
    sprites[0] = tmp;
    tmp = charger_image("sprites/ennemis/zombie/move/zombie_moveV2.png", ecran, 0, 0, -1);
    sprites[1] = tmp;
    tmp = charger_image("sprites/ennemis/zombie/attack/zombie_attack.png", ecran, 0, 0, -1);
    sprites[2] = tmp;
    tmp = charger_image("sprites/effets/blood/blood_hitv3.png", ecran, 0, 0, -1);
    sprites[3] = tmp;

    exit = false;

    while(!exit){

      gameover = false;
      tir = false;

      vitesse = 25;
      tempsActuel = 0;
      tempsPrecedent = 0;
      tempsActuelTir = 0;
      tempsActuelAnim = 0;
      tempsPrecedentAnim = 0;
      xCamera = 0;
      yCamera = 0;
      dxCamera = 0;
      dyCamera = 0;

      mursListe = NULL;
      ballesTirees = NULL;
      effetsListe = NULL;
      persosListe = NULL;
      joueur_ptr = NULL;

      charger_niveau(map[0], &mursListe);

      p = nouveau_joueur(ecran, sprites);
      cons_listeP(&persosListe, p);
      p = nouvel_ennemi_1(ecran, sprites);
      cons_listeP(&persosListe, p);
      p = nouvel_ennemi_1(ecran, sprites);
      cons_listeP(&persosListe, p);
      p = nouvel_ennemi_1(ecran, sprites);
      cons_listeP(&persosListe, p);
      p = nouvel_ennemi_1(ecran, sprites);
      cons_listeP(&persosListe, p);



      //Boucle de jeu
      while(!gameover)
      {
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
                exit = true;
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
                    exit = true;
                    break;
                }
                break;

            }
          }


          joueur_ptr = joueur(persosListe);
          if(joueur_ptr != NULL){
            //Gestion déplacement/angle de tir
            joueur_ptr->tir = tir;
            deplacement_joueur(joueur_ptr, mursListe, &xCamera, &yCamera, &dxCamera, &dyCamera);
            angle_joueur((joueur_ptr), mouseX, mouseY);
          }


          tempsActuelAnim = SDL_GetTicks();
          if(tempsActuelAnim > tempsPrecedentAnim + 40 ){
            animer_persos(persosListe, sprites, joueur_ptr);
            animer_effets(effetsListe);
            tempsPrecedentAnim = tempsActuelAnim;
          }

          //Détection mort joueur
          if(joueur_ptr->vie <= 0){
            gameover = true;
          }


          //Déplacement/angle de tir ennemis
          deplacement_ennemis(persosListe, xCamera, yCamera, dxCamera, dyCamera);

          //Tir
          tempsActuelTir = SDL_GetTicks();
          ballesTirees = tir_update(ballesTirees, persosListe, mursListe, &effetsListe, tempsActuelTir, balleSprite, vitesse, xCamera, yCamera, sprites);

          //Affichage
          SDL_RenderClear(ecran);
          afficher_niveau(map[0], ecran, spritesMap, xCamera, yCamera);
          afficher_listeE(ecran, effetsListe, dxCamera, dyCamera);
          afficher_listeP(ecran, persosListe);
          afficher_listeB(ecran, ballesTirees);
          SDL_RenderPresent(ecran);

          tempsPrecedent = tempsActuel;
        }
      }

      if(gameover)
      printf("gameover :(\n");

    }

    //Nettoyage
    SDL_DestroyWindow(fenetre);
    SDL_DestroyTexture(balleSprite);;
    SDL_DestroyTexture(tmp);
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
