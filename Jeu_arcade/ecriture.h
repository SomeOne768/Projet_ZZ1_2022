#ifndef _ECRITURE_H_
#define _ECRITURE_H_

SDL_Surface** creation_surfaces(int *poisson, int dernier_poisson, TTF_Font* font, SDL_Window *window, SDL_Renderer *renderer);
void affiche_score(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface** text_surface);
void affiche_poisson_score(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture** texture_pechedujour);
int prix_revente(int poisson[8]);
SDL_Texture* appliquer_score(SDL_Renderer *renderer, TTF_Font *font, int argent, SDL_Rect *pos);
void ecran_debut(SDL_Renderer *renderer, TTF_Font *font);
#endif