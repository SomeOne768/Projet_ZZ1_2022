#ifndef _DELIMITE_H_
#define _DELIMITE_H_

char ** CreerMatrice(int n, int m);
void drawMatrice(SDL_Renderer* renderer, int n, int m, char ** tab, int taille_carre);
void LibererMatrice(int n, char ** tab);
int nb_voisins_delimite(char ** matrice, int n, int m, int x, int y);
int future_case_delimite(char ** matrice, int x, int y, int n, int m, char* B, char *S);
void future_matrice_delimite(char ** matrice, int n, int m, char* B, char *S, char ** future_matrice);
void echangematrice(int n, int m, char ** matrice, char ** futurematrice);
int compareMatrice(char** matrice1, char ** matrice2, int n, int m);

#endif