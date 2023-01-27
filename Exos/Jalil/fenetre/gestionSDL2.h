#include <SDL2/SDL.h>
#ifndef __GESTIONSDL2__
#define __GESTIONSDL2__


SDL_Window** Cosima_Circle(int centre_x, int centre_y, int n, int rayon);
void LiberationTabWindow(SDL_Window **tab, int n);
void rotation(SDL_Window **tab,  int n, int centre_x, int centre_y, int R, int delay);
void Circle_Extension(SDL_Window **tab,  int n, int centre_x,
                        int centre_y, int R_debut, int R_fin, int delay);

#endif