#include <stdio.h>
#include "affichage_laby.h"
#include "modelisation_temps.h"
#include "labyrinthe.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


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



int achat_MP(int *thune, int *compteur)
{
    //Si ne peut plus irne acheter retourne 0 sinon 1
    int prix,r=0;

    while((*thune)>4)
    {
        r=1;
        switch(rand()%3)
        {
            case 0:
                (*thune)-= 1;
                compteur[0]++;
                break;
            
            case 1:
                (*thune)-= 2;
                compteur[1]++;
                break;
            
            case 2: 
                (*thune)-= 3;
                compteur[2]++;
                break;
            
            default:
                break;

        }

    }

    return r;
}