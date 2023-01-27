#include <stdio.h>
#include "gestion_SDL.h"


//Structure qui permet de gerer une animation en particulier
//Le tableau nous donne la suite d'image à afficher



int main()
{

    //Initialisation de la SDL
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
            screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de la vie",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 
                                0.66*screen.w,
                                0.66*screen.h,
                                SDL_WINDOW_OPENGL);

    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    
    //Chargement d'une texture
    SDL_Texture* texture = load_texture_from_image("./img/index.jpeg", window, renderer );
    //Affichage d'une image
    // play_with_texture_1(texture, window, renderer);

    // //zoom fenetre
    // play_with_texture_2(texture, window, renderer);

    // //Gestion suite d'image
    // play_with_texture_3(texture, window, renderer);

    // //Gestion suite d'image
    // play_with_texture_4(texture, window, renderer);
    
    SDL_DestroyTexture(texture);

    // Test avec structure anim
    char *knight_attack = "./img/Colour1/Outline/120x80_PNGSheets/_AttackNoMovement.png";
    int suite_attack[] = {0, 1, 2, 3, 2, 1, 0};
    animation anim = CreerAnimation(window, renderer, knight_attack, suite_attack, 7, 4);

    // play(window, renderer, anim);

    //test sans la struct animation
    // texture = load_texture_from_image(knight_attack, window, renderer );
    // play_with_texture_4(texture, window, renderer); 

    SDL_Texture *bg_texture = load_texture_from_image("./img/castlebackground.jpeg", window, renderer);
    play_with_texture_5(bg_texture, anim, window, renderer);


    // //Fermeture du programme
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(bg_texture);
    LibererAnimation(&anim);
    end_sdl(1, "fermeture ok", window, renderer);

    return 0;
}