#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* charger_image(const char* fichier, SDL_Renderer* renderer, int r, int g, int b);
void afficher_niveau(char *tab, SDL_Renderer *renderer, SDL_Texture **spriteMap, int xCamera, int yCamera);
