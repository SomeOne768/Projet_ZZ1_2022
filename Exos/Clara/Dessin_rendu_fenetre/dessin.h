#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#ifndef __DESSIN_H__
#define __DESSIN_H__

void end_sdl(char,                                               
             char const* ,                                       
             SDL_Window* ,                                  
             
             SDL_Renderer*);
            
void draw(SDL_Renderer*, int, int);

#endif