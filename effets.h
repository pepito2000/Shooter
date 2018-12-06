#include <SDL2/SDL.h>


typedef struct s_Effet Effet, s_Effet;
struct s_Effet
{
    SDL_Rect pos;
    SDL_Rect srcrect;
    SDL_Texture *image;
    float angle;
    int xMax;
};

Effet nouvel_effet_bloodHit(SDL_Texture **sprites, SDL_Rect pos, int angle);
void afficher_effet(SDL_Renderer *renderer, Effet e);

