#include <SDL2/SDL.h>
#include <stdio.h>

/********************************************/
/* Vérification de l'installation de la SDL */
/********************************************/

int main(int argc, char **argv) {
    SDL_version nb;
    SDL_VERSION(&nb);

    /*

    -----------------------------------
    | PLEIN DE TESTS POUR COMPRENDRE  |
    -----------------------------------

    printf("Version de la SDL : %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    SDL_Window
        *window_1 =NULL,
        *window_2 =NULL,
        *window_3 =NULL,
        *window_4 =NULL,
        *window_5 =NULL,
        *window_6 =NULL;

    if (SDL_Init(SDL_INIT_VIDEO)!=0)  //initialisation échoue
    {
      fprintf(stderr, "Erreur\n");
      exit(EXIT_FAILURE);

    }

    window_1 = SDL_CreateWindow(
        "Fenêtre 1",                    // codage en utf8, donc accents possibles
        0, 0,                                  // coin haut gauche en haut gauche de l'écran
        200, 150,                              // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE);

    SDL_Delay(2000);

    window_2 = SDL_CreateWindow(
        "Fenêtre 2",                    // codage en utf8, donc accents possibles
        1200, 0,                                  // 1450 pixels en largeur
        250, 150,                             
        SDL_WINDOW_RESIZABLE);

    SDL_Delay(2000);
    
    window_3 = SDL_CreateWindow(
        "Fenêtre3",                    // codage en utf8, donc accents possibles
        200, 0,                                  
        200, 150,                              // largeur = 200, hauteur = 150
        SDL_WINDOW_RESIZABLE);
    SDL_Delay(2000);

    window_4 = SDL_CreateWindow(
        "Fenêtre 4",                    // codage en utf8, donc accents possibles
        200, 0,                                  // coin haut gauche en haut gauche de l'écran
        400, 300,                              // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE);
    

    SDL_Delay(2000);

    window_5 = SDL_CreateWindow(
        "Fenêtre 5",                    // codage en utf8, donc accents possibles
        200, 200,                                  
        400, 300,                              
        SDL_WINDOW_RESIZABLE);


    SDL_Delay(2000);

    window_6 = SDL_CreateWindow(
        "Fenêtre 6",                    // codage en utf8, donc accents possibles
        0, 800,                                  // 1100 pixels en hauteur
        400, 300,                              
        SDL_WINDOW_RESIZABLE); 


    SDL_Delay(2000);

    if (window_1 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", 
            SDL_GetError());                 // échec de la création de la fenêtre
                                       
    exit(EXIT_FAILURE);}

    if (window_2 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", 
            SDL_GetError());                 // échec de la création de la fenêtre
                                  
    exit(EXIT_FAILURE);}

    if (window_3 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", 
            SDL_GetError());                 // échec de la création de la fenêtre
                                   
    exit(EXIT_FAILURE);}

    if (window_4 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", 
            SDL_GetError());                 // échec de la création de la fenêtre
                             // On referme la SDL       
    exit(EXIT_FAILURE);}

    if (window_5 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", 
            SDL_GetError());                 // échec de la création de la fenêtre
                                  // On referme la SDL       
    exit(EXIT_FAILURE);}

    if (window_6 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", 
            SDL_GetError());
            exit(EXIT_FAILURE);                 // échec de la création de la fenêtre
    }SDL_Quit();                              // On referme la SDL       
    
    */

    int x=0;
    int y=0;

    SDL_Window
        *window_1 =NULL;

    if (SDL_Init(SDL_INIT_VIDEO)!=0)  //initialisation échoue
    {
      fprintf(stderr, "Erreur\n");
      exit(EXIT_FAILURE);

    }
    window_1 = SDL_CreateWindow(
        "Fenêtre 1",                    // codage en utf8, donc accents possibles
        x, y,                                  
        250, 150,                              // largeur = 200, hauteur = 150
        SDL_WINDOW_RESIZABLE);

    if (window_1 == NULL) 
    {
        SDL_Log("Error : SDL window 1 creation - %s\n", 
                SDL_GetError());                 // échec de la création de la fenêtre
                                        
        exit(EXIT_FAILURE);
        SDL_Quit(); 
    }


    SDL_bool
        program_on = SDL_TRUE;                          // Booléen pour dire que le programme doit continuer
                                // Booléen pour dire que le programme est en pause
    SDL_Event event;                                  // Evènement à traiter

    while (program_on) 
    {                              // La boucle des évènements
        if(SDL_PollEvent(&event))
        {                                                  
            switch (event.type) 
            {                         // En fonction de la valeur du type de cet évènement
                case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
                    program_on =0;                     // Il est temps d'arrêter le programme
                    break;

                case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                           
                    switch (event.key.keysym.sym) 
                    {             // la touche appuyée est ...
                        //case SDLK_q:                                // 'q'
                        case SDLK_SPACE:
                            program_on=0;
                            break;
                        default:                                    // Une touche appuyée qu'on ne traite pas
                            break;
                    
                    }
                break;

                default:
                    break;
                
            }
             
            
        }
        if (x<1680 && y==0)
        {
            x=x+2;
            SDL_SetWindowPosition(window_1, x, y);
            SDL_Delay(20);
        }
        else
        {
            if (x==1680 && y<1100)
            {
                y=y+2;
                SDL_SetWindowPosition(window_1, x, y);
                SDL_Delay(20);
            }
            else
            {
                if (x>0 && y==1100)
                {
                    x=x-2;
                    SDL_SetWindowPosition(window_1, x, y);
                    SDL_Delay(20);
                }

                else
                {
                    if (y>0 && x==0)
                    {
                        y=y-2;
                        SDL_SetWindowPosition(window_1, x, y);
                        SDL_Delay(20);
                    }
                }

            }
                                            
        }
    }

    
    
    return 0;
}