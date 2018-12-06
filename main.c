#include "image.h"
#include "listeB.h"


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
    ListeR mursListe;
    ListeE effetsListe;
    Perso *joueur_ptr;
    SDL_Texture *sprites[3];
    SDL_Texture *spritesMap[9];
    int xCamera = 0, yCamera = 0, dxCamera = 0, dyCamera = 0;
    int map[30][30];


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
    balleLongueJaune = charger_image("sprites/projectiles/balle/balle_longue_jaune.png", ecran, 255, 255, 255);


    //Chargement du décor (murs etc)
    spritesMap[0] = charger_image("sprites/map/sol.png", ecran, 0, 0, -1);
    spritesMap[1] = charger_image("sprites/map/mur_h.png", ecran, 255, 255, 255);
    spritesMap[2] = charger_image("sprites/map/mur_b.png", ecran, 255, 255, 255);
    spritesMap[3] = charger_image("sprites/map/mur_g.png", ecran, 255, 255, 255);
    spritesMap[4] = charger_image("sprites/map/mur_d.png", ecran, 255, 255, 255);
    spritesMap[5] = charger_image("sprites/map/mur_hg.png", ecran, 255, 255, 255);
    spritesMap[6] = charger_image("sprites/map/mur_hd.png", ecran, 255, 255, 255);
    spritesMap[7] = charger_image("sprites/map/mur_bg.png", ecran, 255, 255, 255);
    spritesMap[8] = charger_image("sprites/map/mur_bd.png", ecran, 255, 255, 255);

    fond = charger_image("sprites/fond.png", ecran, -1, -1, -1);
    perso = charger_image("sprites/perso/handgun/idle/survivor_idle.png", ecran, 255, 255, 255);
    sprites[0] = perso;
    perso = charger_image("sprites/ennemis/zombie/move/zombie_moveV2.png", ecran, 0, 0, -1);
    sprites[1] = perso;
    perso = charger_image("sprites/effets/blood/blood_hitv3.png", ecran, 0, 0, -1);
    sprites[2] = perso;


    SDL_Rect tmpRect;
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = 0;
    tmpRect.h = 0;
    mursListe = nouvelle_listeR(tmpRect);
    charger_niveau(map[0], &mursListe);


    Perso p = nouveau_joueur(ecran , sprites);
    persosListe = nouvelle_listeP(p);
    p = nouvel_ennemi_1(ecran, sprites);
    cons_listeP(&persosListe, p);
    p = nouvel_ennemi_1(ecran, sprites);
    cons_listeP(&persosListe, p);
    p = nouvel_ennemi_1(ecran, sprites);
    cons_listeP(&persosListe, p);
    p = nouvel_ennemi_1(ecran, sprites);
    cons_listeP(&persosListe, p);
    p = nouvel_ennemi_1(ecran, sprites);
    cons_listeP(&persosListe, p);
    p = nouvel_ennemi_1(ecran, sprites);
    cons_listeP(&persosListe, p);


    balle b = nouvelle_balle(balleLongueJaune, 0, 0, persoPos);
    ballesTirees = nouvelle_listeB(b);

    effetsListe = NULL;

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
        if(joueur_ptr != NULL){
          //Gestion déplacement/angle de tir
          joueur_ptr->tir = tir;
          deplacement_joueur(joueur_ptr, mursListe, &xCamera, &yCamera, &dxCamera, &dyCamera);
          angle_joueur((joueur_ptr), mouseX, mouseY);
        }


        tempsActuelAnim = SDL_GetTicks();
        if(tempsActuelAnim > tempsPrecedentAnim + 40 ){
          animer_persos(persosListe);
          animer_effets(effetsListe);
          tempsPrecedentAnim = tempsActuelAnim;
        }





        //Déplacement/angle de tir ennemis
        deplacement_ennemis(persosListe, xCamera, yCamera, dxCamera, dyCamera);

        //Tir
        tempsActuelTir = SDL_GetTicks();
        ballesTirees = tir_update(ballesTirees, persosListe, mursListe, &effetsListe, tempsActuelTir, balleLongueJaune, vitesse, xCamera, yCamera, sprites);

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

    //Nettoyage
    SDL_DestroyWindow(fenetre);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(perso);
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
