#ifndef _TORE_H_
#define _TORE_H_


int nb_voisins_tore(char ** matrice, int n, int m, int x, int y);
int future_case_tore(char ** matrice, int x, int y, int n, int m, char* B, char *S);
void future_matrice_tore(char ** matrice, int n, int m, char* B, char *S, char ** future_matrice);


#endif