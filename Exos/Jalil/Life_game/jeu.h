#ifndef __jeu_h__
#define __jeu_h__
#include <SDL2/SDL.h>

char** CreerMatrice(int n, int m);
void LiberationMatrice(char **M, int n);
void draw(SDL_Renderer* renderer, char **M, int n, int m, int h);
void evolution_matrice(char **avant, char **apres, int n, int m, char *B, char *S);
int nombre_voisin(char **M, int n, int m, int i, int j);
int nombre_voisin_thorique(char **M, int n, int m, int i, int j);
void evolution_matrice_thorique(char **avant, char **apres, int n, int m, char *B, char *S);
int estStable(char **M1, char **M2, int n, int m);
void colorerMatrice(char **M, int taille_carre, int x, int y);
void enregistrerMatrice(char **M, int n, int m, char *filemane);
char** chargerMatrice(char *filemane);
void MatriceCreuse(char **Matrice_avant, int n, int m);
void MatriceRandom(char **Matrice_avant, int n, int m);
char** user_matrix(SDL_Renderer *renderer, int n, int m, int taille_carre);
#endif