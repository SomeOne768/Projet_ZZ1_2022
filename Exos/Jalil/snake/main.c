#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define RBALLE 10
#define SIZE 20


/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/* Ce programme genere un carrré qui doit "manger" les petites cercles qui apparaissent. Il grossit à chaque fois    */
/*********************************************************************************************************************/

int x_balle = 200;
int y_balle = 200;


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
        SDL_DestroyRenderer(renderer);                                // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
        window= NULL;
    }

    SDL_Quit();                                                                     

    if (!ok) {                                                        // On quitte si cela ne va pas                
        exit(EXIT_FAILURE);                                                           
    }                                                                               
}                                                                                 

void draw(SDL_Renderer* renderer, SDL_Rect rectangle, int r, int g, int b) 
{                                             

    SDL_SetRenderDrawColor(renderer,                                                
                            r, g, b,                                  // mode Red, Green, Blue (tous dans 0..255)
                            255);                                      // 0 = transparent ; 255 = opaque
    
    SDL_RenderFillRect(renderer, &rectangle); 
    //Dessin du point objectif
    SDL_RenderDrawPoint(renderer,                                   
                    500,                     // coordonnée en x
                    500);                    //            en y   

    for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 40) {      
        SDL_RenderDrawPoint(renderer,                                   
                            x_balle + RBALLE * cos(angle),                     // coordonnée en x
                            y_balle + RBALLE * sin(angle));   
    }                   

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   

                     

}

int Amanger(SDL_Rect rectangle, int x, int y)
{
    int xg = rectangle.x,
        xd = rectangle.x + rectangle.w,
        yh = rectangle.y,
        yb = rectangle.y + rectangle.h;

    if( xg < (x + (RBALLE/2)) && (x + (RBALLE/2)) < xd)
    {
        if( yh < (y + (RBALLE/2)) && (y + (RBALLE/2)) < yb)
        {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  srand( time(NULL) );

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

  /*********************************************************************************************************************/
  /*                                     On dessine dans le renderer                                                   */
  /*********************************************************************************************************************/
  /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */

    int continuer = 1;
    SDL_Rect rectangle;
    rectangle.x = 0;                                          
    rectangle.y = 0;                                         
    rectangle.w = 50;                                               
    rectangle.h = 50;
    int r = 150;
    int g = 0;
    int b = 0;
    int vitesse = 10;

    int width = screen.w * 0.66,
        height = screen.h * 0.66;

    SDL_Event event;
    while(continuer)
    {  

        //On détecte les evenements qui modifient notre affichage

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
                            rectangle.x += vitesse;
                            if((rectangle.x+rectangle.w)>width)
                            {
                                rectangle.x = width - rectangle.w;
                            }
                            event.drop.file;
                            break;

                        case SDLK_LEFT:
                            rectangle.x -= vitesse;
                            if(rectangle.x<0)
                            {
                                rectangle.x = 0;
                            }
                            break;

                        case SDLK_DOWN:
                            rectangle.y += vitesse;
                            if((rectangle.y+rectangle.h)>height)
                            {
                               
                                rectangle.y = height-rectangle.h;
                            }
                            break;

                        case SDLK_UP:
                            rectangle.y -= vitesse;
                            if(rectangle.y<0)
                            {
                                rectangle.y = 0;
                            }
                            break;
                        
                        default:
                            break;
                    }

                    if(Amanger(rectangle, x_balle , y_balle))
                    {
                        //On grossit le rectangle
                        rectangle.w += SIZE;
                        rectangle.h += SIZE;

                        //On genere une nouvelle balle
                        x_balle = rand()%(width-(RBALLE/2)) + RBALLE/2;
                        y_balle = rand()%(height-(RBALLE/2)) + RBALLE/2;
                    }

                    break;
                
                default:
                    break;
            }
        }
        
        //On efface l'écran puis on redessine par dessus
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        draw(renderer, rectangle, r,g,b);                 // appel de la fonction qui crée l'image  
        SDL_RenderPresent(renderer);                      // affichage
        SDL_Delay(5);                                     // Pause exprimée en ms

    }


    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}

