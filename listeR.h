#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_ListeR *ListeR, s_ListeR;
struct s_ListeR
{
  ListeR next;
  SDL_Rect data;
};


void cons_listeR(ListeR *L, SDL_Rect data);
void charger_niveau(int *tab, ListeR *L);
bool detecter_collision_murs(ListeR L, SDL_Rect rect, int xCamera, int yCamera);
