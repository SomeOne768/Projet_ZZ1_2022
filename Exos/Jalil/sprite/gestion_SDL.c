#include <stdio.h>
#include "gestion_SDL.h"
#include <math.h>


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


//Chargement d'une image
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
{
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp 

    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}



void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect 
            source = {0},                         // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    // Récupération des dimensions de la fenêtre
    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);                    

    // Récupération des dimensions de l'image
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       

    // On fixe les dimensions de l'affichage à  celles de la fenêtre
    destination = window_dimensions;              

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Création de l'élément à afficher

    SDL_RenderPresent(renderer);                  // Affichage
    SDL_Delay(2000);                              // Pause en ms

    SDL_RenderClear(renderer);                    // Effacer la fenêtre
}



void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect 
            source = {0},                         // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    // Récupération des dimensions de la fenêtre
    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);                    

    // Récupération des dimensions de l'image
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       

    // On fixe les dimensions de l'affichage à  celles de la fenêtre
    destination = window_dimensions;              

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Création de l'élément à afficher
}

void play_with_texture_2(SDL_Texture* my_texture,
                            SDL_Window* window,
                            SDL_Renderer* renderer) {

    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);               // Récupération des dimensions de la fenêtre

    //Jouer ici si l'on souhaite recupérer une partie de l'image
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);  // Récupération des dimensions de l'image

    //nb: dans play 1 l'image s'elargit pour coller au dimension
    //Ici l'image peut-être plus petite mais on effectue bien un zoom si zoom >1
    float zoom = 1.5;                        // Facteur de zoom à appliquer    
    destination.w = source.w * zoom;         // La destination est un zoom de la source
    destination.h = source.h * zoom;         // La destination est un zoom de la source
    destination.x =
    (window_dimensions.w - destination.w) /2;     // La destination est au milieu de la largeur de la fenêtre
    destination.y =
        (window_dimensions.h - destination.h) / 2;  // La destination est au milieu de la hauteur de la fenêtre

    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                &source,
                &destination);            
    SDL_RenderPresent(renderer);             
    SDL_Delay(1000);                         

    SDL_RenderClear(renderer);               // Effacer la fenêtre
}



void play_with_texture_3(SDL_Texture* my_texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
    SDL_Rect 
        source = {0},                             // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(                                
        window, &window_dimensions.w,                 
        &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,         
                    &source.w,                       
                    &source.h);                    // Récupération des dimensions de l'image

    /* On décide de déplacer dans la fenêtre         cette image */
    float zoom = 0.25;                              // Facteur de zoom entre l'image source et l'image affichée

    int nb_it = 200;                                // Nombre d'images de l'animation
    destination.w = source.w * zoom;                // On applique le zoom sur la largeur
    destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
    destination.x =                                   
        (window_dimensions.w - destination.w) / 2;  // On centre en largeur
    float h = window_dimensions.h - destination.h;  // hauteur du déplacement à effectuer

    for (int i = 0; i < nb_it; ++i) {
    destination.y =
        h * (1 - exp(-5.0 * i / nb_it) / 2 *
                        (1 + cos(10.0 * i / nb_it * 2 *
                                M_PI)));            // hauteur en fonction du numéro d'image

    SDL_RenderClear(renderer);                    // Effacer l'image précédente

    SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
    SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
    SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
    SDL_Delay(30);                                // Pause en ms
    }                                                 
    SDL_RenderClear(renderer);                      // Effacer la fenêtre une fois le travail terminé
}




void play_with_texture_4(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer) 
{
    SDL_Rect 
            source = {0},                    // Rectangle définissant la zone totale de la planche
            window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
            state = {0};                     // Rectangle de la vignette en cours dans la planche 

    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);
    SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
                    NULL, NULL,
                    &source.w, &source.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = 4;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                        // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


    state.x = 0;                          // La première vignette est en début de ligne
    state.y = 0;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;                    // Hauteur de la vignette

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

    destination.y =                        // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) /2;

    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
        destination.x = x;                   // Position en x pour l'affichage du sprite
        state.x += offset_x;                 // On passe à la vignette suivante dans l'image
        state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                            // celle de début de ligne

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                    &state,
                    &destination);  
        SDL_RenderPresent(renderer);         // Affichage
        SDL_Delay(80);                       // Pause en ms
    }
    SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
}


