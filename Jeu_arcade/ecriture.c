#include <SDL2/SDL_ttf.h>
#include "ecriture.h"
#include "animation.h"

//créer les surfaces pour afficher les scores de chaque poisson
SDL_Surface** creation_surfaces(int poisson[8], int dernier_poisson, TTF_Font* font, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Color noir = {0, 0, 0, 255};                                  // la couleur du compteur de poissons attrapés
    SDL_Color rouge = {225, 23, 23, 255};                                  // la couleur du compteur de poissons du dernier poisson attrapé
    SDL_Color color;
    SDL_Surface **text_surface = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 8);                                    // la surface  (uniquement transitoire)

    char temp[10];
    for (int i=0; i<8; i++)
    {
        if (dernier_poisson == i)
            color = rouge;
        else color=noir;

        sprintf(temp, "%d", poisson[i]);

        text_surface[i] = TTF_RenderText_Blended(font, temp, color); // création du texte dans la surface
        if (text_surface[i] == NULL) 
            end_sdl(0, "Can't create text surface", window, renderer);

    }
    return text_surface;
}

//créer les textures pour afficher les scores de chaque poisson
void affiche_score(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface** text_surface)
{
    SDL_Rect 
            window_dimensions = {0},     
            pos; 
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    SDL_Texture ** text_texture  = (SDL_Texture**)malloc(sizeof(SDL_Surface*) * 8);  
    int position_x = 100, position_y = 50, separation =window_dimensions.w / 10;
    pos.x = position_x;
    pos.y = position_y;
    for (int i=0; i<8; i++)
    {
        text_texture[i] = SDL_CreateTextureFromSurface(renderer, text_surface[i]); // transfert de la surface à la texture
        if (text_texture[i] == NULL)
        end_sdl(0, "Can't create texture from surface", window, renderer);

        SDL_FreeSurface(text_surface[i]);                                       // la texture ne sert plus à rien
        pos.x =  i*separation + window_dimensions.w/7;

        SDL_QueryTexture(text_texture[i], NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
        SDL_RenderCopy(renderer, text_texture[i], NULL, &pos);
    }

    free(text_texture);
}


void affiche_poisson_score(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture** texture_pechedujour)
{
    //Affichage des différents poissons
    int posy = 80,
        posx,
        deltax,
        window_w,
        deltay;
    SDL_GetWindowSize(window, &window_w, &deltay);
    posx= window_w/7 -90;
    deltax =window_w/10;

    appliquer_image(texture_pechedujour[0], window, renderer, 2, posx, posy, 5, 0);
    posx+=deltax;
    appliquer_image(texture_pechedujour[1], window, renderer, 2, posx, posy-10, 3, 0);
    posx+=deltax;
    appliquer_image(texture_pechedujour[2], window, renderer, 2, posx, posy, 3, 0);
    posx+=deltax;
    appliquer_image(texture_pechedujour[3], window, renderer, 2, posx, posy, 3, 0);
    posx+=deltax;
    appliquer_image(texture_pechedujour[4], window, renderer, 2, posx, posy-5, 2, 0);
    posx+=deltax;
    appliquer_image(texture_pechedujour[5], window, renderer, 2, posx, posy, 1.3, 0);
    posx+=deltax;
    appliquer_image(texture_pechedujour[6], window, renderer, 2, posx, posy+2, 2, 0);
    posx+=deltax;
    appliquer_image(texture_pechedujour[7], window, renderer, 2, posx, posy, 2, 0);
}


int prix_revente(int poisson[8])
{
    int prix_revente = 0;
    prix_revente += (poisson[0]*1);
    prix_revente += (poisson[1]*2);
    prix_revente += (poisson[2]*3);
    prix_revente += (poisson[3]*7);
    prix_revente += (poisson[4]*15);
    prix_revente += (poisson[5]*10);
    prix_revente += (poisson[6]*8);
    prix_revente += (poisson[7]*12);
    for(int i=0; i<8; i++) poisson[i] = 0;

    return prix_revente ;
}

SDL_Texture* appliquer_score(SDL_Renderer *renderer, TTF_Font *font, int argent, SDL_Rect *pos)
{
    SDL_Color blanc = {255, 255, 255, 255};
    char tmp[10];
    sprintf(tmp, "%d", argent);
    SDL_Surface *or_surface = TTF_RenderText_Blended(font, tmp, blanc);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, or_surface);
    SDL_QueryTexture(texture, NULL, NULL, &(pos->w), &(pos->h));
    SDL_FreeSurface(or_surface);

    return texture;
}


void ecran_debut(SDL_Renderer *renderer, TTF_Font *font)
{
    //On affiche les regles sur un écran noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); 
    SDL_Rect pos,dest;
    pos.x = 0;
    pos.y = 0;
    dest.x = 500;
    dest.y = 0;
    dest.w = 1000;
    dest.h = 500;

    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Surface *or_surface = TTF_RenderText_Blended(font, 
        "Appuyez sur une touche pour commencer", 
        blanc);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, or_surface);
    SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
    SDL_FreeSurface(or_surface);
    
   // pos.w*=10;
    SDL_RenderCopy(renderer, texture,
                 &pos,
                 &dest);  
    SDL_DestroyTexture(texture); 

    or_surface = TTF_RenderText_Blended(font, 
        "Vous pouvez vendre avec r et acheter de la musique", 
        blanc);
    texture = SDL_CreateTextureFromSurface(renderer, or_surface);
    SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
    SDL_FreeSurface(or_surface);
    dest.y +=250;
    SDL_RenderCopy(renderer, texture,
                 &pos,
                 &dest);  
    SDL_DestroyTexture(texture); 

    SDL_RenderPresent(renderer); 
    int continuer=1;
    SDL_Event e;
    while(continuer)
    {
        if(SDL_PollEvent(&e))
        {
            if(e.type == SDL_KEYDOWN) continuer=0;
        }
    }

}