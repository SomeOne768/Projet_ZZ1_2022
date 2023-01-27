#ifndef __ECRITURE_H__
#define __ECRITURE_H__

SDL_Surface** creation_surfaces(int compteurs[3], TTF_Font* font, SDL_Window *window, SDL_Renderer *renderer, int platdistribue);
void affiche_compteur(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface** text_surface);
void LibererCompteur(SDL_Surface ***text_surface);
SDL_Texture* appliquer_profit(SDL_Renderer *renderer, TTF_Font *font, int profit, SDL_Rect *pos);
void affiche_nourriture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture** texture_nourriture);

#endif