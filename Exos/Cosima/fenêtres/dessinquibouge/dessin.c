#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

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

    SDL_Quit();                                                                     

    if (!ok) 
    {                                                        // On quitte si cela ne va pas                
        exit(EXIT_FAILURE);                                                           
    }                                                                               
}                                                                                 

void draw(SDL_Renderer* renderer, int x, int y) 
{                                 // Je pense que vous allez faire moins laid :)
    SDL_Rect rectangle;                                                             
    
    SDL_SetRenderDrawColor(renderer,                                                
                            246, 211, 14,                                  // mode Red, Green, Blue (tous dans 0..255)
                            255);                                      // 0 = transparent ; 255 = opaque
    rectangle.x = x;                                                  // x haut gauche du rectangle
    rectangle.y = y;                                                  // y haut gauche du rectangle
    rectangle.w = 400;                                                // sa largeur (w = width)
    rectangle.h = 400;                                                // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle);                         
        
}
    
int main(int argc, char** argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/  
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",screen.w, screen.h);
            
    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                                screen.h * 0.66,
                                SDL_WINDOW_OPENGL);
    if (window == NULL) 
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/
    /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */ 
    
    /*draw(renderer, x, y);                                      // appel de la fonction qui crée l'image  
    SDL_RenderPresent(renderer);                         // affichage
    SDL_Delay(10000); */                                   // Pause exprimée en ms

    //SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
    SDL_Event event;
    int x = 0;
    int y = 0;                              // c'est le type IMPORTANT !!
    int program_on = 1;
    int evenement = 0;
    SDL_RenderPresent(renderer);
    while (program_on)
    {                           // Voilà la boucle des évènements 
        if (SDL_PollEvent(&event))
        {                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
                                                    // de file dans 'event'
            switch(event.type)
            {                       // En fonction de la valeur du type de cet évènement
                case SDL_QUIT:                           // Un évènement simple, on a cliqué sur la x de la fenêtre
                    program_on = 0;                 // Il est temps d'arrêter le programme
                    break;

                case SDL_KEYDOWN:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    switch(event.key.keysym.sym)
                    {
                        case 'f':
                            program_on = 0;
                            evenement = 1;
                            break;

                        case 'z':
                            y -= 10;    
                            if(y<0) y = 0;
                            draw(renderer, x, y);
                            evenement = 1;
                        
                        break;
                        
                        case 's':
                            y += 10;    
                            if(y<0) y = 0;
                            draw(renderer, x, y);
                            evenement = 1;
                        
                        break;

                        case 'q':
                            x -= 10;
                            if(x<0) x=0;
                            draw(renderer, x, y);
                            evenement = 1;
                            break;
                                    
                        case 'd':
                            x+=10;
                            draw(renderer, x, y);
                            evenement = 1;
                            break;

                        default:
                            break; 
                    }

                default:
                break;
            }
            
            
        }

        if (evenement)
        {
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
            evenement = 0;
        }
        
        
    }
    /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}