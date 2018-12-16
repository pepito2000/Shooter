#include "image.h"
#include "listeB.h"
#include "SDL2/SDL_ttf.h"
#include <string.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool gameover, tir, exit, switchArme, vagueTerminee;
    SDL_Window *fenetre;
    SDL_Event evenements;
    SDL_Renderer *ecran;
    SDL_Texture *sprites[15], *spritesMap[20], *text, *text2, *text3, *textGameover;
    SDL_Rect postext1, postext2, postext3, posGameover;
    SDL_Surface *pSurf;
    float mouseX, mouseY;
    int vitesse, vagueNum, nbTues, arme, tempsPrecedent, tempsPrecedentTexte, tempsActuelTir, tempsActuelVague, tempsPrecedentVague,
        tempsActuelAnim, tempsPrecedentAnim, xCamera, yCamera, dxCamera, dyCamera, vaguesEnnemis[100];
    char map[62][60];
    ListeB ballesTirees;
    ListeP persosListe;
    ListeR mursListe;
    ListeE effetsListe;
    Perso p, *joueur_ptr;
    Mix_Music *musique;
    Mix_Chunk *sons[3];
    TTF_Font *police;

    FILE* fichier = NULL;
    fichier = fopen("tab_des_scores.txt", "r+");




    if(SDL_Init(SDL_INIT_EVERYTHING)){
      printf("Erreur d'initialisation de la SDL %s", SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }

    if(Mix_OpenAudio(44100, AUDIO_S16, 1, 4096) < 0){
      printf("Erreur d'initialisation de la SDL %s", Mix_GetError() );
      SDL_Quit();
      return EXIT_FAILURE;
    }

    if(TTF_Init() == -1){
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    return (EXIT_FAILURE);
    }

    fenetre = SDL_CreateWindow("Shooter Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL){
      printf("Erreur d'initialisation de la fenetre %s", SDL_GetError());
      return EXIT_FAILURE;
    }

    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    charger_images(&sprites[0], &spritesMap[0], ecran);

    musique = NULL;
    charger_sons(&musique, &sons[0]);

    SDL_Color couleur = {255, 20, 20, 0};

    postext1.x = 10;
    postext1.y = 0;
    postext1.w = 150;
    postext1.h = 50;

    postext2.x = 810;
    postext2.y = 0;
    postext2.w = 180;
    postext2.h = 50;

    postext3.x = 810;
    postext3.y = 50;
    postext3.w = 180;
    postext3.h = 50;

    posGameover.x = 200;
    posGameover.y = 200;
    posGameover.w = 600;
    posGameover.h = 200;

    police = NULL;
    police = TTF_OpenFont("police.otf", 100);


    pSurf = TTF_RenderText_Blended(police, "GAMEOVER", couleur);
    textGameover = SDL_CreateTextureFromSurface(ecran, pSurf);
    SDL_FreeSurface(pSurf);


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
      tempsPrecedent = 0;
      tempsActuelTir = 0;
      tempsPrecedentTexte = 0;
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
      pSurf = NULL;
      text = NULL;
      text2 = NULL;
      text3 = NULL;

      charger_niveau(map[0], &mursListe);

      p = nouveau_joueur(ecran, sprites);
      cons_listeP(&persosListe, p);

      charger_vagues_ennemis(vaguesEnnemis);


      while(!gameover)
      {
        if (SDL_GetTicks() > tempsPrecedent + 16) {
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
            Mix_VolumeMusic(30);
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
          if(tempsActuelAnim > tempsPrecedentAnim + 40){
            animer_balles(ballesTirees);
            animer_persos(persosListe, ballesTirees, sprites, joueur_ptr);
            animer_effets(effetsListe);
            tempsPrecedentAnim = tempsActuelAnim;
          }

          if(joueur_ptr->vie <= 0){

            int caractereActuel;
            while (caractereActuel != EOF){
                caractereActuel = fgetc(fichier);
            }
            char score[13];
            sprintf(score, "Score : %d \n", nbTues);
            fputs(score, fichier);
            gameover = true;
          }

          if(SDL_GetTicks() > tempsPrecedentTexte + 500){
            char sc[13];
            char pv[13];
            char ma[13];
            sc[0] = '\0';
            pv[0] = '\0';
            ma[0] = '\0';
            sprintf(sc, "Score : %d", nbTues);
            sprintf(pv, "Vie : %d", joueur_ptr->vie);
            sprintf(ma, "Manche : %d", vagueNum + 1);
            pSurf = TTF_RenderText_Blended(police, sc, couleur);
            text = SDL_CreateTextureFromSurface(ecran, pSurf);
            SDL_FreeSurface(pSurf);
            pSurf = TTF_RenderText_Blended(police, pv, couleur);
            text2 = SDL_CreateTextureFromSurface(ecran, pSurf);
            SDL_FreeSurface(pSurf);
            pSurf = TTF_RenderText_Blended(police, ma, couleur);
            text3 = SDL_CreateTextureFromSurface(ecran, pSurf);
            SDL_FreeSurface(pSurf);
            tempsPrecedentTexte = SDL_GetTicks();
          }

          deplacement_ennemis(persosListe, mursListe, &effetsListe, sprites, xCamera, yCamera, dxCamera, dyCamera);

          tempsActuelTir = SDL_GetTicks();
          ballesTirees = tir_update(ballesTirees, persosListe, mursListe, &effetsListe, tempsActuelTir, vitesse, xCamera, yCamera, dxCamera, dyCamera, &nbTues, sprites, &sons[0], joueur_ptr);


          SDL_RenderClear(ecran);
          afficher_niveau(map[0], ecran, spritesMap, xCamera, yCamera);
          afficher_listeE(ecran, effetsListe, dxCamera, dyCamera);
          afficher_listeP(ecran, persosListe);
          afficher_listeB(ecran, ballesTirees);
          SDL_RenderCopy(ecran, text, NULL, &postext2);
          SDL_RenderCopy(ecran, text2, NULL, &postext1);
          SDL_RenderCopy(ecran, text3, NULL, &postext3);
          SDL_RenderPresent(ecran);

          tempsPrecedent = SDL_GetTicks();
        }
      }

      Mix_HaltMusic();
      if(!exit){
        int gameoverTimer = SDL_GetTicks();
        if(gameover){
          while(SDL_GetTicks() < gameoverTimer + 3000){
            SDL_RenderCopy(ecran, textGameover, NULL, &posGameover);
            SDL_RenderPresent(ecran);
          }
        }
      }
    }

    fclose(fichier);
    SDL_DestroyWindow(fenetre);
    SDL_DestroyRenderer(ecran);
    Mix_FreeMusic(musique);
    Mix_FreeChunk(sons[0]);
    Mix_FreeChunk(sons[1]);
    Mix_FreeChunk(sons[2]);
    Mix_CloseAudio();
    free(joueur_ptr);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
