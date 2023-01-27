#ifndef __APPARITION_H__
#define __APPARITION_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

void nouveauxclients(int * presenceclient);

int quellecommandesurcetemplacement(int * compteurs);

void quellecommandesurquelemplacement(int * presence, int * quisuremplacement, int * compteurs);


void service(int quiestservi,  int *profitvente, int *tempspreparation, int * compteursvente, int *tempsattente, int periode); //quiestservi= quisuremplacement[i] int *compteurN, int *compteurT, int *compteurB,











#endif
