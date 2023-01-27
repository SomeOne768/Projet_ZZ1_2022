#ifndef __AFFICHAGESDL_H__
#define __AFFICHAGESDL_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "modelisation_temps.h"

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer );
//Fonction legerement modifié par rapport au programme précédent (ici indépendant du nombre de col/ligne du sprite)
void appliquer_image(SDL_Texture *texture, SDL_Window *window, SDL_Renderer *renderer, int nb_images_par_ligne,
                int nb_images_par_col, int num_ligne, int num_col, int x, int y, float zoom);

void appliquer_background(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
#endif