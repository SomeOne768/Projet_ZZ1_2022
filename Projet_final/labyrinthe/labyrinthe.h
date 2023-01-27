#ifndef __labyrinthe_h__
#define __labyrinthe_h__
#define HAUT 0
#define BAS 1
#define GAUCHE 2
#define DROITE 3
#define GAMMA 0.999999999
#define NBITE 5000
#define PROBA_X 95
#define EPS 0.95

 
char** init_matrice_labyrinthe(char *filename, int *nbligne, int *nbcol);
void position(char **M, int n, int m, int *x, int *y);
void affiche_labyrinthe(char **M, int n, int m);
int mouvement_haut(char **M, int n, int m, int *x, int *y);
int mouvement_bas(char **M, int n, int m, int *x, int *y);
int mouvement_droite(char **M, int n, int m, int *x, int *y);
int mouvement_gauche(char **M, int n, int m, int *x, int *y);
int mouvement(char **M, int n, int m, int *x, int *y, int action);
int h_laby(int x, int y, int m);
int run_qualite_action_laby(double **Cosimienne, char **M, int n, int m, double proba_x, double eps);
void LibererLaby(char **M, int n);
int meilleur_action_laby(double **Cosimienne, int etat);
void copiage(char **M1, char **M2, int n, int m);

#endif