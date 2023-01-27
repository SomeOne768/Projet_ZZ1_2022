#ifndef __GESTION_SDL_H__
#define __GESTION_SDL_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef struct {
    int *suite;
    int taille;
    SDL_Texture *texture;
    int nb_img;
} animation;

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer) ;
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );
void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_with_texture_2(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer);
void play_with_texture_3(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer);
void play_with_texture_4(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer);
void play_with_texture_5(SDL_Texture *bg_texture, animation anim, SDL_Window *window, SDL_Renderer *renderer);
animation CreerAnimation(SDL_Window *window, SDL_Renderer *renderer, char *filename , int tab[], int taille, int nb_img);
void LibererAnimation(animation *anim);
void play(SDL_Window *window, SDL_Renderer *renderer, animation anim);

#endif