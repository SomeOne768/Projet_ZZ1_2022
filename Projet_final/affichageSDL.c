#include <stdio.h>
#include "affichageSDL.h"

#define VITESSE 5

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
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
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;   // Variable de passage
    SDL_Texture *my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                          // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                          // uniquement possible si l'image est au format bmp */
    if (my_image == NULL)
        end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL)
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

// Fonction d'ajout d'une image sur un plan
void appliquer_image(SDL_Texture *texture, SDL_Window *window, SDL_Renderer *renderer, int nb_images_ligne,
                     int nb_images_col, int num_ligne, int num_col, int x, int y, float zoom)
{
    // Je suis sur de regretter plus tard de ne pas prendre le nombre vignette par ligne / colonne AHAHAH J4AVAISRAISON
    // Création des rectangles pour récupérer les différents éléments
    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);

    SDL_QueryTexture(texture, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source.w, &source.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int offset_x = source.w / nb_images_ligne, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / nb_images_col;   // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

    state.x = num_col * offset_x;   // La première vignette est en début de ligne
    state.y = num_ligne * offset_y; // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;             // Largeur de la vignette
    state.h = offset_y;             // Hauteur de la vignette

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

    destination.y = y;
    destination.x = x;

    SDL_RenderCopy(renderer, texture, // Préparation de l'affichage
                   &state,
                   &destination);
}

void appliquer_background(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                   &source,
                   &destination); // Création de l'élément à afficher
}

void deplacement_personnage(SDL_Texture *texture, SDL_Window *window, SDL_Renderer *renderer,
                            coordonnee depart, coordonnee arrive, float zoom)
{
    // Pour eviter d'avoir un nombre d'argument trop énorme on va considere le format de nos images actuelles
    // Vais-je encore le regretter plus tard ? Oui !
    // Vais-je regretter de ne pas avoir utiliser la structure animation ? Oui !

    int delta_x = arrive.x - depart.x,
        delata_y = arrive.y - depart.y;

    int sens_horizontal = 1, // droite
        sens_vertical = 1;   // bas

    if (delta_x < 0)
    {
        // On va a gauche
        sens_horizontal = -1;
    }

    if (delata_y < 0)
    {
        // on va en haut
        sens_vertical = -1;
    }

    // On commence par se déplacer sur x => ligne 1 (gauche) ou 2 (droite)

    // A finir, ligne pour enlever les "unused"
    printf("%p %p %p %f %d %d", texture, window, renderer, zoom, sens_vertical, sens_horizontal);

    // On se déplace maintenant sur y => ligne 0 (bas) ou 3 (haut)
}