#include <SDL2/SDL.h>
#include <stdio.h>
#include "dessin.h"


/*
 
CARRE QUI BOUGE ET SE DILATE PUIS SE RETRACTE

*/

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  int x=0;
  int y=0;


  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_DisplayMode screen;

  /*********************************************************************************************************************/  
  /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
         screen.w, screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                            screen.h * 0.66,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);



        SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
SDL_Event event;                              // c'est le type IMPORTANT !!

while (program_on && x<200 )
{                           // Voilà la boucle des évènements 
  while (program_on && SDL_PollEvent(&event))
  {                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
                                              // de file dans 'event'
    switch(event.type)
    {                       // En fonction de la valeur du type de cet évènement
        case SDL_QUIT :                           // Un évènement simple, on a cliqué sur la x de la fenêtre
          program_on = SDL_FALSE;                 // Il est temps d'arrêter le programme
          break;
        
        case SDL_KEYDOWN: 
          switch(event.key.keysym.sym)
          {
            case SDLK_ESCAPE:                           // 'ESCAPE'  
          case SDLK_q:                                // ou 'q'
            program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
            break;
          default:                                    // Une touche appuyée qu'on ne traite pas
            break;
          }
          

        default:                                  // L'évènement défilé ne nous intéresse pas
          break;
    }
  }
  // Affichages et calculs souvent ici
   
  x=x+1;
  y=y+1;
  draw(renderer, x, y);                                      // appel de la fonction qui crée l'image  
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Delay(100);
  }                                                     // affichage
                                      // Pause exprimée en ms


  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}

