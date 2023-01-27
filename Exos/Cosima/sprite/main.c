#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "texture.h"
#include <SDL2/SDL_ttf.h>


int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;
    
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",screen.w, screen.h);
    
    int width = screen.w;
    int height = screen.h;

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (window == NULL) 
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);




    


    SDL_Texture* texture = load_texture_from_image("Attack.png", window, renderer);
    SDL_Texture* background = load_texture_from_image("../../../Jeu_arcade/img/desert_essai.png", window, renderer);
    
    play_with_texture_5(background, texture, window,renderer);

    

    
    
    


    
    
    SDL_DestroyTexture(texture);
    IMG_Quit();                              // Si on charge une librairie SDL, il faut penser à la décharger   
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;

}