#ifndef _ANIMATION_H_
#define _ANIMATION_H_

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer );
void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void play_with_texture_4(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer);
void play_with_texture_5(SDL_Texture *bg_texture, SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void appliquer_image(SDL_Texture *texture, SDL_Window *window, SDL_Renderer *renderer, int nb_images, int x, int y, float zoom, int num_image);
void appliquer_background(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);

#endif