animation CreerAnimation(SDL_Window *window, SDL_Renderer *renderer, char *filename , int tab[], int taille, int nb_img)
{
    animation anim;
    
    //Récupération de la texture
    anim.texture = load_texture_from_image(filename, window, renderer);

    //Récupération de la suite
    int *suite = (int*)malloc(sizeof(int) * taille);
    for(int i =0; i<taille; i++)
    {
        suite[i] = tab[i];
    }
    anim.suite = suite;
    anim.taille = taille;   
    anim.nb_img = nb_img; 
    return anim;
}

void LibererAnimation(animation *anim)
{
    free(anim->suite);
    SDL_DestroyTexture(anim->texture);
}


void play(SDL_Window *window, SDL_Renderer *renderer, animation anim)
{
    //Création des rectangles pour récupérer les différents éléments
    SDL_Rect 
            source = {0},                    // Rectangle définissant la zone totale de la planche
            window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
            state = {0};                     // Rectangle de la vignette en cours dans la planche 


    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                        &window_dimensions.w,
                        &window_dimensions.h);


    SDL_QueryTexture(anim.texture,           // Récupération des dimensions de l'image
                    NULL, NULL,
                    &source.w, &source.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = anim.nb_img;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                        // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


    state.x = 0;                          // La première vignette est en début de ligne
    state.y = 0;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;                    // Hauteur de la vignette

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

    destination.y =                        // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) /2;

    int speed = 9;
    int indice_suite = 0;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
        destination.x = x;                   // Position en x pour l'affichage du sprite
        state.x = anim.suite[indice_suite] * offset_x;// On passe à la vignette suivante dans l'image
        state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                            // celle de début de ligne*
        indice_suite %= anim.taille;        //un fois la suite réaliser on recommence la même
        indice_suite++;

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, anim.texture, // Préparation de l'affichage
                    &state,
                    &destination);  
        SDL_RenderPresent(renderer);         // Affichage
        SDL_Delay(80);                       // Pause en ms
    }
    SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main


}





void play_with_texture_5(SDL_Texture *bg_texture,
                        animation anim,
                        SDL_Window *window,
                        SDL_Renderer *renderer) {
    SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w, 
                    &window_dimensions.h); 

    SDL_QueryTexture(anim.texture, NULL, NULL,    // Récupération des dimensions de l'image
                    &source.w, &source.h); 

    int nb_images = 4;                         //  Il y a 8 vignette dans la ligne qui nous intéresse
    int nb_images_animation = 20 * nb_images;    // 
    float zoom = 2;                             // zoom, car ces images sont un peu petites
    int offset_x = source.w/anim.nb_img,                // La largeur d'une vignette de l'image
        offset_y = source.h;                // La hauteur d'une vignette de l'image
    SDL_Rect state[4];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int i = 0;                                   

    for (int x = 0; x < source.w; x += offset_x) 
    {
        state[i].x = x;
        state[i].y = 0;
        state[i].w = offset_x;
        state[i].h = offset_y;
        ++i;
    }


    destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
    destination.x = window_dimensions.w * 0.45; // Position en x pour l'affichage du sprite
    destination.y = window_dimensions.h * 0.7;  // Position en y pour l'affichage du sprite

    i = 0;
    for (int cpt = 0; cpt < nb_images_animation ; ++cpt) 
    {
        play_with_texture_1_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                                window, renderer); 
        SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                        anim.texture, &state[i], &destination);
        i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
        SDL_RenderPresent(renderer);              // Affichage
        SDL_Delay(100);                           // Pause en ms
    }
    SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}