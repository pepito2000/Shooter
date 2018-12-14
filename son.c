#include "son.h"

void charger_sons(Mix_Music **musique, Mix_Chunk **sons){

    *musique = Mix_LoadMUS("son/musique.mp3");
    sons[0] = Mix_LoadWAV("son/handgun.mp3");
    sons[1] = Mix_LoadWAV("son/shotgun.mp3");
    sons[2] = Mix_LoadWAV("son/rifle.mp3");
    Mix_VolumeChunk(sons[0], 40);
    Mix_VolumeChunk(sons[1], 20);
    Mix_VolumeChunk(sons[2], 40);
    return;
}

