#include "dessin.h"


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
    SDL_DestroyRenderer(renderer);                                  // On suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window);                                      // On suppose que les NULL sont maintenus !!
    window= NULL;
  }

  SDL_Quit();                                                                     

  if (!ok) {                                                        // On quitte si cela ne va pas                
    exit(EXIT_FAILURE);                                                           
  }                                                                               
}                                                                                 

void draw(SDL_Renderer* renderer, int x, int y)   
{

    srand(time(NULL));
    int signe1=rand()%2;
    int signe2=rand()%2;
    
    SDL_Rect rectangle;                                                             
    SDL_SetRenderDrawColor(renderer,                                                
                         255, 153, 255,                                  // mode Red, Green, Blue (tous dans 0..255)
                         255);                                      // 0 = transparent ; 255 = opaque
    if (signe1==0)
    {


        if (signe2==0)
        {
            rectangle.x = 250+x;                                                  // x haut gauche du rectangle
            rectangle.y = 250+y;                                                  // y haut gauche du rectangle
            rectangle.w = 400+3*cos(10*x);                                                // sa largeur (w = width)
            rectangle.h = 400+3*cos(10*y); 
        }
        else
        {
            rectangle.x = 245+x;                                                  // x haut gauche du rectangle
            rectangle.y = 250+y;                                                  // y haut gauche du rectangle
            rectangle.w = 400+3*cos(10*x);                                                // sa largeur (w = width)
            rectangle.h = 400+3*cos(10*y);

        }

        
        
    }
    else 
    {

        if(signe2==0)
        {
            rectangle.x = 250+x;                                                  // x haut gauche du rectangle
            rectangle.y = 245+y-5;                                                  // y haut gauche du rectangle
            rectangle.w = 400+3*cos(10*x);                                                // sa largeur (w = width)
            rectangle.h = 400-3*cos(10*y);

        }
        else
        {
            rectangle.x = 245+x;                                                  // x haut gauche du rectangle
            rectangle.y = 245+y;                                                  // y haut gauche du rectangle
            rectangle.w = 400+3*cos(10*x);                                                // sa largeur (w = width)
            rectangle.h = 400-3*cos(10*y);

        }
                 
            
                                                   // sa hauteur (h = height)
    }
    SDL_RenderFillRect(renderer, &rectangle);                         

    SDL_SetRenderDrawColor(renderer, 51, 250, 0, 255);
  

}