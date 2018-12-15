#include "image.h"


SDL_Texture* charger_image(const char* cheminFichier, SDL_Renderer* renderer, int r, int g, int b){

  SDL_Surface* surface = IMG_Load(cheminFichier);
  if(r >= 0 && g >= 0 && b >= 0){
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b ));
  }
  SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return image;
}


void afficher_niveau(char *tab, SDL_Renderer *renderer, SDL_Texture **spriteMap, int xCamera, int yCamera){
  SDL_Rect destrect;
  int tabVal;

  for(int j = 0; j < 60; j++){
    for(int i = 0; i < 60; i++){
      destrect.x = i * 50 - xCamera;
      destrect.y = j * 50 - yCamera;
      destrect.h = 50;
      destrect.w = 50;
      tabVal = tab[60*j+i];
      if(tabVal != '.' && tabVal != 'A' && tabVal != 'P'){
        SDL_RenderCopy(renderer, spriteMap[0], NULL, &destrect);
      }
      switch(tabVal){
      case '0':
        SDL_RenderCopy(renderer, spriteMap[0], NULL, &destrect);
        break;
      case '1':
        SDL_RenderCopy(renderer, spriteMap[1], NULL, &destrect);
        break;
      case '2':
        SDL_RenderCopy(renderer, spriteMap[2], NULL, &destrect);
        break;
      case '3':
        SDL_RenderCopy(renderer, spriteMap[3], NULL, &destrect);
        break;
      case '4':
        SDL_RenderCopy(renderer, spriteMap[4], NULL, &destrect);
        break;
      case '5':
        SDL_RenderCopy(renderer, spriteMap[5], NULL, &destrect);
        break;
      case '6':
        SDL_RenderCopy(renderer, spriteMap[6], NULL, &destrect);
        break;
      case '7':
        SDL_RenderCopy(renderer, spriteMap[7], NULL, &destrect);
        break;
      case '8':
        SDL_RenderCopy(renderer, spriteMap[8], NULL, &destrect);
        break;
      case 'R':
        destrect.w = 200;
        destrect.h = 200;
        SDL_RenderCopy(renderer, spriteMap[10], NULL, &destrect);
        break;
      case 'S':
        destrect.w = 200;
        destrect.h = 200;
        SDL_RenderCopy(renderer, spriteMap[9], NULL, &destrect);
        break;
      case 'E':
        SDL_RenderCopy(renderer, spriteMap[13], NULL, &destrect);
        break;
      case 'H':
        SDL_RenderCopy(renderer, spriteMap[17], NULL, &destrect);
        break;
      case 'M':
        destrect.w = 550;
        destrect.h = 400;
        SDL_RenderCopy(renderer, spriteMap[15], NULL, &destrect);
        break;
      case 'N':
        destrect.w = 500;
        destrect.h = 600;
        SDL_RenderCopy(renderer, spriteMap[16], NULL, &destrect);
        break;
      case 'L':
        destrect.w = 800;
        destrect.h = 600;
        SDL_RenderCopy(renderer, spriteMap[18], NULL, &destrect);
        break;

      default:
        break;
      }
    }
  }

  for(int j = 0; j < 60; j++){
    for(int i = 0; i < 60; i++){
      destrect.x = i * 50 - xCamera;
      destrect.y = j * 50 - yCamera;
      destrect.h = 50;
      destrect.w = 50;
      switch(tab[60*j+i]){
      case 'P':
        destrect.w = 200;
        destrect.h = 100;
        SDL_RenderCopy(renderer, spriteMap[11], NULL, &destrect);
        break;
      case 'A':
        destrect.w = 100;
        destrect.h = 200;
        SDL_RenderCopy(renderer, spriteMap[12], NULL, &destrect);
        break;
      case 'C' :
        destrect.w = 150;
        destrect.h = 250;
        SDL_RenderCopy(renderer, spriteMap[14], NULL, &destrect);
        break;
      case 'F':
        destrect.w = 300;
        destrect.h = 300;
        SDL_RenderCopy(renderer, spriteMap[19], NULL, &destrect);
        break;
      default :
        break;
      }
    }
  }
  return;
}

void charger_images(SDL_Texture **sprites, SDL_Texture **spritesMap, SDL_Renderer *ecran){
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

  sprites[0] = charger_image("sprites/perso/survivor_handgun.png", ecran, 255, 255, 255);
  sprites[1] = charger_image("sprites/ennemis/zombie/move/ennemi1_move.png", ecran, 0, 0, -1);
  sprites[2] = charger_image("sprites/ennemis/zombie/attack/ennemi1_attack.png", ecran, 0, 0, -1);
  sprites[3] = charger_image("sprites/effets/blood/blood_hitv3.png", ecran, 0, 0, -1);
  sprites[4] = charger_image("sprites/effets/blood/blood_splatter.png", ecran, 255, 255, 255);
  sprites[5] = charger_image("sprites/perso/survivor_shotgun.png", ecran, 255, 255, 255);
  sprites[6] = charger_image("sprites/perso/survivor_rifle.png", ecran, 255, 255, 255);
  sprites[7] = charger_image("sprites/projectiles/balle/balle_handgun.png", ecran, 255, 255, 255);
  sprites[8] = charger_image("sprites/projectiles/balle/balle_shotgun.png", ecran, 255, 255, 255);
  sprites[9] = charger_image("sprites/projectiles/balle/balle_rifle.png", ecran, 255, 255, 255);
  sprites[10] = charger_image("sprites/perso/survivor_shotgun.png", ecran, 255, 255, 255);
  sprites[11] = charger_image("sprites/perso/survivor_rifle.png", ecran, 255, 255, 255);
  sprites[12] = charger_image("sprites/ennemis/zombie/move/ennemi2_move.png", ecran, 0, 0, -1);
  sprites[13] = charger_image("sprites/ennemis/zombie/attack/ennemi2_attack.png", ecran, 0, 0, -1);
  sprites[14] = charger_image("sprites/projectiles/slime.png", ecran, 0, 0, -1);
}
