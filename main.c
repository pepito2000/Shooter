#include <SDL.h>

  

int main (int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *ecran = NULL;
    SDL_Surface *image = NULL;

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    
    SDL_Rect anim;
    anim.h = 125;
    anim.w = 95;

    int colorkey;
    int gameover = 0;
    int dirX = 0;
    int dirY = 0;

    SDL_WM_SetCaption("Test", NULL);
    ecran = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    image = SDL_LoadBMP("sprites.bmp");
    colorkey = SDL_MapRGB(ecran->format, 0, 255, 255);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    if(image  == NULL)
     return EXIT_FAILURE;

    SDL_Event event;
   

    while(gameover == 0){

      
      SDL_PollEvent(&event);

      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym){
	case SDLK_ESCAPE:
	  gameover = 1;
	  break;
	case SDLK_LEFT:
	  dirX = -1;
	  break;
	case SDLK_RIGHT:
	  dirX = 1;
	  break;
	case SDLK_UP:
	  dirY = -1;
	  break;
	case SDLK_DOWN:
	  dirY = 1;
	  break;
	}
  
      }

      position.x += dirX;
      position.y += dirY;
      dirX = 0;
      dirY = 0;
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      SDL_BlitSurface(image, &anim, ecran, &position);
      SDL_Flip(ecran);
    }

   


  SDL_FreeSurface(image);
  SDL_Quit();

  return 0;
}
