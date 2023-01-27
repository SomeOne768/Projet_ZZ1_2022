#ifndef __affichage_laby_h__
#define __affichage_laby_h__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "affichageSDL.h"

void afficherLaby(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *road, SDL_Texture *wall, SDL_Texture *goal, SDL_Texture *perso, char **M, int n, int m);
int faire_les_courses(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *road, SDL_Texture *wall, SDL_Texture *goal, SDL_Texture *perso, char **M, int n, int m, double **Q, int *fini);

int achat_MP(int *thune, int *compteur);



#endif