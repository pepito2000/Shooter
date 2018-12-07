#include "son.h"

void charger_sons(Mix_Music **musique, Mix_Chunk **sons){

    *musique = Mix_LoadMUS("son/musique.mp3");
    sons[0] = Mix_LoadWAV("son/pistolet.mp3");
    Mix_VolumeChunk(sons[0], 50);
    return;
}
