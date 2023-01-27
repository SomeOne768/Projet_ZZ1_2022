#include <SDL2/SDL_ttf.h>
#include "ecriture.h"
#include "affichageSDL.h"

// créer les surfaces pour afficher les compteurs de chaque aliment
SDL_Surface **creation_surfaces(int compteurs[3], TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer, int platdistribue)
{
    SDL_Color noir = {0, 0, 0, 255};
    SDL_Color rouge = {225, 23, 23, 255};
    SDL_Color color;
    // on va afficher en rouge le plat qui est ditribué
    SDL_Surface **text_surface = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 3); // la surface  (uniquement transitoire)

    char temp[10];
    for (int i = 0; i < 3; i++)
    {
        if (platdistribue == i)
            color = rouge; // plat distribue est 0, 1 ou 2 (nachos, burritos, tacos)
        else
            color = noir;
        sprintf(temp, "%d", compteurs[i]);

        text_surface[i] = TTF_RenderText_Blended(font, temp, color); // création du texte dans la surface
        if (text_surface[i] == NULL)
        {
            i--;
            while (i >= 0)
            {
                SDL_FreeSurface(text_surface[i]);
                i--;
            }
            free(text_surface);
            end_sdl(0, "Can't create text surface", window, renderer);
        }
    }
    
    return text_surface;
}

// créer les textures pour afficher le compteur de chaque aliment
void affiche_compteur(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface **text_surface)
{
    SDL_Rect
        window_dimensions = {0},
        pos;
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    SDL_Texture **text_texture = (SDL_Texture **)malloc(sizeof(SDL_Surface *) * 3);
    int position_x = 0.078 * window_dimensions.w, position_y = 0.0185 * window_dimensions.h, separation = 0.088 * window_dimensions.h;
    pos.x = position_x;
    pos.y = position_y;
    for (int i = 0; i < 3; i++)
    {
        text_texture[i] = SDL_CreateTextureFromSurface(renderer, text_surface[i]); // transfert de la surface à la texture
        if (text_texture[i] == NULL)
            end_sdl(0, "Can't create texture from surface", window, renderer);

        // SDL_FreeSurface(text_surface[i]);
        if (i != 0)
            pos.y = pos.y + separation;

        SDL_QueryTexture(text_texture[i], NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
        SDL_RenderCopy(renderer, text_texture[i], NULL, &pos);
    }

    // free(text_texture);
}

void LibererCompteur(SDL_Surface ***text_surface)
{
    for (int i = 0; i < 3; i++)
    {
        SDL_FreeSurface((*text_surface)[i]);
    }
    free(*text_surface);
}

SDL_Texture *appliquer_profit(SDL_Renderer *renderer, TTF_Font *font, int profit, SDL_Rect *pos)
{
    SDL_Color noir = {0, 0, 0, 255};
    char tmp[10];
    sprintf(tmp, "%d", profit);
    SDL_Surface *profit_surface = TTF_RenderText_Blended(font, tmp, noir);
    SDL_Texture *profit_texture = SDL_CreateTextureFromSurface(renderer, profit_surface);
    SDL_QueryTexture(profit_texture, NULL, NULL, &(pos->w), &(pos->h));
    SDL_FreeSurface(profit_surface);

    return profit_texture;
}

void affiche_nourriture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture **texture_nourriture)
{

    // Affichage des différents produits vendus
    int posy,
        posx,
        width,
        height,
        deltay;
    SDL_GetWindowSize(window, &width, &height);

    deltay = 0.09 * height;
    posx = 0.01 * width;
    posy = 0.0185 * height;

    appliquer_image(texture_nourriture[0], window, renderer, 1, 1, 0, 0, posx, posy, 0.7);
    posy += deltay;
    appliquer_image(texture_nourriture[1], window, renderer, 1, 1, 0, 0, posx, posy, 0.7);
    posy += deltay;
    appliquer_image(texture_nourriture[2], window, renderer, 1, 1, 0, 0, posx, posy, 0.7);
}
