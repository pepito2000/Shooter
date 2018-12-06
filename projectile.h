#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265359

typedef struct s_Balle balle, s_Balle;
struct s_Balle
{
    SDL_Rect ballePos;
    float angle;
    SDL_Texture *image;
    bool collision;
    int degats;
};

balle nouvelle_balle(SDL_Texture *image, float angle, int degats, SDL_Rect persoPos);
void incrementer_balle(balle *b, int vitesse);
void afficher_balle(SDL_Renderer *renderer, balle b);

