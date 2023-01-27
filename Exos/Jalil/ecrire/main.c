#include <stdio.h>
#include <SDL2/SDL_ttf.h>                                            // Charger la bibliothèque



void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer)                                // renderer à fermer
{                              
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
    if (!ok) {                                                        // On quitte si cela ne va pas                
        exit(EXIT_FAILURE);                                                           
    }

}  



int main()
{


    //Initialisation de la SDL
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
            screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de la vie",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 
                                0.66*screen.w,
                                0.66*screen.h,
                                SDL_WINDOW_OPENGL);

    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);


    if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font* font = NULL;                                               // la variable 'police de caractère'
    font = TTF_OpenFont("./font/paulo-pacito.ttf", 65);                     // La police à charger, la taille désirée
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);           // en italique, gras

    SDL_Color color = {255, 255, 255, 255};                                  // la couleur du texte
    SDL_Surface* text_surface = NULL;                                    // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, "Hello World !", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien

    SDL_Rect pos = {0, 0, 0, 0};                                         // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer   
    SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte

    SDL_RenderPresent(renderer);                                         // Affichage 
    SDL_Delay(2000);



    TTF_Quit();  


    return 0;
}
