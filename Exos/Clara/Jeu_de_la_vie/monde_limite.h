#ifndef __MONDE_LIMITE__
#define __MONDE_LIMITE__
#include <SDL2/SDL.h>


char ** CreerMatrice(int n, int m);


void Liberation_matrice(char **M, int n);

void draw(SDL_Renderer*, char**, int n, int m, int h);

int nb_voisin(char ** Matrice, int n, int m, int a, int b );

int etatstable(char ** Mat1, char** Mat2, int n,int m);

void nvlle_matrice(char** avant, char** apres, int n, int m, int *Birth, int * Survive);

void enregistrerMatrice(char **Matrice, int n, int m, char *fichier);

void colorerMatrice(char **M, int taille_carre, int x, int y);

char** chargerMatrice(char *fichier);




#endif