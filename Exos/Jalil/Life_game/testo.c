#include <stdio.h>
#include <SDL2/SDL.h>
#include "jeu.h"
#include <time.h>
#include "regle.h"



int main()
{

    // srand(time(NULL));
    // int taille_carre = 10;

    // SDL_Window* window = NULL;
    // SDL_Renderer* renderer = NULL;
    // SDL_DisplayMode screen;


    // SDL_GetCurrentDisplayMode(0, &screen);
    // printf("Résolution écran\n\tw : %d\n\th : %d\n",
    //         screen.w, screen.h);

    // int width = screen.w *0.8;
    // int height = screen.h *0.8;

    // width = width- (width%taille_carre);
    // height = height -  (height%taille_carre);

    // /* Création de la fenêtre */
    // window = SDL_CreateWindow("Jeu de la vie",
    //                             SDL_WINDOWPOS_CENTERED,
    //                             SDL_WINDOWPOS_CENTERED, 
    //                             width,
    //                             height,
    //                             SDL_WINDOW_OPENGL);

    // /* Création du renderer */
    // renderer = SDL_CreateRenderer(window, -1,
    //                                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    // //test affichage d'une matrice

    // int n = 50;
    // int m = 50;
    // char** M = CreerMatrice(n, m);
    // for(int i=0; i<n; i++)
    // {
    //     for(int j=0; j<m; j++)
    //     {
    //         M[i][j] = rand()%2;
    //     }
    // }


    
    // while(1)
    // {

    //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //     SDL_RenderClear(renderer);

    //      draw(renderer, M, n, m, 10);                // appel de la fonction qui crée l'image  
    //      SDL_RenderPresent(renderer);                      // affichage
    //      SDL_Delay(50);   
    
    // }

    //test du nombre de voisins
    // for(int i=0; i<2; i++)
    // {
    //     printf("\n");
    //     for(int j=0; j<2; j++)
    //     {
    //         printf("%d |", M[i][j]);
    //     }
    // }
    //  printf("\n");
    // int k = nombre_voisin(M, n, m, 0, 0);
    //  printf("%d\n", k);


    //test extraction des regles

    // char B[9], S[9];

    // extraire_regle("B13/S45", B, S);
    // printf("Affichage de B:\n");
    // for(int i=0; i<9; i++)
    // {
    //     printf("%d |", B[i]);
    // }

    // printf("\nAffichage de S:\n");
    // for(int i=0; i<9; i++)
    // {
    //     printf("%d |", S[i]);
    // }


    //Test récupération coordonnées souris

    // SDL_Event event;
    // int continuer = 1;
    // int x;
    // int y;

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderPresent(renderer);
    // while(continuer)
    // {
    //     while(continuer && SDL_PollEvent(&event))
    //     {
    //         switch(event.type)
    //         {
    //             case SDL_QUIT:
    //                 continuer = 0;
    //                 break;
    //             case SDL_MOUSEBUTTONDOWN:
    //                 x = event.motion.x;
    //                 y = event.motion.y;
    //                 continuer = 0;
    //                 break;


    //             default:
    //                 break;
    //         }
    //     }
    //     SDL_Delay(500);

    // }

    // printf("%d %d\n", x, y);


    //Test chargement d'un fichier

    //char **M2 = chargerMatrice("sauvegarde.txt");


    char **M = malloc(sizeof(char*)*2);
    M[0] = malloc(sizeof(char)*3); M[0][0] = 0; M[0][1] = 0; M[0][2] = 1; 
    M[1] = malloc(sizeof(char)*3); M[1][0] = 1; M[1][1] = 0; M[1][2] = 0;
    enregistrerMatrice(M, 2, 3, "sauvegarde.txt");

    return 0;
}