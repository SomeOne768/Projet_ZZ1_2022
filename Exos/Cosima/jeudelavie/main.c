#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "delimite.h"
#include "regles.h"
#include "tore.h"
#include <time.h>

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer) 
{                              
    char msg_formated[255];                                                         
    int l;                                                                          

    if (!ok) 
    {                                                      
        strncpy(msg_formated, msg, 250);                                              
        l = strlen(msg_formated);                                                     
        strcpy(msg_formated + l, " : %s\n");                                          
        SDL_Log(msg_formated, SDL_GetError());                                        
    }                                                                               

    if (renderer != NULL) 
    {                                           
        SDL_DestroyRenderer(renderer);                               
        renderer = NULL;
    }

    if (window != NULL)
    {                                           
        SDL_DestroyWindow(window);                                     
        window= NULL;
    }

    SDL_Quit();                                                                     

    if (!ok) 
    {
        exit(EXIT_FAILURE);
    }                                                                               
}



int main(int argc, char **argv)
{
    srand(time(NULL));
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;

    
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",screen.w, screen.h);
    
    int taille_carre = 10;

    int width = screen.w * 0.8;
    int height = screen.h * 0.8;
    width = width - (width%taille_carre);
    height = height - (height%taille_carre);




    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (window == NULL) 
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);


    int n = height/taille_carre;
    int m = width/taille_carre;

    //récupérer les arguments argv dans saisie

    char B[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};
    char S[9] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    
    char ** matrice = CreerMatrice(n, m);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            matrice[i][j] = rand()%2;
        }
    }

    
    char ** futurematrice = CreerMatrice(n, m);
    char **tmp;
    int acceleration = 200;
    int mode = 0;
    int ecrit = 0;
    SDL_bool program_on = SDL_TRUE;               
    SDL_Event event;
    while (program_on)
    {              
                    
        while (program_on && SDL_PollEvent(&event))
        {          
                  
            switch(event.type)
            {                       
                case SDL_QUIT:                          
                    program_on = SDL_FALSE;                 
                    break;

                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            acceleration = acceleration -10;
                            if (acceleration < 20)
                                acceleration = 20;
                            break;

                        case SDLK_LEFT:
                            acceleration = acceleration +10;
                            if (acceleration > 2000)
                                acceleration = 2000;
                            break;
                        case 'f':
                            program_on = SDL_FALSE;                 
                            break;
                        case 'm':
                            if (mode == 0)
                                mode = 1;
                            if (mode == 1)
                                mode = 0;
                        default:
                            break;
                    }

                default:
                break;
            }
        }
        if (mode == 0)
        {
            future_matrice_delimite(matrice, n, m, B, S, futurematrice);
        }
        else
        {
            future_matrice_tore(matrice, n, m, B, S, futurematrice);
        }
        drawMatrice(renderer, n, m, matrice, taille_carre);
        int stable = compareMatrice(matrice, futurematrice, n, m);
        if (stable == 1 && ecrit == 0)
        {
            printf("L'état est stable \n");
            ecrit++;
        }
            
       
        tmp = matrice;
        matrice = futurematrice;
        futurematrice = tmp;

        SDL_RenderPresent(renderer);
        SDL_Delay(acceleration);
    }


    LibererMatrice(n, matrice);
    LibererMatrice(n, futurematrice);
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

