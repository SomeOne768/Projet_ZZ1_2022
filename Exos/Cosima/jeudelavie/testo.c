#include <stdio.h>
#include <SDL2/SDL.h>
#include "delimite.h"
#include <time.h>



int main()
{

    srand(time(NULL));
    int taille_carre = 10;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;


    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
            screen.w, screen.h);

    int width = screen.w *0.8;
    int height = screen.h *0.8;

    width = width- (width%taille_carre);
    height = height -  (height%taille_carre);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de la vie",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 
                                width,
                                height,
                                SDL_WINDOW_OPENGL);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    //test affichage d'une matrice

    int n = 50;
    int m = 50;


    char** M = CreerMatrice(n, m);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            M[i][j] = rand()%2;
        }
    }


    
    // while(1)
    // {

    //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //     SDL_RenderClear(renderer);

    //      draw(renderer, M, n, m, 10);                // appel de la fonction qui crée l'image  
    //      SDL_RenderPresent(renderer);                      // affichage
    //      SDL_Delay(50);   
    
    // }

    for(int i=0; i<2; i++)
    {
        printf("\n");
        for(int j=0; j<3; j++)
        {
            printf("%d |", M[i][j]);
        }
    }

     printf("\n");
    int k = nb_voisins_delimite(M, n, m, 0, 1);
     printf("%d\n", k);



    return 0;
}