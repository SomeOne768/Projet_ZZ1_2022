#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window 
    *window_1 = NULL;
    //SDL_Window * window_2 = NULL;
    int x=0;
    int y=0;
    int w=800;
    int h=400;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", 
        SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
        
    window_1 = SDL_CreateWindow(
      "Fenêtre !!!",                    // codage en utf8, donc accents possibles
      x, y,                                  // coin haut gauche en haut gauche de l'écran
      w,h,                              // largeur = 800, hauteur = 400
      SDL_WINDOW_RESIZABLE);                 // redimensionnable

    if (window_1 == NULL) 
    {
        SDL_Log("Error : SDL window 1 creation - %s\n", 
        SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }
    
    SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
    SDL_Event event;                              // c'est le type IMPORTANT !!
    int *a = &x;
    int *b = &y;
    /*int *c = &w;
    int *d = &h;*/
    while (program_on)
    {                           // Voilà la boucle des évènements 
        if (SDL_PollEvent(&event))
        {                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
                                                    // de file dans 'event'
            SDL_GetWindowPosition(window_1,a,b);

            switch(event.type)
            {                       // En fonction de la valeur du type de cet évènement
                case SDL_QUIT:                           // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE;                 // Il est temps d'arrêter le programme
                break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case 'f':
                        program_on = 0;
                        break;

                        case 'm':
                        SDL_SetWindowPosition(window_1, *a+10, *b+10);
                        break;

                        case 'o':
                        SDL_SetWindowPosition(window_1, *a-10, *b-10);
                        break;

                        case 'p':
                        SDL_SetWindowPosition(window_1, *a+10, *b-10);
                        break;

                        case 'l':
                        SDL_SetWindowPosition(window_1, *a-10, *b+10);
                        break;

                        case 'z':
                        SDL_SetWindowPosition(window_1, *a, *b-10);
                        break;

                        case 'q':
                        SDL_SetWindowPosition(window_1, *a-10, *b);
                        break;

                        case 's':
                        SDL_SetWindowPosition(window_1, *a, *b+10);
                        break;

                        case 'd':
                        SDL_SetWindowPosition(window_1, *a+10, *b);
                        break;

                        default:
                        break;
                        
                    }
                default:
                break;
            }
        }
    }
     
    SDL_Delay(50);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    return 0;
}
