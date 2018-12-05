#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_ListeR *ListeR, s_ListeR;
struct s_ListeR
{
  ListeR next;
  SDL_Rect data;
};

ListeR nouvelle_listeR(SDL_Rect data);
ListeR cons_listeR(ListeR L, SDL_Rect data);
ListeR charger_niveau(int *tab, ListeR L);
bool detecter_collision_murs(ListeR L, SDL_Rect rect, int xCamera, int yCamera);
