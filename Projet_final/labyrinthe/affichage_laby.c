#include <stdio.h>
#include "affichage_laby.h"
#include "labyrinthe.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;   // Variable de passage
    SDL_Texture *my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                          // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                          // uniquement possible si l'image est au format bmp */
    // if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    // if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

// Afficher une matrice
void afficherLaby(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *road, SDL_Texture *wall, SDL_Texture *goal, SDL_Texture *perso, char **M, int n, int m)
{
    // On commence par definir les dimensions des elements

    SDL_Rect
        source_road = {0}, // Rectangle définissant la zone totale de la planche
        source_wall = {0},
        source_goal = {0},
        source_perso = {0},
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        pos = {0};               // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);

    SDL_QueryTexture(road, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source_road.w, &source_road.h);

    SDL_QueryTexture(wall, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source_wall.w, &source_wall.h);

    SDL_QueryTexture(goal, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source_goal.w, &source_goal.h);
    SDL_QueryTexture(perso, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source_perso.w, &source_perso.h);

    float dx = window_dimensions.w / m,
          dy = window_dimensions.h / n;

    // //J espere tout est carr
    // float   coeffR = source_road.w/dx,
    //         coeffW = source_wall.w/dx,
    //         coeffG = source_goal.w/dx,
    //         coeffP = source_perso.w/dx;

    pos.w = dx; /// 2;
    pos.h = dy; /// 2;

    SDL_Texture *texture = NULL;
    for (int i = 0; i < n; i++)
    {
        pos.y = i * dy;
        for (int j = 0; j < m; j++)
        {

            pos.x = j * dx;
            switch (M[i][j])
            {
            case '#':
                // wall
                texture = wall;
                // pos.w = source_wall.w / coeffW;
                // pos.h = source_wall.h / coeffW;
                break;

            case '-':
                texture = road;
                // pos.w = source_wall.w / coeffR;
                // pos.h = source_wall.h / coeffR;
                break;

            case '2':
                texture = goal;
                // pos.w = source_wall.w / coeffG;
                // pos.h = source_wall.h / coeffG;
                break;

            case '1':
                // le perso => on l'affiche au dessus de la route
                SDL_RenderCopy(renderer, road, // Préparation de l'affichage
                               NULL,
                               &pos);
                texture = perso;
                // pos.w = source_wall.w / coeffP;
                // pos.h = source_wall.h / coeffP;
                break;

            default:
                break;
            }

            SDL_RenderCopy(renderer, texture, // Préparation de l'affichage
                           NULL,
                           &pos);
        }
    }
}

int faire_les_courses(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *road, SDL_Texture *wall, SDL_Texture *goal, SDL_Texture *perso, char **M, int n, int m, double **Q, int *fini)
{
    int program_on = 1;


    SDL_Event event;
    int etat, action;
    int x, y;
    position(M, n, m, &x, &y);
    while (program_on && !(*fini))
    {

        etat = h_laby(x, y, m);

        action = meilleur_action_laby(Q, etat);

        // On calcul la récompense en fonction de notre action
        (*fini) = mouvement(M, n, m, &x, &y, action);
        while (program_on && !fini && SDL_PollEvent(&event))
        {
            switch (event.type)
            {                   // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:      // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = 0; // Il est temps d'arrêter le programme
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:

                    program_on = 0;
                    break;
                case SDLK_RETURN:
                    (*fini) = 1;
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
            
        }

        affiche_labyrinthe(M, n, m);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        affiche_labyrinthe(M, n, m);
        afficherLaby(window, renderer, road, wall, goal, perso, M, n, m);
        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }
    return program_on;
}