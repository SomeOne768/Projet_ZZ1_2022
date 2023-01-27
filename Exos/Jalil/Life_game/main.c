#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "jeu.h"
#include "regle.h"
#include <time.h>
#include <SDL2/SDL_ttf.h>  

/*******************************************************************************/
/* Programme permettant d'executer le jeu de la vie.                           */
/* Possibilité de charger/enregistrer                                          */
/* Possibilité de créer au clic la grille de départ avec n                     */
/* Nom de fichier toujours charger : sauvegarde.txt                            */
/* Nom de fichier lors de la sauvegarde : sauvegarde.txt                       */
/* Format de regle attendu : "B1235/S259"                                      */
/* Format de fichier : 1ere ligne : nbligne nb colonne                         */
/* Autres lignes : Lignes de notre matrice avec un espace entre chaque colonne */
/* Pour charger il faut appuyer sur c                                          */
/* Enregistrer une partie: e                                                   */
/* Mettre/Enlever la pause: appuyer sur espace                                  */
/* Créer une matrice aléatoirement appuyer sur r                               */
/*******************************************************************************/

char *Regle = "B45/S38";

void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer) {                              // renderer à fermer
    char msg_formated[255];                                                         
    int l;                                                                          

    if (!ok) {                                                        // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);                                              
        l = strlen(msg_formated);                                                     
        strcpy(msg_formated + l, " : %s\n");                                          

        SDL_Log(msg_formated, SDL_GetError());                                        
    }                                                                               

    if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
        window= NULL;
    }

    SDL_Quit();                                                                     
    TTF_Quit();
    if (!ok) {                                                        // On quitte si cela ne va pas                
        exit(EXIT_FAILURE);                                                           
    }

}  







int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    //taille de carré desirée
    int taille_carre = 31; //10 par défaut 


    //Initialisation de la SDL

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

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
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

   
    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/


    //On commence par defenir les variables de jeu
    int n = height/taille_carre;
    int m = width/taille_carre;
    int vitesse = 200;

    char **Matrice_avant = NULL;
    char **Matrice_apres = CreerMatrice(n, m);
    char **tmp; //Permet l'echange des matrices dans le while

    //On représente B45/S38 pour le test
    //Extraction de la regle

    char B[9], S[9];
    extraire_regle(Regle, B, S);

    int continuer = 1;

    SDL_Event event;

    //Crétion de la matrice aléatoirement
    Matrice_avant = CreerMatrice(n, m);
    MatriceRandom(Matrice_avant, n, m);


    continuer = 1;
    int stable_message = 0;
    int pause = 1;

    //1er affichage
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    draw(renderer, Matrice_avant, n, m, taille_carre);                // appel de la fonction qui crée l'image  
    SDL_RenderPresent(renderer);                      // affichage
    
    //Programme de jeu
    while(continuer)
    {
        //On veut afficher le jeu tant que l'utilisateur n'appuie pas sur la croix
        while(continuer && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                

                case SDL_KEYDOWN:
                    //On se deplace si c'est les fleches
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            //On souhaite aller plus vite
                            vitesse -= 10;
                            if(vitesse<1)                           
                            {
                                vitesse = 1;
                            }
                            break;

                        case SDLK_LEFT:
                            //On souhaite ralentir
                            vitesse += 10;
                            if(vitesse>2000)
                            {
                                vitesse = 2000;
                            }
                            break;

                        case SDLK_SPACE:
                            pause = !pause;
                            break;

                        case SDLK_e:
                            //On souhaite enregistrer la matrice
                            enregistrerMatrice(Matrice_avant, n, m, "sauvegarde.txt");
                            break;
                        
                        case SDLK_c:
                            //On charge un jeu deja existant
                            //Ici on charge toujours le même fichier pour simplifier
                            tmp = chargerMatrice("sauvegarde.txt");
                            if(tmp)
                            {
                                LiberationMatrice(Matrice_avant, n);
                                Matrice_avant = tmp;
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                SDL_RenderClear(renderer);
                                draw(renderer, Matrice_avant, n, m, taille_carre);                // appel de la fonction qui crée l'image  
                                SDL_RenderPresent(renderer);                      // affichage
                            }                          
                            break;
                        
                        case SDLK_r:
                            MatriceRandom(Matrice_avant, n, m);

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                            SDL_RenderClear(renderer);
                            draw(renderer, Matrice_avant, n, m, taille_carre);                // appel de la fonction qui crée l'image  
                            SDL_RenderPresent(renderer);                      // affichage
                            break;
                        
                        case SDLK_n:
                            //L'utilisateur souhaite taper sa propre matrice
                            LiberationMatrice(Matrice_avant, n);
                            Matrice_avant = user_matrix(renderer, n, m, taille_carre);
                            break;

                        default:
                            break;
                    }

                    break;


                default:
                    break;
            }
        }
        if(!pause)
        {
            //On fait evoluer la matrice
            evolution_matrice(Matrice_avant, Matrice_apres, n, m, B, S);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            draw(renderer, Matrice_apres, n, m, taille_carre);                // appel de la fonction qui crée l'image  
            SDL_RenderPresent(renderer);                      // affichage
        
            //On échange nos matrices pour la prochaine itération
            tmp = Matrice_avant;
            Matrice_avant = Matrice_apres;
            Matrice_apres = tmp;
            tmp = NULL;
            if(estStable(Matrice_apres, Matrice_avant, n, m) && !stable_message)
            {
                //On arrête car il n'y a plus d'évolution
                printf("C'est stable YOUUUUPI\n");
                stable_message = 1;
            }
        }
        SDL_Delay(vitesse);  

    }

    /* on referme proprement le programme */
    end_sdl(1, "Normal ending", window, renderer);
    LiberationMatrice(Matrice_avant,  n);
    LiberationMatrice(Matrice_apres,  n);



    return 0;
}