#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct s_Balle balle, s_Balle;
struct s_Balle
{
    SDL_Rect ballePos;
    float angle;
    SDL_Texture *image;
    bool collision;
};

balle nouvelle_balle(SDL_Texture *image, float angle, SDL_Rect persoPos);
void incrementer_balle(balle *b, int vitesse);
void afficher_balle(SDL_Renderer *renderer, balle b);

