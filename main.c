#include "image.h"
#include "listeB.h"
#include "SDL2/SDL_ttf.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool gameover, tir, exit, switchArme, vagueTerminee;
    SDL_Window *fenetre;
    SDL_Event evenements;
    SDL_Renderer *ecran;
    SDL_Texture *sprites[12], *spritesMap[20];
    float mouseX, mouseY;
    int vitesse, vagueNum, nbTues = 0, arme, tempsActuel, tempsPrecedent, tempsActuelTir, tempsActuelVague, tempsPrecedentVague,
        tempsActuelAnim, tempsPrecedentAnim, xCamera, yCamera, dxCamera, dyCamera, vaguesEnnemis[100];
    char map[62][60];
    ListeB ballesTirees;
    ListeP persosListe;
    ListeR mursListe;
    ListeE effetsListe;
    Perso p, *joueur_ptr;
    Mix_Music *musique;
    Mix_Chunk *sons[3];


    //Initialisation SDL
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
      printf("Erreur d'initialisation de la SDL %s", SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }


    if(Mix_OpenAudio(44100, AUDIO_S16, 1, 4096) < 0)
    {
      printf("Erreur d'initialisation de la SDL %s", Mix_GetError() );
      SDL_Quit();
      return EXIT_FAILURE;
    }

    if(TTF_Init() == -1)
    {
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    return (EXIT_FAILURE);
    }

    //Création fenêtre
    fenetre = SDL_CreateWindow("gameName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL)
    {
      printf("Erreur d'initialisation de la fenetre %s", SDL_GetError());
      return EXIT_FAILURE;
    }

    //Création renderer
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    //Initialisation texte
    SDL_Color couleur = {255, 20, 20};
    SDL_Rect postext;
    postext.x = 810;
    postext.y = 0;
    postext.w = 180;
    postext.h = 50;
    SDL_Rect postext2;
    postext2.x = 0;
    postext2.y = 0;
    postext2.w = 150;
    postext2.h = 50;
    SDL_Rect postext3;
    postext3.x = 370;
    postext3.y = 350;
    postext3.w = 300;
    postext3.h = 100;
    TTF_Font *police =  NULL;
    police = TTF_OpenFont("RAVIE.ttf", 100);
    if(police == NULL)
        return false;

    SDL_Surface *pSurf;
    SDL_Texture *text;
    SDL_Surface *pSurf2;
    SDL_Texture *text2;




    //Chargement images
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
    spritesMap[9] = charger_image("sprites/map/route_ver.png", ecran, 0, 0, -1);
    spritesMap[10] = charger_image("sprites/map/route_hor.png", ecran, 0, 0, -1);
    spritesMap[11] = charger_image("sprites/map/police_car.png", ecran, 0, 0, -1);
    spritesMap[12] = charger_image("sprites/map/ambulance.png", ecran, 0, 0, -1);
    spritesMap[13] = charger_image("sprites/map/eau.png", ecran, 0, 0, -1);
    spritesMap[14] = charger_image("sprites/map/conteneurs.png", ecran, 0, 0, -1);
    spritesMap[15] = charger_image("sprites/map/maison2.png", ecran, 0, 0, -1);
    spritesMap[16] = charger_image("sprites/map/maison.png", ecran, 0, 0, -1);
    spritesMap[17] = charger_image("sprites/map/herbe.png", ecran, 0, 0, -1);
    spritesMap[18] = charger_image("sprites/map/maison3.png", ecran, 0, 0, -1);
    spritesMap[19] = charger_image("sprites/map/fontaine.png", ecran, 0, 0, -1);

    //Personnages + Effets
    sprites[0] = charger_image("sprites/perso/survivor_handgun.png", ecran, 255, 255, 255);
    sprites[1] = charger_image("sprites/ennemis/zombie/move/zombie_moveV2.png", ecran, 0, 0, -1);
    sprites[2] = charger_image("sprites/ennemis/zombie/attack/zombie_attack.png", ecran, 0, 0, -1);
    sprites[3] = charger_image("sprites/effets/blood/blood_hitv3.png", ecran, 0, 0, -1);
    sprites[4] = charger_image("sprites/effets/blood/blood_splatter.png", ecran, 255, 255, 255);
    sprites[5] = charger_image("sprites/perso/survivor_shotgun.png", ecran, 255, 255, 255);
    sprites[6] = charger_image("sprites/perso/survivor_rifle.png", ecran, 255, 255, 255);
    sprites[7] = charger_image("sprites/projectiles/balle/balle_handgun.png", ecran, 255, 255, 255);
    sprites[8] = charger_image("sprites/projectiles/balle/balle_shotgun.png", ecran, 255, 255, 255);
    sprites[9] = charger_image("sprites/projectiles/balle/balle_rifle.png", ecran, 255, 255, 255);
    sprites[10] = charger_image("sprites/perso/survivor_shotgun.png", ecran, 255, 255, 255);
    sprites[11] = charger_image("sprites/perso/survivor_rifle.png", ecran, 255, 255, 255);

    //Sons
    musique = NULL;

    charger_sons(&musique, &sons[0]);

    exit = false;

    while(!exit){

      gameover = false;
      tir = false;
      switchArme = false;
      vagueTerminee = false;

      vitesse = 25;
      vagueNum = 0;
      nbTues = 0;
      arme = 0;
      tempsActuel = 0;
      tempsPrecedent = 0;
      tempsActuelTir = 0;
      tempsActuelVague = 0;
      tempsPrecedentVague = 0;
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

      charger_vagues_ennemis(vaguesEnnemis);


      //Boucle de jeu
      while(!gameover)
      {
        tempsActuel = SDL_GetTicks();
        if (tempsActuel > tempsPrecedent + 16) {
          //Détection événements
          while(SDL_PollEvent(&evenements))
          {
            switch(evenements.type)
            {
              case SDL_QUIT:
                gameover = true;
                exit = true;
                break;
              case SDL_MOUSEWHEEL:
                if(evenements.wheel.y > 0){
                  arme++;
                  if(arme > 2){
                    arme = 0;
                  }
                } else if(evenements.wheel.y < 0){
                  arme--;
                  if(arme < 0){
                    arme = 2;
                  }
                }
                switchArme = true;
                break;
              case SDL_MOUSEMOTION:
                mouseX = evenements.motion.x;
                mouseY = evenements.motion.y;
                break;
              case SDL_MOUSEBUTTONDOWN:
                switch(evenements.button.button){
                  case SDL_BUTTON_LEFT:
                    tir = true;
                    break;
                }
                break;
              case SDL_MOUSEBUTTONUP:
                switch(evenements.button.button){
                  case SDL_BUTTON_LEFT:
                    tir = false;
                    break;
                }
                break;
              case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym){
                  case SDLK_ESCAPE:
                    gameover = true;
                    exit = true;
                    break;
                }
                break;
              default:
                break;
            }
          }

          if(Mix_PlayingMusic() == 0) {
            Mix_VolumeMusic(20);
            Mix_FadeInMusic(musique, 1, 1000);
          }


          tempsActuelVague = SDL_GetTicks();
          if(!vagueTerminee){
            if(tempsActuelVague > tempsPrecedentVague + 250){
              charger_vague_ennemis(ecran, &vagueTerminee, vaguesEnnemis, vagueNum, xCamera, yCamera, &persosListe, mursListe, sprites);
              tempsPrecedentVague = tempsActuelVague;
            }
          } else {
              if(vague_terminee(persosListe)){
                if(tempsActuelVague > tempsPrecedentVague + 2000){
                  vagueNum ++;
                  tempsPrecedentVague = tempsActuelVague;
                  vagueTerminee = false;
                }
              } else {
                tempsPrecedentVague = tempsActuelVague;
              }
            }



          joueur_ptr = joueur(persosListe);
          if(joueur_ptr != NULL){
            if(switchArme){
              joueur_ptr->arme = arme;
              changer_arme_joueur(joueur_ptr, arme, sprites);
              switchArme = false;
            }
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
            SDL_Surface *pSurf3 = TTF_RenderText_Blended(police, "GameOver", couleur);
            SDL_Texture *text3 = SDL_CreateTextureFromSurface(ecran, pSurf3);
            SDL_RenderCopy(ecran, text3, NULL, &postext3);
            gameover = true;
          }
          else{
            char sc[10];
            char score[] = "Score : ";
            char pv[10];
            char vie[] = "Vie : ";
            sprintf(sc, "%d", nbTues);
            strcat(score, sc);
            sprintf(pv, "%d", joueur_ptr->vie);
            strcat(vie, pv);
            pSurf = TTF_RenderText_Blended(police, score, couleur); ////
            text = SDL_CreateTextureFromSurface(ecran, pSurf);
            pSurf2 = TTF_RenderText_Blended(police, vie, couleur);
            text2 = SDL_CreateTextureFromSurface(ecran, pSurf2);

          }

          //Déplacement/angle de tir ennemis
          deplacement_ennemis(persosListe, mursListe, &effetsListe, sprites, xCamera, yCamera, dxCamera, dyCamera);

          //Tir
          tempsActuelTir = SDL_GetTicks();
          ballesTirees = tir_update(ballesTirees, persosListe, mursListe, &effetsListe, tempsActuelTir, vitesse, xCamera, yCamera, &nbTues, sprites, &sons[0]);



          //Affichage
          SDL_RenderClear(ecran);
          afficher_niveau(map[0], ecran, spritesMap, xCamera, yCamera);
          afficher_listeE(ecran, effetsListe, dxCamera, dyCamera);
          afficher_listeP(ecran, persosListe);
          afficher_listeB(ecran, ballesTirees);
          SDL_RenderCopy(ecran, text, NULL, &postext);
          SDL_RenderCopy(ecran, text2, NULL, &postext2);
          SDL_RenderPresent(ecran);

          tempsPrecedent = tempsActuel;
        }
      }

      if(gameover)
      printf("gameover :(\n");

    }

    //Nettoyage
    SDL_DestroyWindow(fenetre);
    SDL_DestroyRenderer(ecran);
    Mix_FreeMusic(musique);
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
}
