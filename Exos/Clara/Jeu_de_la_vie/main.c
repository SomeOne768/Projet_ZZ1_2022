#include <stdio.h>
#include <stdlib.h>
#include "regles.h"
#include "monde_limite.h"
#include "monde_tore.h"
#include <SDL2/SDL.h>
#include <string.h>
//#include <time.h>


void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
        char const* msg,                                       // message à afficher
        SDL_Window* window,                                    // fenêtre à fermer
        SDL_Renderer* renderer)        
{                              // renderer à fermer
    char msg_formated[255];                                                         
    int l;                                                                          

    if (!ok) 
    {                                                        // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);                                              
        l = strlen(msg_formated);                                                     
        strcpy(msg_formated + l, " : %s\n");                                          

        SDL_Log(msg_formated, SDL_GetError());                                        
    }                                                                               

    if (renderer != NULL) 
    {                                           // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)   
    {                                           // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
        window= NULL;
    }

                                                                     

    if (!ok) 
    {                                                        // On quitte si cela ne va pas                
        exit(EXIT_FAILURE);                                                           
    }    
    SDL_Quit();                                                                         
}                  
 


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int Birth[9]={1, 0, 0, 0, 1, 0, 1, 0, 1};             
    int Survive[9]={1, 0, 0, 0, 1, 0, 0, 0, 0};

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;
    int h=5;//taille du carré


    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", 
        SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    /*********************************************************************************************************************/  
  /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
         screen.w, screen.h);

    int largeur= 0.8*screen.w;
    int hauteur= 0.8*screen.h;

    largeur= largeur-(largeur%h); //pour tomber sur le bon nb de carrés
    hauteur= hauteur-(hauteur%h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de la vie",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, largeur,
                                hauteur,
                                SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    int torique=1;
    int n= hauteur/h;
    int m= largeur/h;

    char** Matrice1=CreerMatrice(n,m);
    char** Matrice2=CreerMatrice(n,m);
    char ** tmp;



    int vitesse=50;

    
    //si on veut une disposition initiale aléatoire (ici, on fait saisir par l'utilisateur) donc on ne s'en sert pas

    // srand(time(NULL));
    // for (int i=0; i<n; i++)
    // {
    //     for (int j=0; j<m; j++)
    //     {
    //         Matrice1[i][j]=rand()%2;
    //     }
    // }
    
    
   

//int Birth[9], Survive[9];
    //extraire_regles(saisie, Birth, Survive);

    

    //Partie Récupération d'une matrice avec des click de l'utilisateur
    int continuer=1;
    SDL_Event event;

      for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            Matrice1[i][j] = 0;
        }
    }
    int x,y;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); 

    //On utilise souris pour choisir situation initiale
    while(continuer)
    {
        while(continuer&& SDL_PollEvent(&event))
        {

            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE)
                    {
                        continuer = 0;
                    }
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;
                     y = event.motion.y;
                     colorerMatrice(Matrice1, h, x, y);
                    
                     break;
                
                default:
                    break;
            }
        }
        draw(renderer, Matrice1, n, m, h); 
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }



    continuer=1;
    while (continuer)
    {
        while (continuer && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer=0;
                    break;

                 case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                         case SDLK_RIGHT:
                             vitesse=vitesse-10;
                             if(vitesse<1)
                             {
                                 vitesse=1;
                             }
                             break;



                         case SDLK_LEFT:
                             vitesse+=10;
                             if (vitesse>2000)
                             {
                                 vitesse=2000;
                             }
                             break;

                         case 's':
                            enregistrerMatrice(Matrice1, n, m, "fichier2.txt" );
                            break;

                         case 'l':
                            Liberation_matrice(Matrice1,n);
                            Matrice1=chargerMatrice("fichier2.txt");
                            break;


                         default:
                             break;
                     }
                     break;

                default:
                    break;


            }
            

        }

        if (torique) nvlle_matricet(Matrice1,Matrice2, n, m, Birth, Survive); //selon si monde torique ou limité
        else nvlle_matrice(Matrice1,Matrice2, n, m, Birth, Survive);
        tmp=Matrice1;
        Matrice1=Matrice2;
        Matrice2=tmp;

        if (etatstable(Matrice1, Matrice2, n,m))
        {
            printf("L'état est stable \n");
            continuer=0;
            vitesse=1000;
        }
        

    

        draw(renderer, Matrice1, n, m, h);
        SDL_RenderPresent(renderer);                         // affichage
        SDL_Delay(vitesse); 


    
    }
    end_sdl(1, "Normal ending", window, renderer);
    Liberation_matrice(Matrice1, n);
    Liberation_matrice(Matrice2, n);
    

    //Liberation_matrice(Matrice,n);

    return 0;
}